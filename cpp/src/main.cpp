//#include "kestrel/itch_stat_json.hpp"
#include "../include/kestrel/itch_stat_json.hpp"

int main() {
    kestrel::itch_stat_json::Itch_Stat_JSON my_itch_stat_json;
    int fd {kestrel::itch_stat_json::open_binary_file_and_get_descriptor("/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50")};
    my_itch_stat_json.parse_mmap_binary_file(fd);
    return 0;
}
