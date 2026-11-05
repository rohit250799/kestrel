#include <cstdint>
#include <unordered_map>

namespace kestrel::itch_stat_json {

struct stock_directory_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    uint8_t timestamp[6];
    char stock[8];
    char market_category;
    char financial_status_indicator;
    int round_lot_size; //standardized fixed number of units traded on an exchange
    char round_lots_only;
    char issue_clarification;
    char issue_sub_type;
    char authenticity;
    char short_sale_threshold_indicator;
    char ipo_flag;
    char luld_reference;
    char etp_flag;
    int etp_leverage_factor;
    char inverse_indicator;
};

int open_binary_file_and_get_descriptor(const char* binary_file_path);

class Itch_Stat_JSON {
    public:
    Itch_Stat_JSON();
    char* mmap_extracted_binary_file(int fd);
    void check_for_anomalies();
    void parse_mmap_binary_file(int fd);
    long get_total_bytes();

    private:
    std::unordered_map<char, unsigned int> count_per_messge_type;
    unsigned long long first_timestamp;
    unsigned long long last_timestamp;
    unsigned long total_bytes;
    unsigned int total_messages;
    int fd;
};

}
