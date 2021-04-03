#pragma once

#include <cstdint>
#include <string>
#include <tuple>

#include "Keywords.h"

// Todo: Change std::string to ObjString.
class Reader final {
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
        m_pos += 1;
        return m_buffer[m_currPos++];
    }

    inline char peek() noexcept {
        return m_buffer[m_currPos];
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

    Reader& expect(const Keywords &keyword);

    Reader& expectId(std::string &id);

    bool match(Keywords keyword) noexcept;
private:

    inline void ungetChar() noexcept {
        unget(1);
    }

    inline void unget(size_t offset) noexcept {
        m_currPos -= offset;
        m_pos -= offset;
    }

    inline void removeSpace() noexcept;

    std::tuple<std::size_t, Keywords> parseKeyword();

    inline Keywords getTok() {
        return std::get<1>(parseKeyword());
    }

private:
    std::string m_buffer{};
    std::size_t m_line{};
    std::size_t m_pos{};
    Keywords m_currTok{};
    size_t m_currPos{};
};
