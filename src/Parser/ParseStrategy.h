#pragma once
#include "Parser.h"

class ParseStrategy final {
public:
    static void useNewParser() {
        isNew = true;
    }

    static std::unique_ptr<Vm> parse(const std::filesystem::path &path) {
        if (isNew) {
            throw std::runtime_exception("unreached");
        }
        return Parse::parse(path);
    }

private:
    static bool isNew;
};
