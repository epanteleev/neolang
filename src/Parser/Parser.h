#pragma once
#include <memory>
#include <filesystem>

#include "Parser/Reader.h"
#include "Vm/Vm.h"

class Parser {
public:
    explicit Parser(const std::filesystem::path& path) noexcept;

    std::unique_ptr<Vm> apply() noexcept;

private:
    std::unique_ptr<Reader> m_reader;
};