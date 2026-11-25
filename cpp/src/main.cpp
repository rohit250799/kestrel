#include "kestrel/itch_stat_json.hpp"
#include "kestrel/itch_filter.hpp"
#include "kestrel/file_functions.hpp"
#include <cerrno>
#include <iostream>
#include <cassert>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./app <modeA | modeB>\n";
        return 1;
    }

    std::string command = argv[1];
    if (command == "itch_stat") {
        kestrel::itch_stat_json::Itch_Stat_JSON my_itch_stat_json;
        int fd {kestrel::io::open_binary_file_and_get_descriptor("/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50")};
        my_itch_stat_json.parse_mmap_binary_file(fd);
        return 0;
    }
    if (command == "itch_filter") {
        int filtered_fd {-1};
        try {
            filtered_fd = {kestrel::io::open_binary_file_and_get_descriptor("/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50")};
        } catch(...) {
            std::cerr << "Error getting the unfiltered file descriptor" << errno << " \n";
            return 1;
        }
        kestrel::itch_filter::ITCH_Filter my_itch_filter;
        my_itch_filter.parse_mmap_unfiltered_binary_file();
        auto filtering_result = my_itch_filter.check_if_only_SRH_messages_in_filtered_file();
        if (!filtering_result) {
            std::cout << "Check failed: Other messages also present \n";
            return 1;
        }
        std::cout << "All checks passed: only allowed types exist \n";
        return 0;
    }
    else {
        std::cerr << "Invalid command entered.. \n";
        return 1;
    }
}
