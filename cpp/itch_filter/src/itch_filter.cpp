#include "kestrel/itch_filter.hpp"
#include "kestrel/itch_stat_json.hpp"
#include <cassert>
#include <cerrno>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>

namespace kestrel::itch_filter {

template<typename T>
char* as_bytes(T& i) {
    return static_cast<char*>(&i);
}

std::map<std::string, short> ITCH_Filter::get_universe_stock_locate_map() {
    return universe_stock_locate_map;
}

uint32_t ITCH_Filter::get_SRH_messages_count() {
    return SRH_messages_count;
}

bool check_if_filtered_file_exists(const std::filesystem::path f = "/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50_filtered.bin") {
    if (exists(f))
        return true;
    return false;
}

bool ITCH_Filter::write_message_to_filtered_binary_file(char* message_start, uint16_t message_length, std::ofstream& ofs) {
    if (!ofs){
        std::cerr << errno;
        throw itch_stat_json::Error_codes::IO_Error;
        return false;
    }

    for (auto i = 0; i <= message_length; ++i) {
        ofs.write(as_bytes(message_start[i]), message_length);
    }
    return true;
}

ITCH_Filter::ITCH_Filter() {
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

int fd = kestrel::itch_stat_json::open_binary_file_and_get_descriptor("/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50");
off_t binary_file_size = kestrel::itch_stat_json::get_binary_file_size(fd);

void ITCH_Filter::parse_mmap_unfiltered_binary_file(int fd) {
    assert(fd != -1);
    char* mapped_file;
    off_t binary_file_size;

    try {
        mapped_file = itch_stat_json::mmap_extracted_binary_file(fd);
        binary_file_size = itch_stat_json::get_binary_file_size(fd);
    } catch (...) {
        close(fd);
        std::cerr << "Cannot mmap file \n";
        return;
    }

    assert(binary_file_size >= sizeof(itch_stat_json::system_event_message));
    SRH_messages_count = get_SRH_messages_count();
    uint16_t message_length_value {0};
    auto first_byte_mapped_file = mapped_file[0];
    auto second_byte_mapped_file = mapped_file[1];
    const std::filesystem::path filter_file_path = "/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50_filtered.bin";
    const std::filesystem::path unfiltered_file_path = "/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50.bin";

    std::ifstream ifs(unfiltered_file_path, std::ios_base::binary);
    std::ofstream ofs(filter_file_path, std::ios_base::binary);

    for(std::size_t i = 0; i < binary_file_size; ) {
        size_t first_byte_mapped_file_index = i + message_length_value;
        size_t second_byte_mapped_file_index = i + message_length_value + 1;
        first_byte_mapped_file = mapped_file[first_byte_mapped_file_index];
        second_byte_mapped_file = mapped_file[second_byte_mapped_file_index];

        std::uint8_t temp_buffer[2] = {
            static_cast<uint8_t>(first_byte_mapped_file),
            static_cast<uint8_t>(second_byte_mapped_file)
        };
        message_length_value = itch_stat_json::decode_big_endian_message_length(temp_buffer);

        // checking all the existing SRH messages and writing them to the new binary file
        auto message_body_first_byte = mapped_file[second_byte_mapped_file_index + 1];
        if (message_body_first_byte == 'S' || message_body_first_byte == 'R' || message_body_first_byte == 'H' ) {
            SRH_messages_count += 1;
            // write to empty binary file - thinking about skipping the decoding part and passing the entire message body as a const reference to the write function
            i = second_byte_mapped_file_index + 1;
            write_message_to_filtered_binary_file(&mapped_file[i], message_length_value, ofs);
            auto next_message_start = i;
            continue;
        }
        i = second_byte_mapped_file_index + 1;
    }

    if (std::filesystem::is_empty(filter_file_path)) {
        throw std::runtime_error("Filter file does not exist or is empty.");
    }
    return;

}

}
