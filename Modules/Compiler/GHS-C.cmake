include(Compiler/GHS)

set(CMAKE_C_VERBOSE_FLAG "-v")
set(CMAKE_C_OUTPUT_EXTENSION ".o")

set(CMAKE_C_FLAGS_INIT "")
set(CMAKE_C_FLAGS_DEBUG_INIT "-Odebug -g")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT "-Ospace")
set(CMAKE_C_FLAGS_RELEASE_INIT "-O")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O -g")

set(CMAKE_C_GHS_KERNEL_FLAGS_DEBUG_INIT "-ldebug ${CMAKE_C_FLAGS_DEBUG_INIT}")
set(CMAKE_C_GHS_KERNEL_FLAGS_MINSIZEREL_INIT "${CMAKE_C_FLAGS_MINSIZEREL_INIT}")
set(CMAKE_C_GHS_KERNEL_FLAGS_RELEASE_INIT "${CMAKE_C_FLAGS_RELEASE_INIT}")
set(CMAKE_C_GHS_KERNEL_FLAGS_RELWITHDEBINFO_INIT
  "-ldebug ${CMAKE_C_FLAGS_RELWITHDEBINFO_INIT}")

if(NOT CMAKE_NOT_USING_CONFIG_FLAGS)
  set (CMAKE_C_GHS_KERNEL_FLAGS_DEBUG "${CMAKE_C_GHS_KERNEL_FLAGS_DEBUG_INIT}"
    CACHE STRING "Kernel flags used by the compiler during debug builds.")
  set (CMAKE_C_GHS_KERNEL_FLAGS_MINSIZEREL
    "${CMAKE_C_GHS_KERNEL_FLAGS_MINSIZEREL_INIT}" CACHE STRING
    "Kernel flags used by the compiler during release builds for minimum size.")
  set (CMAKE_C_GHS_KERNEL_FLAGS_RELEASE
    "${CMAKE_C_GHS_KERNEL_FLAGS_RELEASE_INIT}"
    CACHE STRING "Kernel flags used by the compiler during release builds.")
  set (CMAKE_C_GHS_KERNEL_FLAGS_RELWITHDEBINFO
    "${CMAKE_C_GHS_KERNEL_FLAGS_RELWITHDEBINFO_INIT}" CACHE STRING
    "Kernel flags used by the compiler during release builds with debug info.")
endif()
