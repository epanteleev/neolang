#include "Parser.h"
#include <fstream>

void Parser::parse(const std::filesystem::path &path) {
    std::ifstream stream;
    stream.open(path);
    if (!stream.is_open()) {
        throw std::invalid_argument("File was not opened.");
    }

    std::ostringstream s{};
    s << stream.rdbuf();
    auto m = Parser(s.str()).apply();
    Vm::registerModule(std::move(m));
}