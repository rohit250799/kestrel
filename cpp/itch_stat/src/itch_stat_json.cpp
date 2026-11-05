#include "kestrel/itch_stat_json.hpp"
#include "kestrel/Errorcode.h"
#include <cassert>
#include <cerrno>
#include <cstddef>
#include <iostream>
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
        return -1;
    }
    close(fd);
    return fd;
}

long get_binary_file_size(int fd=open_binary_file_and_get_descriptor()) {
    assert(fd != -1 && "Assertion failed: file descriptor is negative \n");
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        throw kestrel::itch_stat_json::Error_codes::IO_Error;
    }
    return sb.st_size;
}

Itch_Stat_JSON::Itch_Stat_JSON() {
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
    close(fd);
    return addr;
}

void Itch_Stat_JSON::parse_mmap_binary_file(int fd=open_binary_file_and_get_descriptor()) {
    assert(fd != -1);
    char* mapped_file;
    long binary_file_size;

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

    assert(binary_file_size > 0);
    auto* current_tick = reinterpret_cast<stock_directory_message*>(mapped_file);
    auto* end_tick = reinterpret_cast<stock_directory_message*>(static_cast<char*>(mapped_file + binary_file_size));
    auto first_timestamp {current_tick->timestamp};
    auto last_timestamp {current_tick->timestamp};
    long total_bytes {0};

    while (current_tick < end_tick) {
        auto current_tick_message_type {current_tick->Message_type};
        auto current_tick_message_byte {sizeof(current_tick)};
        total_bytes += current_tick_message_byte;
        if (current_tick->timestamp < first_timestamp)
            first_timestamp = current_tick->timestamp;
        if (current_tick->timestamp > last_timestamp)
            last_timestamp = current_tick->timestamp;
        ++current_tick;
    }
    std::cout << "The binary file has been parsed successfully \n";
    return;
}

void Itch_Stat_JSON::check_for_anomalies() {

}

}
