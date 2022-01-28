#pragma once

#include <memory>
#include <vector>
#include "Objects/ObjFrwd.h"
#include "Objects/ObjString.h"

struct Node;

class StringBufferIterator  {
public:
    using reference = ObjString&;

public:
    explicit StringBufferIterator(Node* n) : m_node(n) {
        UNREACHABLE(); // Not implemented yet.
    }

public:
    StringBufferIterator& operator++();

    StringBufferIterator operator++(int);

    bool operator==(StringBufferIterator other) const {
        return m_node == other.m_node;
    }

    bool operator!=(StringBufferIterator other) const {
        return !(*this == other);
    }

    reference operator*() const;

public:
    Node* m_node;
};

/**
 * Map String to index in symbol table.
 */
class StringBuffer final {
public:
    using iterator = StringBufferIterator;

private:
    static const std::size_t INITIAL_LENGTH = 0xFF;

public:
    StringBuffer();

    ~StringBuffer();

public:
    std::size_t push(ObjString &&string) noexcept;

    ObjString &find(std::size_t pos) noexcept;

    std::size_t find(const ObjString &string) noexcept;

public:
    iterator begin() {
        return iterator(m_nodes);
    }

    iterator end();

private:
    static inline std::uint32_t mod(std::uint32_t hash) noexcept {
        return hash % INITIAL_LENGTH;
    }

    static inline std::size_t makeId(std::uint32_t idx, uint32_t pos) noexcept {
        return ((std::size_t) pos << 32) | idx;
    }

private:
    Node *m_nodes{};
};