cmake_minimum_required(VERSION 3.17)
project(neolang)

set(CMAKE_CXX_STANDARD 20)
include_directories(Vm Objects)
add_executable(neolang main.cpp Vm/Value.h Vm/OpCode.h Vm/Vm.cpp Vm/Vm.h Objects/ObjMethod.h Interpreter/Interpret.cpp Interpreter/Interpret.h Vm/ApiStack.h Vm/TypeCheck.h Vm/Instruction.h Vm/Common.h Vm/Context.cpp Vm/Context.h Objects/Object.cpp Objects/Object.h Objects/ObjString.h Objects/ObjFrwd.h Objects/SymbolTable.h Objects/ObjModule.cpp Objects/ObjModule.h Parser/Parser.cpp Parser/Parser.h)