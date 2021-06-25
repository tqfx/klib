# include compiler flag check
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

# compiler is gnu or clang
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

  # C check -Wno-cast-qual
  check_c_compiler_flag(-Wno-cast-qual FLAG_SUPPORTED_Wno-cast-qual)
  if(FLAG_SUPPORTED_Wno-cast-qual)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-cast-qual")
  endif(FLAG_SUPPORTED_Wno-cast-qual)
  # C++ check -Wno-cast-qual
  check_cxx_compiler_flag(-Wno-cast-qual FLAG_SUPPORTED_Wno-cast-qual)
  if(FLAG_SUPPORTED_Wno-cast-qual)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-qual")
  endif(FLAG_SUPPORTED_Wno-cast-qual)

endif("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
      "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
      "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
      "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
