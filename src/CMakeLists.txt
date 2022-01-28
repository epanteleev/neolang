cmake_minimum_required(VERSION 3.7)
project(neolang)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(.)

file(GLOB OBJECTS_SOURCES Objects/*.cpp Objects/Module/*.cpp Objects/Method/*.cpp)
file(GLOB OBJECTS_HEADERS Objects/*.h Objects/Module/*.h Objects/Method/*.h)

file(GLOB INTERPRETER_SOURCES Interpreter/*.cpp)
file(GLOB INTERPRETER_HEADERS Interpreter/*.h)

file(GLOB VM_SOURCES Vm/*.cpp Vm/Allocator/*.cpp)
file(GLOB VM_HEADERS Vm/*.h Vm/Allocator/*.h)

file(GLOB MODULES_SOURCES Modules/*.cpp )
file(GLOB MODULES_HEADERS Modules/*.h)

file(GLOB PARSER_SOURCES Parser/*.cpp)
file(GLOB PARSER_HEADERS Parser/*.h)

set(ALL ${OBJECTS_SOURCES} ${OBJECTS_HEADERS}
        ${INTERPRETER_SOURCES} ${INTERPRETER_HEADERS}
        ${VM_SOURCES} ${VM_HEADERS}
        ${MODULES_SOURCES} ${MODULES_HEADERS}
        ${PARSER_SOURCES} ${PARSER_HEADERS}
        )

add_executable(${PROJECT_NAME} main.cpp ${ALL})

add_executable(lexer-test unittests/testLexer.cpp ${ALL})
add_executable(buff-test unittests/testBuffer.cpp ${ALL})

enable_testing()

add_test(NAME "lexer test" COMMAND lexer-test)
