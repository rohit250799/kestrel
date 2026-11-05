cmake_minimum_required(VERSION 3.23)
project(Kestrel LANGUAGES CXX)

add_executable(kestrel main.cpp)

target_link_libraries(kestrel PRIVATE
    itch_stat
)

