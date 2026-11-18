#include <cstdint>
#include <fstream>
#include <map>
#include <string>
#include <sys/types.h>

namespace kestrel::itch_filter {

class ITCH_Filter {
    public:
    ITCH_Filter();
    // ~ITCH_Filter();
    std::map<std::string, short> get_universe_stock_locate_map();
    void parse_mmap_unfiltered_binary_file(int fd);
    uint32_t get_SRH_messages_count();
    bool create_an_empty_binary_file_for_filtered_data();
    void check_if_filtered_file_exists();
    bool write_message_to_filtered_binary_file(char* message_start, uint16_t message_length, std::ofstream& ofs);

    private:
    std::map<std::string, short> universe_stock_locate_map;
    uint32_t SRH_messages_count;

};

}
