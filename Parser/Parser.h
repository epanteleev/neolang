#pragma once
#include <memory>
#include <iosfwd>
#include <stack>
#include <fstream>

#include "Vm/Instruction.h"
#include "Objects/ObjFrwd.h"

enum class Keyword : uint8_t {
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
    NONE
};

struct StrKeyword {
    Keyword value;
    const char *key;
};

static constexpr StrKeyword stringKeywords[] = {
        {Keyword::DEF,    "def"},
        {Keyword::IMPORT, "import"},
        {Keyword::CLASS,  "class"}
};

class Reader final {
public:
    enum class ParseStatus: uint8_t {
        NO_MATCH,
        ERROR,
        SUCCESS
    };

public:
    Reader() = default;

    ~Reader() = default;

    Reader(Reader &) = delete;

public:
    bool open(const std::string &fileName) noexcept;

    char getChar() noexcept;

    [[nodiscard]]
    inline std::string getWord() noexcept;

    [[nodiscard]]
    inline float getFloat() noexcept;

    [[nodiscard]]
    inline uint32_t getInt() noexcept;

    bool match(Keyword keyword) noexcept;

    Reader& expect(const Keyword &keyword) noexcept;

    Reader& part(std::string &keyword) noexcept;

    [[nodiscard]]
    inline bool noMatch() const noexcept {
        return m_match == ParseStatus::NO_MATCH;
    }

    [[nodiscard]]
    inline bool success() const noexcept {
        return m_match == ParseStatus::SUCCESS;
    }

    [[nodiscard]]
    inline bool error() const noexcept {
        return m_match == ParseStatus::ERROR;
    }

private:
    inline void ungetChar() noexcept;

    inline void unget(size_t offset) noexcept;

    inline void removeSpace() noexcept;

private:
    friend Reader &operator>>(Reader &reader, std::string &keyword) noexcept;

private:
    std::string m_buffer;
    size_t m_currPos;
    ParseStatus m_match;

};


class Parser {
public:
    explicit Parser(const std::string& path) noexcept;

    std::unique_ptr<Vm> apply() noexcept;

private:
    std::unique_ptr<Reader> m_reader;
};