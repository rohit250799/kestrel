#include <cstdint>
#include <array>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include "message_type_enums.h"

namespace kestrel::itch_stat_json {

struct stock_directory_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char stock[8];
    Stock_Directory_Message_market_category market_category;
    Stock_Directory_Message_Financial_Status_Indicator financial_status_indicator;
    int round_lot_size; //standardized fixed number of units traded on an exchange
    Stock_Directory_Message_Round_Lots_Only round_lots_only;
    char issue_clarification;
    char issue_sub_type;
    Stock_Directory_Message_Authenticity authenticity;
    Stock_Directory_Message_Short_Sale_Threshold_Indicator short_sale_threshold_indicator;
    Stock_Directory_Message_IPO_Flag ipo_flag;
    Stock_Directory_Message_LULD_Reference_Price_Tier luld_reference;
    Stock_Directory_Message_ETP_Flag etp_flag;
    int etp_leverage_factor;
    Stock_Directory_Message_Inverse_Indicator inverse_indicator;
};

struct system_event_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    System_Event_Message_event_code event_code;
};

struct stock_trading_action_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char stock[8];
    Stock_Trading_action_Trading_State trading_state;
    char reserved;
    char reason[4];
};

struct reg_sho_registration_message {
    char Message_type;
    short locate_code;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char stock[8];
    Reg_SHO_Restriction_reg_sho_action reg_sho_action;
};

struct market_participant_position_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char MPID[4];
    char stock[8];
    Market_Participant_position_primary_market_maker primary_market_maker;
    Market_Participant_position_market_maker_mode market_maker_mode;
    Market_Participation_position_market_participant_state market_participant_state;
};

struct mwcb_decline_level_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t level_1;
    int64_t level_2;
    int64_t level_3;
};

struct mwcb_status_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    MWCB_status_message_breached_level breached_level;
};

struct IPO_Quoting_period_update_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char stock[8];
    int ipo_quotation_release_time;
    IPO_Quoting_period_update_message_ipo_quotation_release_qualifier ipo_quotation_release_qualifier;
    int ipo_price;
};

struct luld_action_collar_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char stock[8];
    int action_collar_reference_price;
    int upper_action_collar_price;
    int lower_auction_collar_price;
    int auction_collar_extension;
};

struct operation_halt_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char stock[8];
    Operation_halt_message_market_code market_code;
    Operation_halt_message_operational_halt_action operational_halt_action;
};

struct add_order_no_mpid_attribution_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t order_reference_number;
    order_message_buy_sell_indicator buy_sell_indicator;
    int32_t shares;
    char stock[8];
    int price;
};

struct add_order_mpid_attribution_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t order_reference_number;
    order_message_buy_sell_indicator buy_sell_indicator;
    int32_t shares;
    char stock[8];
    int price;
    char attribution[4];
};

struct add_order_order_executed_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t order_reference_number;
    int32_t executed_shares;
    int64_t match_number;
};

struct add_order_order_executed_with_price_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t order_reference_number;
    int32_t executed_shares;
    int64_t match_number;
    add_order_executed_with_price_message_printable printable;
    int execution_price;
};

struct order_cancel_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t order_reference_number;
    int32_t cancelled_shares;
};

struct order_delete_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t original_order_reference_number;
    int64_t new_order_reference_number;
    int32_t shares;
    int price;
};

struct order_replace_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t order_reference_number;
    order_message_buy_sell_indicator buy_sell_indicator;
    int32_t shares;
    char stock[8];
    int price;
    int64_t match_number;
};

struct trade_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t order_reference_number;
    order_message_buy_sell_indicator buy_sell_indicator;
    int32_t shares;
    char stock[8];
    int price;
    int64_t match_number;
};

struct cross_trade_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t shares;
    char stock[8];
    int cross_price;
    int64_t match_number;

};

struct broken_trade_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    int64_t match_number;
};

struct noii_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    uint64_t paired_shares;
    uint64_t imbalance_shares;
    noii_message_imbalance_direction imbalance_direction;
    char stock[8];
    int far_price;
    int near_price;
    int current_reference_price;
    noii_message_cross_type cross_type;
    noii_message_price_variation_indicator price_variation_indicator;
};

struct retail_interest_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char stock[8];
    retail_interest_message_interest_flag interest_flag;
};

struct direct_listing_with_capital_raise_message {
    char Message_type;
    short stock_locate;
    short tracking_number;
    std::array<uint8_t, 6> timestamp;
    char stock[8];
    direct_listing_with_capital_raise_message_open_eligibility_status open_eligibility_status;
    int minimum_allowable_price;
    int maximum_allowable_price;
    int near_execution_price;
    uint64_t near_execution_time;
    int lower_price_range_collar;
    int upper_price_range_collar;
};

struct Raw_data_for_json {
    std::array<uint16_t, 26> existing_message_frequencies_raw {};
    std::array<uint8_t, 6> first_timestamp;
    std::array<uint8_t, 6> last_timestamp;
    unsigned long total_bytes;
    unsigned int total_anomalies_count;
    unsigned int total_messages;
    unsigned int operational_halt_message_count;
};

using message_record_type = std::variant<system_event_message, stock_directory_message, stock_trading_action_message, reg_sho_registration_message, market_participant_position_message, mwcb_decline_level_message, mwcb_status_message, IPO_Quoting_period_update_message, luld_action_collar_message, operation_halt_message, add_order_no_mpid_attribution_message, add_order_mpid_attribution_message, add_order_order_executed_message, add_order_order_executed_with_price_message, order_cancel_message, order_delete_message, order_replace_message, trade_message, cross_trade_message, broken_trade_message, noii_message, retail_interest_message, direct_listing_with_capital_raise_message>;

struct binary_file_message {
    short message_length;
    message_record_type record_type;
};

int open_binary_file_and_get_descriptor(const char* binary_file_path);

class Itch_Stat_JSON {
    public:
    Itch_Stat_JSON();
    ~Itch_Stat_JSON();
    char* mmap_extracted_binary_file(int fd);
    unsigned int get_anomalies_count();
    unsigned int get_total_messages_count();
    unsigned int get_operational_halt_message_type_count();
    std::array<uint16_t, 26>& get_acceptable_message_types_array();
    unsigned long get_total_bytes_count();
    void parse_mmap_binary_file(int fd);
    long get_total_bytes();
    std::string convert_to_JSON(const Raw_data_for_json& raw_data) const;

    private:
    std::unordered_map<char, unsigned int> count_per_messge_type;
    std::unordered_set<int> acceptable_message_length;
    std::array<uint16_t, 26> acceptable_message_types {};
    std::array<uint8_t, 6> first_timestamp {};
    std::array<uint8_t, 6> last_timestamp {};
    unsigned long total_bytes;
    unsigned int total_anomalies_count;
    unsigned int total_messages;
    unsigned int operational_halt_message_count;
    int fd;
};

}
