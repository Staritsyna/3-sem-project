cmake_minimum_required(VERSION 3.10)
project(fields VERSION 1.0)


find_package(ROOT REQUIRED)
find_package(ROOT CONFIG REQUIRED)

include_directories(${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARY_DIR})

set(SOURCES  "read_exp.cpp;plot_trace.cpp;input.cpp" )
set(HEADERS "read_exp.h;plot_trace.h;input.h")

add_executable(main_file main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(main_file ${ROOT_LIBRARIES})


