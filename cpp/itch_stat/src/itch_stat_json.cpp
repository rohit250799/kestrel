#include "kestrel/itch_stat_json.hpp"
#include "kestrel/Errorcode.h"
#include <array>
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <sstream>
#include <iostream>
#include <string_view>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <sys/stat.h>
#include <sys/mman.h>

namespace kestrel::itch_stat_json {

void check_orphan_cancels_or_executes() {
    //receiving an order cancel (X) or order delete (D) or
    // Order Execute (E / C) message for a order reference number that
    // was never explicitly added
}

int open_binary_file_and_get_descriptor(const char* binary_file_path="/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50") {
    int fd = open(binary_file_path, O_RDONLY);
    if (fd == -1) {
        throw kestrel::itch_stat_json::Error_codes::IO_Error;
    }
    return fd;
}

off_t get_binary_file_size(int fd=open_binary_file_and_get_descriptor()) {
    assert(fd != -1 && "Assertion failed: file descriptor is negative \n");
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        throw kestrel::itch_stat_json::Error_codes::IO_Error;
    }
    return sb.st_size;
}

uint64_t convert_timestamp(const std::array<uint8_t, 6>& timestamp) {
    uint64_t result {0};
    for (int i =0; i < 6; ++i) {
        result = (result << 8) | timestamp[i];
    }
    return result;
}

uint16_t decode_big_endian_message_length(const uint8_t* ptr) {
    return (static_cast<uint16_t>(ptr[0]) << 8 | static_cast<uint16_t>(ptr[1]));
}

Itch_Stat_JSON::Itch_Stat_JSON() {
    acceptable_message_length = {12, 39, 25, 20, 26, 35, 12, 28, 21, 32, 40, 31, 36, 23, 19, 44, 19, 50, 20, 48};
    total_anomalies_count = {0};
    total_messages = {0};
    first_timestamp.fill(0xFF);
    last_timestamp.fill(0x00);
}

unsigned int Itch_Stat_JSON::get_anomalies_count() {
    return total_anomalies_count;
}

unsigned int Itch_Stat_JSON::get_total_messages_count() {
    return total_messages;
}

char* Itch_Stat_JSON::mmap_extracted_binary_file(int fd=open_binary_file_and_get_descriptor()) {
    assert(fd != -1);
    long binary_file_size = get_binary_file_size();
    assert(binary_file_size > 0);
    char* addr = static_cast<char*>(mmap(NULL, binary_file_size, PROT_READ, MAP_PRIVATE | MAP_NORESERVE, fd, 0));
    if (addr == MAP_FAILED) {
        close(fd);
        throw kestrel::itch_stat_json::Error_codes::System_Error;
    }
    return addr;
}

void Itch_Stat_JSON::parse_mmap_binary_file(int fd=open_binary_file_and_get_descriptor()) {
    assert(fd != -1);
    char* mapped_file;
    off_t binary_file_size;

    try {
        mapped_file = mmap_extracted_binary_file();
        binary_file_size = get_binary_file_size();
    } catch (const kestrel::itch_stat_json::Error_codes& e) {
        if (int(e) == 3) {
            close(fd);
            std::cerr << "Cannot mmap file \n";
            return;
        }
    }

    assert(binary_file_size >= sizeof(stock_directory_message));

    uint16_t message_length_value {0};
    unsigned int total_anomalies_count {get_anomalies_count()};
    unsigned int total_messages_count {get_total_messages_count()};
    auto first_byte_mapped_file = mapped_file[0];
    auto second_byte_mapped_file = mapped_file[1];

    for(std::size_t i = 0; i < binary_file_size; ) {
        size_t first_byte_mapped_file_index = i + message_length_value;
        size_t second_byte_mapped_file_index = i + message_length_value + 1;
        first_byte_mapped_file = mapped_file[first_byte_mapped_file_index];
        second_byte_mapped_file = mapped_file[second_byte_mapped_file_index];
        std::uint8_t temp_buffer[2] = {
            static_cast<uint8_t>(first_byte_mapped_file),
            static_cast<uint8_t>(second_byte_mapped_file)
        };
        message_length_value = decode_big_endian_message_length(temp_buffer);
        if (!acceptable_message_length.contains(message_length_value)) {
            // check which type of message and increment its counter
            total_anomalies_count += 1;
            total_messages_count += 1;
            i = second_byte_mapped_file_index + 1;
            continue;
        }
        total_messages_count += 1;
        i = second_byte_mapped_file_index + 1;
    }

    std::cout << "The total anomaly count is: " << total_anomalies_count << " \n";
    close(fd);
    return;
}

std::string Itch_Stat_JSON::convert_to_JSON() const {
    std::ostringstream oss;
    oss << "{\n"
        << "  \"first_timestamp\": \"" << convert_timestamp(first_timestamp) << "\",\n"
        << "  \"last_timestamp\": " << convert_timestamp(last_timestamp) << ",\n"
        << "  \"Total bytes\": " << total_bytes << ",\n"
        << "  \"Total messages\": " << total_messages << ",\n"
        << "}";
    return oss.str();
}

void Itch_Stat_JSON::check_for_anomalies() {

}

Itch_Stat_JSON::~Itch_Stat_JSON() {
    char* addr = mmap_extracted_binary_file();
    off_t binary_file_size {get_binary_file_size()};
    int unmapping_result {munmap(addr, binary_file_size)};
    assert(unmapping_result == 0 && "Assertion failed: Memory unmap not succcesful \n");
    close(fd);
}

}
