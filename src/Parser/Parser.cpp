#include "Parser.h"

#include <antlr4-runtime.h>
#include "generated/GrammarLexer.h"
#include "generated/GrammarParser.h"
#include "VisitorImpl.h"

void Parser::parse(const std::filesystem::path &path) {
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
    VisitorImpl visitor;
    visitor.visitCompilationUnit(tree);
}
