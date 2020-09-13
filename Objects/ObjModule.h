#pragma once

#include <list>
#include <memory>

#include "Objects/Object.h"
#include "Objects/ObjMethod.h"
#include "Objects/SymbolTable.h"
#include "Objects/ObjModuleBase.h"

class ObjModule final : public ObjModuleBase {
public:
    explicit ObjModule(const std::string &moduleName) : ObjModuleBase(moduleName) {}

    ObjModule(ObjModule &) = delete;
    ~ObjModule() override = default;

    inline void addField(const std::string &fieldName, Value defaultValue) noexcept {
        ASSERT(m_fields.find(fieldName) != m_fields.end(),
               "Field is exist yet...");
        m_fields.insert(std::make_pair(fieldName, defaultValue));
    }

    void addMethod(std::unique_ptr<ObjMethod> &method) noexcept {
        m_methods.push_back(std::move(method));
    }

    inline void registerConstants(SymbolTable& strings) noexcept {
        m_constantStrings = std::move(strings);
    }

    [[nodiscard]]
    inline const ObjStringLiteral* findString(size_t idx) const noexcept {
        if (m_constantStrings.size() <= idx) {
            return nullptr;
        } else {
            return m_constantStrings[idx].get();
        }
    }

public:
    static std::unique_ptr<ObjModule> make(const std::string &moduleName) noexcept {
        return std::move(std::make_unique<ObjModule>(moduleName));
    }

public:
    SymbolTable m_constantStrings{};
    std::map<std::string, Value> m_fields{};
};
