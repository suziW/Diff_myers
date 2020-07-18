cmake_minimum_required(VERSION 3.16)
project(mstt)
set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(includes)
file(GLOB_RECURSE SOURCE_LIST src/*.cpp)

add_library(mstt SHARED ${SOURCE_LIST})
add_executable(main ${SOURCE_LIST})
add_subdirectory(Google_tests)

target_link_libraries(main SDL2 SDL2_image SDL2_ttf)
