#pragma once

#include <list>
#include <memory>

#include "Objects/Object.h"
#include "Objects/ObjMethod.h"
#include "Objects/StringBuffer.h"
#include "Objects/ObjModuleBase.h"

/**
 * Represent module of programming language.
 * @author minium2
 */
class ObjModule final : public ObjModuleBase {
public:
    explicit ObjModule(ObjString moduleName) : ObjModuleBase(std::move(moduleName)) {}

    ObjModule(ObjModule &&module) noexcept:
            ObjModuleBase(module.moduleName()),
            m_constantStrings(std::move(module.m_constantStrings)) {}

    ObjModule(ObjModule &) = delete;

    ~ObjModule() override = default;

public:

    inline void addMethod(std::unique_ptr<ObjMethod> &&method) noexcept {
        method->setModule(this);
        m_methods.push_back(std::move(method));
    }

    inline void addConstants(StringBuffer &&strings) noexcept {
        m_constantStrings = std::move(strings);
    }
    /**
     * Insert given str to string pull.
     * @return position str in string buffer.
     */
    inline size_t addStringConstant(ObjString &&str) noexcept {
        m_constantStrings.push_back(std::move(str));
        return m_constantStrings.size() - 1;
    }

    [[nodiscard]]
    inline size_t sizeStringPool() const noexcept {
        return m_constantStrings.size();
    }

    [[nodiscard]]
    inline const ObjString *findString(size_t idx) const noexcept {
        if (m_constantStrings.size() <= idx) {
            return nullptr;
        } else {
            return &m_constantStrings[idx];
        }
    }

public:
    static std::unique_ptr<ObjModule> make(ObjString moduleName) noexcept {
        return std::make_unique<ObjModule>(std::move(moduleName));
    }

private:
    StringBuffer m_constantStrings{};
};
