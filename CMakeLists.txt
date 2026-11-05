cmake_minimum_required(VERSION 3.25...4.2.3)
project(KestrelProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(itch_stat_library STATIC cpp/itch_stat/src/itch_stat_json.cpp)
target_include_directories(itch_stat_library PUBLIC cpp/itch_stat/include)

add_executable(kestrel cpp/src/main.cpp)
target_link_libraries(kestrel PRIVATE itch_stat_library)
