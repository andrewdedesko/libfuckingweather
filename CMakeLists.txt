cmake_minimum_required (VERSION 2.6)
project (fuckingweather)

include_directories ("${PROJECT_BINARY_DIR}")

# libxml2
find_package (LibXml2)
include_directories ("${LIBXML2_INCLUDE_DIR}")

# curl
find_package (CURL)
include_directories ("${CURL_INCLUDE_DIR}")

# libfuckingweather
add_library (fuckingweather fuckingweather.c)

# test_fuckingweather_conditions
add_executable (test_fuckingweather_conditions test_fuckingweather_conditions.c fuckingweather.c)
target_link_libraries (test_fuckingweather_conditions ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
