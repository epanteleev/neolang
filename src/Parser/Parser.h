#pragma once

#include "Vm/Vm.h"

#include <iostream>
#include <filesystem>
#include "Lexer.h"
#include "Vm/Instruction.h"
#include "Vm/OpCode.h"

class Parser {
public:
    using MethodsList = std::vector<ObjMethod::Pointer>;
    using InstructionList = ::InstructionList;
    using FieldList = ObjModule::Fields;

public:
    explicit Parser(Vm& vm, std::string_view data) :
        lex(data),
        vm(vm) {}

private:
    inline bool expect(OpCode code) {
        return lex.is<detail::lexer::Tok::STRING>(opCodeToString(code));
    }

    template<detail::lexer::Tok tok>
    inline decltype(auto) get(const char *error) {
        if (lex.is<tok>()) {
            return lex.peek<tok>();
        } else {
            throw detail::lexer::LexError(lex, error);
        }
    }

private:
    InstructionList parseInstructions();

    MethodsList parseFunctions();

    FieldList parseFields();

    ObjModule::Pointer parseModule();

public:
    static void parse(Vm& vm, const std::filesystem::path &path);

private:
    detail::lexer::Lexer lex;
    Vm& vm;
};