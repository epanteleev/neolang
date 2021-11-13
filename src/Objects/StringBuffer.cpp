#include "StringBuffer.h"

struct Node {
    ObjString str;
    Node *next{};

public:
    void destroy() const {
        Node* last = next;
        while (last != nullptr) {
            Node* tmp = last;
            last = last->next;
            delete tmp;
        }
    }

private:
    Node *last(std::uint32_t &pos) noexcept {
        if (next == nullptr) {
            return this;
        }
        pos = 0;
        Node *last = next;
        for (Node *n = next; n != nullptr; n = n->next) {
            last = n;
            pos += 1;
        }
        return last;
    }

public:
    std::size_t append(ObjString &&string) noexcept {
        std::uint32_t pos{};
        Node *l = last(pos);
        l->next = new Node();
        l->str = std::move(string);
        return pos;
    }

    [[nodiscard]]
    Node *findByPos(std::uint32_t pos) const noexcept {
        std::uint32_t count{};
        for (Node *n = const_cast<Node *>(this); n != nullptr; n = n->next) {
            if (count == pos) {
                return n;
            }
            count += 1;
        }
        return nullptr;
    }

    [[nodiscard]]
    std::size_t find(const ObjString &string) const noexcept {
        std::uint32_t count{};
        for (Node *n = const_cast<Node *>(this); n != nullptr; n = n->next) {
            if (string == n->str) {
                return count;
            }
            count += 1;
        }
        return std::numeric_limits<std::uint32_t>::max();
    }
};

StringBuffer::StringBuffer() {
    m_nodes = new Node[INITIAL_LENGTH];
}

StringBuffer::~StringBuffer() {
    for (std::size_t n = 0; n < INITIAL_LENGTH; n++) {
        m_nodes[n].destroy();
    }
    delete[] m_nodes;
}

std::size_t StringBuffer::push(ObjString &&string) noexcept {
    auto idx = string.hash();
    auto pos = m_nodes[mod(idx)]
            .append(std::move(string));

    return makeId(idx, pos);
}

ObjString &StringBuffer::find(std::size_t pos) noexcept {
    std::uint32_t p = ((pos >> 32) & 0xFFFFFFFF);
    std::uint32_t idx = pos & 0xFFFFFFFF;
    Node *node = m_nodes[mod(idx)].findByPos(p);
    ASSERT(node != nullptr, "string buffer error: string doesn't exist");
    return node->str;
}

std::size_t StringBuffer::find(const ObjString &string) noexcept {
    std::uint32_t idx = string.hash();
    std::uint32_t pos = m_nodes[mod(idx)].find(string);
    return makeId(idx, pos);
}