cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 14)
project(mstt)

IF (IS_ANDROID)
    MESSAGE(STATUS "mstt project build on android")

    include_directories(src)
    include_directories(includes)
    file(GLOB_RECURSE SOURCE_LIST src/*.cpp)
    MESSAGE(STATUS "SOURCE LIST: " ${SOURCE_LIST})
    MESSAGE(STATUS "ANDROID SOURCE LIST: " ${ANDROID_SOURCE_LIST})

    add_library(mstt ${SOURCE_LIST})

ELSE ()
    MESSAGE(STATUS "mstt project build on other platform rather than android")
    add_definitions(-DPLOT)

    include_directories(src)
    include_directories(includes)
    file(GLOB_RECURSE SOURCE_LIST src/*.cpp)
    MESSAGE(STATUS "SOURCE LIST: " ${SOURCE_LIST})

    add_library(mstt SHARED ${SOURCE_LIST})
    add_executable(main ${SOURCE_LIST} src/utils/utils.hpp src/utils/utils.cpp)
    add_subdirectory(Google_tests)

    target_link_libraries(main SDL2 SDL2_image SDL2_ttf SDL2_gfx)

ENDIF ()
