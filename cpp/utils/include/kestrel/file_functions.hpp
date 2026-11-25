#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <sys/types.h>
#include <type_traits>
#include <algorithm>

#pragma once

namespace kestrel::io {
    
int open_binary_file_and_get_descriptor(const char* binary_file_path);
off_t get_binary_file_size(int fd);
char* mmap_extracted_binary_file(int fd);
uint16_t decode_big_endian_message_length(const uint8_t* ptr);

template<typename T>
constexpr T byteswap(T value) noexcept {
    static_assert(std::has_unique_object_representations_v<T>, "T may not have padding bits");
    auto value_representation = std::bit_cast<std::array<std::byte, sizeof(T)>>(value);
    std::ranges::reverse(value_representation);
    return std::bit_cast<T>(value_representation);
}

template<typename T>
T read_big_endian(const uint8_t* buffer, std::size_t offset) {
    static_assert(std::is_integral_v<T>, "Type must be integral");
    T value{};
    
    std::memcpy(&value, buffer+offset, sizeof(T));
    if constexpr (std::endian::native == std::endian::little)
        value = byteswap(value);
    return value;
}

}