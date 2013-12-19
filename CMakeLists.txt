cmake_minimum_required (VERSION 2.6)
project (fuckingweather)

include_directories ("${PROJECT_BINARY_DIR}")

## TODO  Don't hardcode libxml2 include directory
include_directories (/usr/include/libxml2)

set (CMAKE_C_FLAGS, "-ggdb")

# libfuckingweather
add_library (fuckingweather fuckingweather.c)

# test_fuckingweather_conditions
add_executable (test_fuckingweather_conditions test_fuckingweather_conditions.c fuckingweather.c)
target_link_libraries (test_fuckingweather_conditions curl xml2)

