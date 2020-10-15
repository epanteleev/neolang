#pragma once
#include <list>

#include <Vm/Value.h>
#include "Vm/Allocator/DefaultAllocator.h"

class RootSet final {
public:
    RootSet() = default;

    ~RootSet() = default;

    RootSet(const RootSet &) = delete;

public:
    inline void addRoot(Value ref) noexcept {
        m_ref.push_front(ref);
    }

    inline void finalize() noexcept {
        for (auto &i: m_ref)
            Allocator::Delete(reinterpret_cast<void *>(i.value()));
        m_ref.clear();
    }

public:
    // Todo: Perhaps this must not singleton.
    static RootSet& set() noexcept {
        static RootSet set;
        return set;
    }

private:
    std::list<Value> m_ref;
};
