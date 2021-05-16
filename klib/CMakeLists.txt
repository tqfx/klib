
cmake_minimum_required (VERSION 3.0)

project (KLIB)

include (cmake-flags.cmake)

aux_source_directory(. SRC_KLIB)

add_library(klib STATIC ${SRC_KLIB})

