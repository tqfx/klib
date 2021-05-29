
cmake_minimum_required (VERSION 3.10)

project (KLIB)

include (../cmake/cmake-flags.cmake)

aux_source_directory(. SOURCE_KLIB)

add_library(klib STATIC ${SOURCE_KLIB})

target_include_directories(klib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

