cmake_minimum_required(VERSION 3.25...4.2.3)
project(KestrelProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(utils_library cpp/utils/file_functions.cpp)
target_include_directories(utils_library PUBLIC cpp/utils/include)

add_library(itch_stat_library cpp/itch_stat/src/itch_stat_json.cpp)
target_include_directories(itch_stat_library PUBLIC cpp/itch_stat/include)
target_link_libraries(itch_stat_library PRIVATE utils_library)

add_library(itch_filter_library cpp/itch_filter/src/itch_filter.cpp)
target_include_directories(itch_filter_library PUBLIC cpp/itch_filter/include)
target_link_libraries(itch_filter_library PRIVATE utils_library)

add_executable(kestrel cpp/src/main.cpp)
target_link_libraries(kestrel
    PUBLIC
        utils_library
    PRIVATE
        itch_stat_library
        itch_filter_library
)
