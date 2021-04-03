#include "NewParser.h"

#include "antlr4-runtime.h"
#include "generated/GrammarLexer.h"
#include "generated/GrammarParser.h"
#include "VisitorImpl.h"

std::unique_ptr<Vm> NewParser::parse(const std::filesystem::path &path) {
    using namespace antlr4;
    std::ifstream stream;
    stream.open(path);
    if (!stream.is_open()) {
        throw std::invalid_argument("File was not opened.");
    }

    ANTLRInputStream input(stream);
    GrammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    GrammarParser parser(&tokens);

    GrammarParser::CompilationUnitContext* tree = parser.compilationUnit();

    auto vm = std::make_unique<Vm>();
    VisitorImpl visitor(*vm);
    visitor.visitCompilationUnit(tree);

    return vm;
}
