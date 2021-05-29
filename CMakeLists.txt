
cmake_minimum_required (VERSION 3.10)

project (KLIB_TEST)

if (NOT CMAKE_BUILD_TYPE)
set (CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

include (cmake/cmake-flags.cmake)

message (STATUS ${CMAKE_SYSTEM})

# include_directories ("${PROJECT_SOURCE_DIR}/klib")

add_subdirectory (klib)

# test kstring
add_executable (kstring test/test_kstring.c)
target_link_libraries (kstring klib)

# test kvec
add_executable (kvec test/test_kvec.cpp)
target_link_libraries (kvec klib)

# test klist
add_executable (klist test/test_klist.c)
target_link_libraries (klist klib)

# test ksort
add_executable (ksort test/test_ksort.c)
target_link_libraries (ksort klib)
