#include <cstdint>

namespace kestrel::itch_stat_json {

enum class Error_codes : uint8_t {
    None = 0,
    Timeout = 1,
    IO_Error = 2,
    System_Error = 3
};

[[nodiscard]] const char* to_string(Error_codes code) noexcept;

}
