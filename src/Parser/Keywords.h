#pragma once

enum class Keywords : uint8_t {
    NONE = 0,
    DEF,
    IMPORT,
    CLASS,
    OPEN_BRACE,
    CLOSE_BRACE,
    OPEN_PAREN,
    CLOSE_PAREN,
    EQ,
    DOT,
    STAR,
    COLON,
    NEWLINE
};

struct KeywordEntry {
    Keywords value;
    const char *key;
};

static constexpr KeywordEntry entries[] = {
        {Keywords::DEF,         "def"},
        {Keywords::IMPORT,      "import"},
        {Keywords::CLASS,       "class"},
        {Keywords::OPEN_BRACE,  "{"},
        {Keywords::CLOSE_BRACE, "}"},
        {Keywords::OPEN_PAREN,  "("},
        {Keywords::CLOSE_PAREN, ")"},
        {Keywords::NEWLINE, "\n"},
        //Todo
};

constexpr const char *tokToString(Keywords tok) {
    for (auto &i: entries) {
        if (i.value == tok)
            return i.key;
    }
    return "<None>";
}