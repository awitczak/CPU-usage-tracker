cmake_minimum_required(VERSION 3.8)
project(CPU_Usage_Tracker VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CPU_Usage_Tracker 
    src/main.c
    src/fileread.c
    src/analyzer.c
    src/rb_queue.c
    src/mpsc_queue.c
    src/logger.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(CPU_Usage_Tracker PRIVATE
    src
    inc
)

# If using GCC
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter")
endif()

# If using Clang
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything -Wno-unused-parameter -Wno-double-promotion -Wno-disabled-macro-expansion -Wno-atomic-implicit-seq-cst -Wno-padded -Wno-declaration-after-statement")
endif()

set_property(TARGET CPU_Usage_Tracker PROPERTY C_STANDARD 11)