#pragma once

#include <list>
#include <memory>

#include "Objects/Object.h"
#include "Objects/ObjMethod.h"
#include "Objects/SymbolTable.h"
#include "Objects/ObjModuleBase.h"

class ObjModule final : public ObjModuleBase {
public:
    explicit ObjModule(const ObjStringLiteral &moduleName) : ObjModuleBase(moduleName) {}

    ObjModule(ObjModule &) = delete;
    ~ObjModule() override = default;

    inline void addField(const ObjStringLiteral &fieldName, Value defaultValue) noexcept {
        ASSERT(m_fields.find(fieldName) != m_fields.end(),
               "Field is exist yet...");
        m_fields.insert(std::make_pair(fieldName, defaultValue));
    }

    void addMethod(std::unique_ptr<ObjMethod> &method) noexcept {
        m_methods.push_back(std::move(method));
    }

    inline void registerConstants(StringBuffer& strings) noexcept {
        m_constantStrings = std::move(strings);
    }

    inline void addStringConstant(std::string& str) noexcept {
        m_constantStrings.push_back(std::move(str));
    }

    inline size_t sizeStringPool() const noexcept {
        return m_constantStrings.size();
    }

    [[nodiscard]]
    inline const ObjStringLiteral * findString(size_t idx) const noexcept {
        if (m_constantStrings.size() <= idx) {
            return nullptr;
        } else {
            return &m_constantStrings[idx];
        }
    }

public:
    static std::unique_ptr<ObjModule> make(const ObjStringLiteral &moduleName) noexcept {
        return std::move(std::make_unique<ObjModule>(moduleName));
    }

public: // todo make private
    StringBuffer m_constantStrings{};
    std::map<ObjStringLiteral, Value> m_fields{};
};
