cmake_minimum_required(VERSION 3.7)
project(neolang)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

set(ANTLR_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/../tools/antlr-4.9.1-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(GrammarParser ${PROJECT_SOURCE_DIR}/Parser/grammar/Grammar.g4 VISITOR OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/generated/)

# add our project source directories
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/generated/)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

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

file(GLOB PARSER_SOURCES Parser/*.cpp )
file(GLOB PARSER_HEADERS Parser/*.h )

add_executable(${PROJECT_NAME} main.cpp ${OBJECTS_SOURCES} ${OBJECTS_HEADERS}
        ${INTERPRETER_SOURCES} ${INTERPRETER_HEADERS}
        ${VM_SOURCES} ${VM_HEADERS}
        ${MODULES_SOURCES} ${MODULES_HEADERS}
         ${PARSER_SOURCES} ${PARSER_HEADERS}
        ${ANTLR_GrammarParser_CXX_OUTPUTS}
        )

target_link_libraries(${PROJECT_NAME} antlr4_static ${SYSTEM_LIBS})
