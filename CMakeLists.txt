cmake_minimum_required(VERSION 3.0.0)
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

set_property(TARGET CPU_Usage_Tracker PROPERTY C_STANDARD 99)