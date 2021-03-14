#pragma once
#include <memory>
#include <filesystem>
#include <utility>

#include "Parser/Reader.h"
#include "Vm/Vm.h"

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
    explicit Parser(const std::filesystem::path &path);

    ~Parser() = default;

private:
    bool parseModule(Vm &vm);

    bool parseMethod(ObjModule &module);

    InstList parseInstructions(ObjModule &module, LabelBuffer& labels);

    std::string parseLabel();

    Instruction parseCallStatic(ObjModule &module);

private:
    Reader reader;
};