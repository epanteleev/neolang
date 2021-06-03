#pragma once
#include <memory>
#include <filesystem>
#include <utility>
#include <Vm/Vm.h>

/**
 * Parse input file and initialize virtual machine.
 *
 * @throw std::invalid_argument if file wasn't open.
 * @author minium2
 */
class Parser {
public:
    static void parse(const std::filesystem::path &path);
};
