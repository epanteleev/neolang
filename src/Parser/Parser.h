#pragma once
#include <memory>
#include <filesystem>
#include <utility>

#include "Parser/Reader.h"
#include "Vm/Vm.h"

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

class Parser {
public:
    static std::unique_ptr<Vm> parse(const std::filesystem::path &path);
};