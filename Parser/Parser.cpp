#include "Parser.h"
#include <fstream>

#include "Vm/Vm.h"

// Returns true if [c] is a valid (non-initial) identifier character.
inline static bool isName(char c) noexcept {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

// Returns true if [c] is a digit.
inline static bool isDigit(char c) noexcept {
    return c >= '0' && c <= '9';
}

Reader& Reader::expect(const Keyword &keyword) noexcept {
    if (m_match == Reader::ParseStatus::ERROR) {
        return *this;
    }
    match(keyword);
    return *this;
}

Reader & Reader::part(std::string &keyword) noexcept {
    if (m_match != Reader::ParseStatus::SUCCESS) {
        return *this;
    }
    const auto word = getWord();
    if (word.empty()) {
        m_match = Reader::ParseStatus::ERROR;
    } else {
        keyword = word;
    }
    return *this;
}

bool Reader::open(const std::string &fileName) noexcept {
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        return false;
    }
    std::string line;
    while (file) {
        std::getline(file, line);
        m_buffer += line;
    }
    file.close();
    return true;
}

std::string Reader::getWord() noexcept {
    removeSpace();
    char ch = getChar();
    std::string str;
    while (isName(ch) || isDigit(ch)) {
        str += ch;
        ch = getChar();
    }
    ungetChar();
    return str;
}

bool matchChar(char ch, Keyword keyword) noexcept {
    switch (ch) {
        case '(': return keyword == Keyword::OPEN_PAREN;
        case ')': return keyword == Keyword::CLOSE_PAREN;
        case '{': return keyword == Keyword::OPEN_BRACE;
        case '}': return keyword == Keyword::CLOSE_BRACE;
        case '.': return keyword == Keyword::DOT;
        case '*': return keyword == Keyword::STAR;
        case '=': return keyword == Keyword::EQ;
        case ':': return keyword == Keyword::COLON;
        default: return false;
    }
}

bool matchWord(std::string& string, Keyword keyword) noexcept {
    for (auto &i: stringKeywords) {
        if (i.key == string)
            return keyword == i.value;
    }
    return false;
}

bool Reader::match(Keyword keyword) noexcept {
    removeSpace();
    char ch = getChar();
    if (matchChar(ch, keyword)) {
        m_match = Reader::ParseStatus::SUCCESS;
        return true;
    }
    ungetChar();
    if (!isName(ch)) {
        m_match = Reader::ParseStatus::NO_MATCH;
        return false;
    }
    std::string word = getWord();
    if (matchWord(word, keyword)) {
        m_match = Reader::ParseStatus::SUCCESS;
        return true;
    } else {
        m_match = Reader::ParseStatus::NO_MATCH;
        unget(word.size());
        return false;
    }
}

char Reader::getChar() noexcept {
    char ch = m_buffer[m_currPos];
    m_currPos++;
    return ch;
}

void Reader::ungetChar() noexcept {
    m_currPos--;
}

void Reader::unget(size_t offset) noexcept {
    m_currPos -= offset;
}

float Reader::getFloat() noexcept {
    return std::stof(getWord());
}

uint32_t Reader::getInt() noexcept {
    return std::stoi(getWord());
}

void Reader::removeSpace() noexcept {
    char ch = getChar();
    while (std::isspace(ch)) {
        ch = getChar();
    }
    ungetChar();
}

static bool parseInsts(ObjModule &module, ObjMethod &method, Reader &reader) noexcept {
    std::string instName = reader.getWord();
    while (!instName.empty()) {
        if (instName == iPUSH) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::iPUSH, Value(i)));
        } else if (instName == iADD) {
            method.addInst(Instruction(OpCode::iADD));
        } else if (instName == iSUB) {
            method.addInst(Instruction(OpCode::iSUB));
        } else if (instName == iMUL) {
            method.addInst(Instruction(OpCode::iMUL));
        } else if (instName == CALLSTATIC) {
            std::string className, methodName;
            reader.part(className)
                .expect(Keyword::COLON)
                .expect(Keyword::COLON)
                .part(methodName);
            if (!reader.success()) {
                return false;
            }
            module.addStringConstant(className);
            module.addStringConstant(methodName);
            size_t size = module.sizeStringPool();
            method.addInst(Instruction(OpCode::CALLSTATIC, Value((int)size - 2), Value((int)size - 1)));
        } else if (instName == RET) {
            method.addInst(Instruction(OpCode::RET));
        } else {
            UNREACHABLE();
        }
        instName = reader.getWord();
    }
    return true;
}

static bool parseMethod(ObjModule &module, Reader &reader) noexcept {
    std::string methodName;
    reader.expect(Keyword::DEF)
        .part(methodName)
        .expect(Keyword::EQ)
        .expect(Keyword::OPEN_BRACE);
    if (reader.error()) {
        return false;
    } else if (reader.noMatch()) {
        return true;
    }
    auto method = ObjMethod::make(module, methodName);
    parseInsts(module, *method, reader);
    module.addMethod(method);
    reader.expect(Keyword::CLOSE_BRACE);
    if (!reader.success()) {
        return false;
    }
    return true;
}

static bool parseModule(Vm &vm, Reader &reader) noexcept {
    std::string className;
    reader.expect(Keyword::CLASS).part(className).expect(Keyword::OPEN_BRACE);
    if (reader.error()) {
        return false;
    }
    auto module = ObjModule::make(className);
    while (!reader.noMatch()) {
        parseMethod(*module, reader);
    }
    reader.expect(Keyword::CLOSE_BRACE);
    if (reader.error()) {
        return false;
    }
    vm.addModule(module);
    return true;
}

Parser::Parser(const std::string &path) noexcept:
        m_reader(std::make_unique<Reader>()) {
    m_reader->open(path);
}

std::unique_ptr<Vm> Parser::apply() noexcept {
    auto vm = std::make_unique<Vm>();
    ASSERT(parseModule(*vm, *m_reader), "pipets");
    return vm;
}
