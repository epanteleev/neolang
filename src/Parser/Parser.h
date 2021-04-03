#pragma once
#include <memory>
#include <filesystem>
#include <utility>
#include <Vm/Vm.h>

#include "Reader.h"

class LabelBuffer;

class ParseError: std::exception {
public:
    explicit ParseError(std::string message):
        m_message(std::move(message)) {}

    [[nodiscard]]
    const char * what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class Parser final {
public:

    static std::unique_ptr<Vm> parse(const std::filesystem::path &path);

private:
    Parser(const std::filesystem::path &path, Vm &vm);
    ~Parser() = default;

private:
    bool parseModule();

    bool parseMethod(ObjModule &module);

    InstructionList parseInstructions(LabelBuffer& labels);

    std::string parseLabel();

    Instruction parseCallStatic();

private:
    Reader reader;
    Vm &m_vm;
};