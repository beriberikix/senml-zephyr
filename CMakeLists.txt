cmake_minimum_required(VERSION 3.20.5)

# Define the module name and its sources
zephyr_include_directories(include)
zephyr_library()
zephyr_library_sources(src/senml_codec.c)

# Include Kconfig
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/zephyr)

# Include samples
add_subdirectory(samples/json_senml)
add_subdirectory(samples/cbor_senml)