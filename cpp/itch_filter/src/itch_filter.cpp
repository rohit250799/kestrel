#include "kestrel/itch_filter.hpp"
#include "kestrel/file_functions.hpp"
#include "kestrel/Errorcode.h"
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <vector>

namespace kestrel::itch_filter {

template<typename T>
char* as_bytes(T& i) {
    return static_cast<char*>(&i);
}

bool check_if_filtered_file_exists(const std::filesystem::path f) {
    if (exists(f))
        return true;
    return false;
}

std::map<std::string, short>& ITCH_Filter::get_universe_stock_locate_map() {
    return universe_stock_locate_map;
}

uint32_t ITCH_Filter::get_SRH_messages_count() {
    return SRH_messages_count;
}

std::vector<uint8_t>& ITCH_Filter::get_filtered_file_buffer() {
    return filtered_file_buffer;
}

bool ITCH_Filter::write_message_to_filtered_binary_file(char* message_start, uint16_t message_length, std::ofstream& ofs) {
    if (!ofs){
        std::cerr << errno;
        throw kestrel::io::Error_codes::IO_Error;
        return false;
    }

    for (auto i = 0; i <= message_length; ++i) {
        ofs.write(as_bytes(message_start[i]), message_length);
    }
    return true;
}

ITCH_Filter::ITCH_Filter() {
    unfiltered_file_descriptor = {kestrel::io::open_binary_file_and_get_descriptor("/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50")};
    filtered_file_descriptor = -1;
    filtered_binary_file_size = 0;
    universe_stock_locate_map = {
        {"AAPL", -1},
        {"MSFT", -1},
        {"AMZN", -1},
        {"GOOGL", -1},
        {"FB", -1},
        {"NVDA", -1},
        {"INTC", -1},
        {"CSCO", -1},
        {"CMSA", -1},
        {"PEP", -1},
        {"ADBE", -1},
        {"NFLX", -1},
        {"TSLA", -1},
        {"QQQ", -1},
        {"AMD", -1},
        {"MU", -1},
        {"SBUX", -1},
        {"COST", -1},
        {"PYPL", -1},
        {"AVGO", -1}
    };

    SRH_messages_count = {0};
}

void ITCH_Filter::parse_mmap_unfiltered_binary_file() {
    assert(unfiltered_file_descriptor != -1);
    char* mapped_file;
    off_t binary_file_size;

    try {
        mapped_file = kestrel::io::mmap_extracted_binary_file(unfiltered_file_descriptor);
        binary_file_size = kestrel::io::get_binary_file_size(unfiltered_file_descriptor);
    } catch (kestrel::io::Error_codes& e) {
        close(unfiltered_file_descriptor);
        std::cerr << "Cannot mmap file \n";
        return;
    }

    SRH_messages_count = get_SRH_messages_count();
    uint16_t message_length_value {0};
    auto first_byte_mapped_file = mapped_file[0];
    auto second_byte_mapped_file = mapped_file[1];
    const std::filesystem::path unfiltered_file_path = "/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50.bin";

    std::ifstream ifs(unfiltered_file_path, std::ios_base::binary);
    std::ofstream ofs(filtered_file_path, std::ios_base::binary);
    std::filesystem::permissions(filtered_file_path, std::filesystem::perms::owner_write, std::filesystem::perm_options::add);

    for(std::size_t i = 0; i < binary_file_size; ) {
        size_t first_byte_mapped_file_index = i + message_length_value;
        size_t second_byte_mapped_file_index = i + message_length_value + 1;
        first_byte_mapped_file = mapped_file[first_byte_mapped_file_index];
        second_byte_mapped_file = mapped_file[second_byte_mapped_file_index];

        std::uint8_t temp_buffer[2] = {
            static_cast<uint8_t>(first_byte_mapped_file),
            static_cast<uint8_t>(second_byte_mapped_file)
        };
        message_length_value = kestrel::io::decode_big_endian_message_length(temp_buffer);

        // checking all the existing SRH messages and writing them to the new binary file
        auto message_body_first_byte = mapped_file[second_byte_mapped_file_index + 1];
        if (message_body_first_byte == 'S' || message_body_first_byte == 'R' || message_body_first_byte == 'H' ) {
            SRH_messages_count += 1;
            // write to empty binary file - thinking about skipping the decoding part and passing the entire message body as a const reference to the write function
            i = second_byte_mapped_file_index + 1;
            try {
                write_message_to_filtered_binary_file(&mapped_file[i], message_length_value, ofs);
            } catch(kestrel::io::Error_codes& e) {
                std::cerr << "Failed to write message to binary file: " << errno << " \n";

            }
            auto next_message_start = i;
            continue;
        }
        i = second_byte_mapped_file_index + 1;
    }

    if (std::filesystem::is_empty(filtered_file_path)) {
        throw std::runtime_error("Filter file does not exist or is empty.");
        std::cerr << "File does not exist or is empty " << errno << " \n";
    }
    return;
}

bool ITCH_Filter::load_filtered_file_into_buffer(const std::filesystem::path filtered_file_path, int file_descriptor) {
    if (!check_if_filtered_file_exists(filtered_file_path))
        return false;
    filtered_file_descriptor = kestrel::io::open_binary_file_and_get_descriptor("/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50_filtered.bin");
    std::ifstream ifs(filtered_file_path, std::ios_base::binary);
    if (!ifs)
        return false;
    uint16_t message_length_value {0};
    filtered_file_buffer.reserve(filtered_binary_file_size);
    if(!ifs.read(reinterpret_cast<char*>(filtered_file_buffer.data()), filtered_binary_file_size))
        return false;
    return true;
}

bool ITCH_Filter::check_if_only_SRH_messages_in_filtered_file() {
    assert(check_if_filtered_file_exists(filtered_file_path) && "Filtered file does not exist \n");
    bool buffer_loading_result = load_filtered_file_into_buffer(filtered_file_path, filtered_file_descriptor);
    if (!buffer_loading_result) {
        std::cout << "Buffer empty! \n";
        return false;
    }
    uint16_t message_length_value {0};
    auto first_byte_vector = 0;
    auto second_byte_vector = 0;

    for (std::size_t i = 0; i < filtered_file_buffer.size(); ) {
        size_t first_byte_file_index = i + message_length_value;
        size_t second_byte_file_index = i + message_length_value + 1;
        first_byte_vector = filtered_file_buffer[first_byte_file_index];
        second_byte_vector = filtered_file_buffer[second_byte_file_index];
        std::uint8_t temp_buffer[2] = {
            static_cast<uint8_t>(first_byte_vector),
            static_cast<uint8_t>(second_byte_vector)
        };
        message_length_value = kestrel::io::decode_big_endian_message_length(temp_buffer);
        if (message_length_value != 12 || message_length_value != 39 != message_length_value != 25)
            return false;
        auto message_body_first_byte = filtered_file_buffer[second_byte_file_index + 1];
        int message_body_first_byte_int {message_body_first_byte - 'A'};
        if (message_body_first_byte_int != 12 || message_body_first_byte_int != 11 || message_body_first_byte_int != 17)
            return false;
        i = second_byte_file_index + 1;
        continue;
    }
    return true;
}

ITCH_Filter::~ITCH_Filter() {
    close(filtered_file_descriptor);
    close(unfiltered_file_descriptor);
}

}
