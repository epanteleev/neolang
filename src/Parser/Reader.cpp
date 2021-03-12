#include <fstream>
#include "Reader.h"
#include "Parser.h"

/**
 * Returns true if [c] is a valid (non-initial) identifier character.
 */
inline static bool isName(char c) noexcept {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

/**
 * Returns true if [c] is a digit.
 */
inline static bool isDigit(char c) noexcept {
    return c >= '0' && c <= '9';
}

Reader& Reader::expect(const Keywords &keyword) {
    if (!match(keyword)) {
        throw ParseError(std::to_string(m_pos) + ":" + std::to_string(m_line) +
        " parse error: expect '" + tokToString(keyword) + "'. found '" + tokToString(getTok()));
    }
    return *this;
}

Reader &Reader::expectId(std::string &id) {
    const auto word = getWord();
    if (!word.empty()) {
        id = word;
    } else {
        throw ParseError(std::to_string(m_pos) + ":" + std::to_string(m_line) + " parse error: expect identifier.");
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
        m_buffer += (line + '\n');// Todo refactor it
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

Keywords getKeyword(char ch) noexcept {
    switch (ch) {
        case '(': return Keywords::OPEN_PAREN;
        case ')': return Keywords::CLOSE_PAREN;
        case '{': return Keywords::OPEN_BRACE;
        case '}': return Keywords::CLOSE_BRACE;
        case '.': return Keywords::DOT;
        case '*': return Keywords::STAR;
        case '=': return Keywords::EQ;
        case ':': return Keywords::COLON;
        default: return Keywords::NONE;
    }
}

Keywords getKeyword(std::string& string) noexcept {
    for (auto &i: entries) {
        if (i.key == string)
            return i.value;
    }
    return Keywords::NONE;
}

std::tuple<std::size_t, Keywords> Reader::parseKeyword() {
    removeSpace();
    char ch = peek();
    auto tok = getKeyword(ch);
    if (tok != Keywords::NONE) {
        getChar();
        return std::make_tuple(1, tok);
    }
    if (ch == '\n') {
        m_line += 1;
        m_pos = 0;
        getChar();
        return std::make_tuple(1, Keywords::NEWLINE);
    }

    std::string word = getWord();
    tok = getKeyword(word);
    if (tok != Keywords::NONE) {
        return std::make_tuple(word.size(), tok);
    } else {
        return std::make_tuple(word.size(), Keywords::NONE);
    }
}

bool Reader::match(Keywords keyword) noexcept {
    auto [pos, tok] = parseKeyword();
    if (tok != keyword) {
        unget(pos);
        return false;
    } else {
        return true;
    }
}

void Reader::removeSpace() noexcept {
    char ch = getChar();
    while (ch == ' ' || ch == '\t') {
        ch = getChar();
    }
    ungetChar();
}
