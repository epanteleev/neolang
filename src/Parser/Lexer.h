#pragma once

#include <string>
#include <array>
#include <cassert>
#include <vector>
#include <format>
#include "Vm/eternal.h"

namespace detail::lexer {

    enum class Tok : char {
        STRING = 0,
        INTEGER,
        UINTEGER,
        FLOAT,
        OPEN_PAREN = '(',
        CLOSE_PAREN = ')',
        OPEN_BRACE = '{',
        CLOSE_BRACE = '}',
        COMMA = ',',
        POINT = '.',
        OPEN_SQUARE_BRACKET = '[',
        CLOSE_SQUARE_BRACKET = ']',
        STRING_LITERAL,
        DOLLAR = '$',
        SEMICOLON = ';',
        COLON = ':',
        SLASH = '/',
        EQUALITY = '=',
        // Keywords
        CLASS,
        DEF,
        VAL,
        FIELD,
    };

    template<Tok t>
    concept is_keyword = (t == Tok::CLASS || t == Tok::DEF || t == Tok::VAL || t == Tok::FIELD);

    namespace keyword {
        static constexpr const char *CLASS = "class";
        static constexpr const char *DEF   = "def";
        static constexpr const char *VAL   = "val";
        static constexpr const char *FIELD = "field";
    }

    struct hash {
        constexpr std::size_t operator()(const Tok& t) const {
            return static_cast<std::size_t>(t);
        }
    };

    constexpr const auto keywordMap = constexpression::hash_map<Tok, constexpression::eternal::string, hash> ({
              {Tok::DEF, keyword::DEF},
              {Tok::CLASS, keyword::CLASS},
              {Tok::VAL, keyword::VAL},
              {Tok::FIELD, keyword::FIELD}
    });

    class Lexer final {
    public:
        using iterator = const char *;

    public:
        explicit Lexer(std::string_view string) :
                m_pos(string.data()),
                m_end(string.data() + string.length()),
                m_lineBegin(string.data()),
                m_lineCount(1)
                {}

    private:

        static inline bool isSpace(iterator p) {
            return *p == ' ' || *p == '\n' || *p == '\t' || *p == '\0';
        }

        [[nodiscard]]
        iterator findStringEnd() const noexcept;

        std::string getString(iterator &it) const;

        std::int64_t getInteger();

        std::size_t getUinteger();

        bool checkDigits(iterator it) const;

        [[nodiscard]]
        bool isInteger() const;

        [[nodiscard]]
        bool isUinteger() const;

        [[nodiscard]]
        bool isFloat() const;

        [[nodiscard]]
        iterator findLiteralEnd() const;

        inline bool checkStringLiteral() {
            return *m_pos == '"';
        }

        std::string getStringLiteral();

        inline void get() noexcept {
            assert(!eof());
            m_pos++;
        }

        bool isDelimiter(iterator pos) const;

        bool check(iterator keyword);

        float getFloat();
    public:
        template<Tok t>
        [[nodiscard]]
        inline bool is() noexcept {
            if (*m_pos == static_cast<char>(t)) {
                get();
                return true;
            } else {
                return false;
            }
        }

        template<Tok t>
        requires (t == Tok::STRING)
        [[nodiscard]]
        inline bool is() noexcept {
            return std::isalnum(*m_pos);
        }

        template<Tok t>
        requires (t == Tok::STRING)
        [[nodiscard]]
        constexpr inline bool is(iterator str) {
            return check(str);
        }

        template<Tok t>
        requires (t == Tok::INTEGER)
        [[nodiscard]]
        inline bool is() noexcept {
            return isInteger();
        }

        template<Tok t>
        requires (t == Tok::UINTEGER)
        [[nodiscard]]
        inline bool is() noexcept {
            return isUinteger();
        }

        template<Tok t>
        requires (t == Tok::FLOAT)
        [[nodiscard]]
        inline bool is() noexcept {
            return isFloat();
        }

        template<Tok t>
        requires (t == Tok::STRING_LITERAL)
        [[nodiscard]]
        inline bool is() noexcept {
            return *m_pos == '"';
        }

        template<Tok t>
        requires is_keyword<t>
        [[nodiscard]]
        constexpr inline bool is() {
            return check(keywordMap.find(t)->second.c_str());
        }

        template<Tok t>
        requires (t == Tok::STRING)
        inline decltype(auto) peek() {
            assert(is<Tok::STRING>());
            assert(!eof());
            return getString(m_pos);
        }

        template<Tok t>
        requires (t == Tok::INTEGER)
        inline decltype(auto) peek() {
            assert(is<Tok::INTEGER>());
            assert(!eof());
            return getInteger();
        }

        template<Tok t>
        requires (t == Tok::UINTEGER)
        inline decltype(auto) peek() {
            assert(is<Tok::UINTEGER>());
            return getUinteger();
        }

        template<Tok t>
        requires (t == Tok::FLOAT)
        inline decltype(auto) peek() {
            assert(is<Tok::FLOAT>());
            return getFloat();
        }

        template<Tok t>
        requires (t == Tok::STRING_LITERAL)
        inline decltype(auto) peek() {
            assert(is<Tok::STRING_LITERAL>());
            return getStringLiteral();
        }

        inline bool skipSpaces() {
            auto pos = m_pos;
            while (pos != m_end && isSpace(pos)) {
                if (*pos == '\n') {
                    m_lineCount++;
                    m_lineBegin = pos + 1;
                }
                pos++;
            }
            m_pos = pos;
            return true;
        }

        void skipComment() {
            while (*m_pos != '\n') {
                m_pos++;
            }
            m_lineCount++;
            m_pos++;
            m_lineBegin = m_pos;
        }

        [[nodiscard]]
        inline bool eof() const noexcept {
            return m_pos == m_end;
        }

        [[nodiscard]]
        inline std::size_t lines() const noexcept {
            return m_lineCount;
        }

        [[nodiscard]]
        inline std::size_t pos() const noexcept {
            return m_pos - m_lineBegin;
        }

        [[nodiscard]]
        std::string message() const noexcept {
            return std::format("{}:{} '{}'", lines(), pos(), std::string(m_pos, m_end));
        }

    private:
        iterator m_pos;
        iterator m_end;
        std::size_t m_lineCount{};
        iterator m_lineBegin{};
    };

    class LexError : public std::exception {
    public:
        LexError(Lexer &lex, std::string_view text) :
                message(std::format("in {} {}", lex.message(), text)) {}

    public:
        [[nodiscard]]
        char const *what() const override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}