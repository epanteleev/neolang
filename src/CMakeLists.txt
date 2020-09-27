cmake_minimum_required(VERSION 3.17)
project(neolang)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(.)

file(GLOB OBJECTS_SOURCES Objects/*.cpp)
file(GLOB OBJECTS_HEADERS Objects/*.h)

file(GLOB INTERPRETER_SOURCES Interpreter/*.cpp)
file(GLOB INTERPRETER_HEADERS Interpreter/*.h)

file(GLOB VM_SOURCES Vm/*.cpp)
file(GLOB VM_HEADERS Vm/*.h)

file(GLOB MODULES_SOURCES Modules/*.cpp)
file(GLOB MODULES_HEADERS Modules/*.h)

file(GLOB PARSER_SOURCES Parser/*.cpp)
file(GLOB PARSER_HEADERS Parser/*.h)

add_executable(${PROJECT_NAME} main.cpp ${OBJECTS_SOURCES} ${OBJECTS_HEADERS}
        ${INTERPRETER_SOURCES} ${INTERPRETER_HEADERS}
        ${VM_SOURCES} ${VM_HEADERS}
        ${MODULES_SOURCES} ${MODULES_HEADERS}
        ${PARSER_SOURCES} ${PARSER_HEADERS}
        Vm/Allocator/Allocator.cpp Vm/Allocator/Allocator.h Vm/Allocator/Collector.cpp Vm/Allocator/Collector.h)