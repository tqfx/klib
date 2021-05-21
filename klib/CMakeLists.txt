
cmake_minimum_required (VERSION 3.0)

project (KLIB)

include (cmake-flags.cmake)

aux_source_directory(. SOURCE_KLIB)

add_library(klib STATIC ${SOURCE_KLIB})

