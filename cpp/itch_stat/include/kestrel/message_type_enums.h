enum class System_Event_Message_event_code {
    Start_of_Messages = 'O',
    Start_of_System_hours = 'S',
    Start_of_Market_hours = 'Q',
    End_of_Market_hours = 'M',
    End_of_System_hours = 'E',
    End_of_Messages = 'C'
};

enum class Stock_Directory_Message_market_category {
    NASDAQ_Global_Select_market = 'Q',
    NASDAQ_Global_market = 'G',
    NASDAQ_Capital_market = 'S',
    New_York_stock_exchange = 'N',
    NYSE_American = 'A',
    NYSE_Arca = 'P',
    BATS_Z_Exchange = 'Z',
    Investors_Exchange_LLC = 'V',
    Not_Available = ' '
    // <space> means Not Available. Will have to check if this alpha does not appear while parsing - will have to handle this specifically
};

enum class Stock_Directory_Message_Financial_Status_Indicator {
    Deficient = 'D',
    Delinquent = 'E',
    Bankrupt = 'Q',
    Suspended = 'S',
    Deficient_and_Bankrupt = 'G',
    Deficient_and_Delinquent = 'H',
    Delinquent_and_Bankrupt = 'J',
    Deficient_Delinquent_and_Bankrupt = 'K',
    Creations_and_or_Redemptions_suspended_for_Exchange_Traded_Product = 'C',
    Normal_default_Issuer_not_Deficient_Delinquent_or_Bankrupt = 'N',
    Not_Available = ' '
    // <space> = not available. Firms should refer to SIAC feeds for code if needed
};

enum class Stock_Directory_Message_Round_Lots_Only {
    Nasdaq_system_only_accepts_round_lots = 'Y',
    No_order_size_restrictions_in_Nasdaq = 'N'
};

enum class Stock_Directory_Message_Authenticity {
    Production_or_live = 'P',
    Test = 'T'
};

enum class Stock_Directory_Message_Short_Sale_Threshold_Indicator {
    Issue_restricted_under_SEC_rule_203_b3 = 'Y',
    Issue_is_not_restricted = 'N',
    Threshold_indicator_not_available = ' '
    // <space> = threshold indicator not available (special handling needed)
};

enum class Stock_Directory_Message_IPO_Flag {
    Nasdaq_listed_instrument_set_up_as_new_IPO_security = 'Y',
    Nasdaq_listed_instrument_not_set_up_as_new_IPO_security = 'N',
    Not_Available = ' '
};

enum class Stock_Directory_Message_LULD_Reference_Price_Tier {
    Tier_1_NMS_Stocks_and_select_ETPs = 1,
    Tier_2_NMS_Stocks = 2
    // format reversed, integers were to be the keys but not allowed in c++. <space> = not available
};

enum class Stock_Directory_Message_ETP_Flag {
    Instrument_is_an_ETP = 'Y',
    Instrument_is_not_an_ETP = 'N',
    Not_available = ' '
    // <space> = not available
};

enum class Stock_Directory_Message_Inverse_Indicator {
    ETP_is_an_inverse_ETP = 'Y',
    ERP_is_not_an_inverse_ETP = 'N',
};

enum class Stock_Trading_action_Trading_State {
    Halted_across_all_US_equity_markets_or_SRO = 'H',
    Paused_across_all_US_equity_markets_or_SRO = 'P',
    Quotation_only_period_for_cross_SRO_halt_or_pause = 'Q',
    Trading_on_Nasdaq = 'T'
};

enum class Reg_SHO_Restriction_reg_sho_action {
    No_price_test_in_place = '0',
    Reg_SHO_Short_sale_price_test_restriction_in_effect_for_intra_day_price_drop = '1',
    Reg_SHO_Short_sale_price_test_registration_remains_in_effect = '2'
};

enum class Market_Participant_position_primary_market_maker {
    Primary_market_maker = 'Y',
    Non_primary_market_maker = 'N'
};

enum class Market_Participant_position_market_maker_mode {
    Normal = 'N',
    Passive = 'P',
    Syndicate = 'S',
    Pre_syndicate = 'R',
    Penalty = 'L'
};

enum class Market_Participation_position_market_participant_state {
    Active = 'A',
    Excused_or_Withdrawn = 'E',
    Withdrawn = 'W',
    Suspended = 'S',
    Deleted = 'D'
};

enum class MWCB_status_message_breached_level {
    Level_1 = 1,
    Level_2 = 2,
    Level_3 = 3
};

enum class IPO_Quoting_period_update_message_ipo_quotation_release_qualifier {
    Anticipated_quotation_release_time = 'A',
    IPO_release_canceled_or_postponed = 'C'
};

enum class Operation_halt_message_market_code {
    NASDAQ = 'Q',
    BX = 'B',
    PSX = 'X'
};

enum class Operation_halt_message_operational_halt_action {
    Operationally_halted_on_the_identified_market = 'H',
    Operational_halt_lifted_and_trading_resumed = 'T'
};

enum class order_message_buy_sell_indicator {
    Buy_order = 'B',
    Sell_order = 'S'
};

enum class add_order_executed_with_price_message_printable {
    Non_printable = 'N',
    Printable = 'Y'
};

enum class cross_trade_message_cross_type {
    Nasdaq_opening_cross = 'O',
    Nasdaq_closing_cross = 'C',
    Cross_for_IPO_and_halted_or_paused_securities = 'H'
};

enum noii_message_imbalance_direction {
    Buy_imbalance = 'B',
    Sell_imbalance = 'S',
    No_imbalance = 'N',
    Insufficient_orders_to_calculate = 'O',
    Paused = 'P'
};

enum noii_message_cross_type {
    Nasdaq_opening_cross = 'O',
    Nasdaq_closing_cross = 'C',
    Cross_for_IPO_and_halted_or_paused_securities = 'H',
    Extended_trading_close = 'A'
};

enum noii_message_price_variation_indicator {
    Less_than_1_pc = 'L',
    One_to_one_point_nine_nine = 1,
    Two_to_two_point_nine_nine = 2,
    Three_to_three_point_nine_nine = 3,
    Four_to_four_point_nine_nine = 4,
    Five_to_five_point_nine_nine = 5,
    Six_to_six_point_nine_nine = 6,
    Seven_to_seven_point_nine_nine = 7,
    Eight_to_eight_point_nine_nine = 8,
    Nine_to_nine_point_nine_nine = 9,
    Ten_to_nineteen_point_nine = 'A',
    Twenty_to_twenty_nine_point_nine = 'B',
    Thirty_percent_or_greater = 'C',
    Cannot_be_calculated = ' '
};

enum class retail_interest_message_interest_flag {
    RPI_orders_available_on_buy_side = 'B',
    RPI_orders_available_on_sell_side = 'S',
    RPI_orders_available_on_both_sides = 'A',
    No_RPI_orders_available = 'N'
};

enum class direct_listing_with_capital_raise_message_open_eligibility_status {
    Not_Eligible = 'N',
    Eigible = 'Y'
};

// enum class message_type_based_on_big_endian_decoded_length {
//     System_event_message=12,
//     Stock_directory_message= 
// };