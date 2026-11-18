#include <cstdint>
#include <sys/types.h>

#pragma once

namespace kestrel::io {
    
int open_binary_file_and_get_descriptor(const char* binary_file_path);
off_t get_binary_file_size(int fd);
char* mmap_extracted_binary_file(int fd);
uint16_t decode_big_endian_message_length(const uint8_t* ptr);

}