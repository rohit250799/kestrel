#include <cstddef>
#include <cstdint>
#include <fstream>
#include <map>
#include <string>
#include <sys/types.h>
#include <filesystem>
#include <vector>

namespace kestrel::itch_filter {

bool check_if_filtered_file_exists(const std::filesystem::path f);

class ITCH_Filter {
    public:
    ITCH_Filter();
    ~ITCH_Filter();
    std::map<std::string, short>& get_universe_stock_locate_map();
    void parse_mmap_unfiltered_binary_file();
    uint32_t get_SRH_messages_count();
    bool create_an_empty_binary_file_for_filtered_data();
    bool write_message_to_filtered_binary_file(char* message_start, uint16_t message_length, std::ofstream& ofs);
    bool check_if_only_SRH_messages_in_filtered_file();
    bool load_filtered_file_into_buffer(const std::filesystem::path filtered_file_path, int fd);
    std::vector<uint8_t>& get_filtered_file_buffer();

    private:
    std::map<std::string, short> universe_stock_locate_map;
    off_t filtered_binary_file_size;
    std::vector<uint8_t> filtered_file_buffer;
    static inline const std::filesystem::path filtered_file_path="/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50_filtered.bin";
    static inline const std::filesystem::path unfiltered_file_path="/media/coding/Quant_projects/kestrel/12302019.NASDAQ_ITCH50.bin";
    uint32_t SRH_messages_count;
    int filtered_file_descriptor;
    int unfiltered_file_descriptor;
};

}
