#pragma once
#include <memory>
#include <filesystem>

#include "Parser/Reader.h"
#include "Vm/Vm.h"

class Parser {
public:
    static bool parse(Vm &vm, const std::filesystem::path &path) noexcept;
};