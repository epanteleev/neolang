#pragma once
#include <array>

/**
 * Represent local variable in virtual machine.
 * @author minium2
 */
class Locals final {
private:
    static constexpr size_t MAX_LOCAL_VARS = 4;

public:
    Locals() = default;

    Locals(Locals&) = delete;

    ~Locals() = default;

    Locals operator=(Locals&) = delete;
public:
    forceinline void store(Value val, size_t idx) noexcept {
        ASSERT(idx < MAX_LOCAL_VARS, "Invalid variable index.");
        m_locals[idx] = val;
    }

    [[nodiscard]]
    forceinline Value load(size_t idx) const noexcept {
        ASSERT(idx < MAX_LOCAL_VARS, "Invalid local variables index.");
        return m_locals[idx];
    }

private:
    std::array<Value, MAX_LOCAL_VARS> m_locals;
};
