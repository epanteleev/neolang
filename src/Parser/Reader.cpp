#include <fstream>
#include "Reader.h"

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

Reader& Reader::expect(const Keyword &keyword) noexcept {
    if (m_match == Reader::ParseStatus::ERROR) {
        return *this;
    }
    match(keyword);
    return *this;
}

Reader &Reader::part(std::string &keyword) noexcept {
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
    for (auto &i: entries) {
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

void Reader::removeSpace() noexcept {
    char ch = getChar();
    while (std::isspace(ch)) {
        ch = getChar();
    }
    ungetChar();
}
