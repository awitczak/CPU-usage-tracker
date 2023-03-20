cmake_minimum_required(VERSION 3.8)

if(DEFINED ENV{CC})
  set(CMAKE_C_COMPILER $ENV{CC})
endif()

project(CPU_Usage_Tracker VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# If using GCC
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter")
endif()

# If using Clang
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything -Wno-strict-prototypes -Wno-double-promotion -Wno-disabled-macro-expansion -Wno-atomic-implicit-seq-cst -Wno-padded -Wno-declaration-after-statement")
endif()

add_executable(CPU_usage_tracker
    src/main.c
    src/fileread.c
    src/analyzer.c
    src/rb_queue.c
    src/mpsc_queue.c
    src/logger.c
)

target_include_directories(CPU_usage_tracker PRIVATE
    src
    inc
)

set_property(TARGET CPU_usage_tracker PROPERTY C_STANDARD 11)

include(CTest)
enable_testing()

add_executable(CPU_usage_tracker_test 
    tests/test1.c
    src/fileread.c
)

target_include_directories(CPU_usage_tracker_test PRIVATE
    src
    inc
)

add_test(NAME CPU_usage_tracker_test COMMAND $<TARGET_FILE:CPU_usage_tracker_test>)