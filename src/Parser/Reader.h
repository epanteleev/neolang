#pragma once

#include <cstdint>
#include <string>

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

struct KeywordEntry {
    Keyword value;
    const char *key;
};

static constexpr KeywordEntry entries[] = {
        {Keyword::DEF,    "def"},
        {Keyword::IMPORT, "import"},
        {Keyword::CLASS,  "class"}
};

// Todo: Change std::string to ObjString.
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
    /**
     * Open (@param fileName)
     * @return false if file wasn't open.
     */
    bool open(const std::string &fileName) noexcept;

    inline char getChar() noexcept {
        return m_buffer[m_currPos++];
    }

    [[nodiscard]]
    std::string getWord() noexcept;

    [[nodiscard]]
    inline float getFloat() noexcept {
        return std::stof(getWord());
    }

    [[nodiscard]]
    inline uint32_t getInt() noexcept {
        return std::stoi(getWord());
    }

    [[nodiscard]]
    inline uint64_t getULong() noexcept {
        return std::stoull(getWord());
    }

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
    inline void reset() noexcept {
        if (m_match == ParseStatus::NO_MATCH) {
            m_match = ParseStatus::SUCCESS;
        }
    }

private:
    bool match(Keyword keyword) noexcept;

    inline void ungetChar() noexcept {
        m_currPos--;
    }

    inline void unget(size_t offset) noexcept {
        m_currPos -= offset;
    }

    inline void removeSpace() noexcept;

private:
    std::string m_buffer{};
    size_t m_currPos{};
    ParseStatus m_match{};
};
