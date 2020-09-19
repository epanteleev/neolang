cmake_minimum_required(VERSION 3.17)
project(neolang)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

file(GLOB OBJECTS_SOURCES Objects/*.cpp)
file(GLOB OBJECTS_HEADERS Objects/*.h)

file(GLOB INTERPRETER_SOURCES Interpreter/*.cpp)
file(GLOB INTERPRETER_HEADERS Interpreter/*.h)

file(GLOB VM_SOURCES Vm/*.cpp)
file(GLOB VM_HEADERS Vm/*.h)

file(GLOB MODULES_SOURCES Modules/*.cpp)
file(GLOB MODULES_HEADERS Modules/*.h)

add_executable(neolang main.cpp ${OBJECTS_SOURCES} ${OBJECTS_HEADERS}
        ${INTERPRETER_SOURCES} ${INTERPRETER_HEADERS}
        ${VM_SOURCES} ${VM_HEADERS}
        ${MODULES_SOURCES} ${MODULES_HEADERS})

add_executable(parser ${OBJECTS_SOURCES} ${OBJECTS_HEADERS}
        ${INTERPRETER_SOURCES} ${INTERPRETER_HEADERS}
        ${VM_SOURCES} ${VM_HEADERS}
        ${MODULES_SOURCES} ${MODULES_HEADERS}
        Parser/Parser.cpp Parser/Parser.h Parser/main.cpp)