#include <cassert>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include "kestrel/Errorcode.h"
#include "kestrel/file_functions.hpp"

namespace kestrel::io {

int open_binary_file_and_get_descriptor(const char* binary_file_path="/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50") {
    int fd = open(binary_file_path, O_RDONLY);
    if (fd == -1) {
        throw kestrel::io::Error_codes::IO_Error;
    }
    return fd;
}

off_t get_binary_file_size(int fd=open_binary_file_and_get_descriptor()) {
    assert(fd != -1 && "Assertion failed: file descriptor is negative \n");
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        throw kestrel::io::Error_codes::IO_Error;
    }
    return sb.st_size;
}

char* mmap_extracted_binary_file(int fd=open_binary_file_and_get_descriptor()) {
    assert(fd != -1);
    long binary_file_size = get_binary_file_size();
    assert(binary_file_size > 0);
    char* addr = static_cast<char*>(mmap(NULL, binary_file_size, PROT_READ, MAP_PRIVATE | MAP_NORESERVE, fd, 0));
    if (addr == MAP_FAILED) {
        close(fd);
        throw kestrel::io::Error_codes::System_Error;
    }
    return addr;
}

uint16_t decode_big_endian_message_length(const uint8_t* ptr) {
    return (static_cast<uint16_t>(ptr[0]) << 8 | static_cast<uint16_t>(ptr[1]));
}

} // namespace kestrel::io