#pragma once
#include <memory>
#include <filesystem>
#include <utility>
#include <Vm/Vm.h>

class NewParser {
public:
    static std::unique_ptr<Vm> parse(const std::filesystem::path &path);
};
