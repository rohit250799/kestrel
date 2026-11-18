#include "../itch_stat/include/kestrel/itch_stat_json.hpp"
#include "../itch_filter/include/kestrel/itch_filter.hpp"
#include <iostream>

int main() {
    kestrel::itch_stat_json::Itch_Stat_JSON my_itch_stat_json;
    int fd {kestrel::itch_stat_json::open_binary_file_and_get_descriptor("/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50")};
    my_itch_stat_json.parse_mmap_binary_file(fd);

    kestrel::itch_filter::ITCH_Filter my_itch_filter;
    my_itch_filter.parse_mmap_unfiltered_binary_file(fd);
    return 0;
}
