#pragma once

#include <list>
#include <memory>

#include "Objects/Object.h"
#include "Objects/ObjMethod.h"
#include "Objects/SymbolTable.h"
#include "Objects/ObjModuleBase.h"

class ObjModule final : public ObjModuleBase {
public:
    explicit ObjModule(const String &moduleName) : ObjModuleBase(moduleName) {}

    ObjModule(ObjModule &&module) noexcept:
            ObjModuleBase(module.moduleName()),
            m_constantStrings(std::move(module.m_constantStrings)),
            m_fields(std::move(module.m_fields)) {}

    ObjModule(ObjModule &) = delete;

    ~ObjModule() override = default;

public:
    inline void addField(const String &fieldName, Value defaultValue) noexcept {
        ASSERT(m_fields.find(fieldName) != m_fields.end(),
               "Field is exist yet...");
        m_fields.insert(std::make_pair(fieldName, defaultValue));
    }

    inline void addMethod(std::unique_ptr<ObjMethod> &method) noexcept {
        m_methods.push_back(std::move(method));
    }

    inline void registerConstants(StringBuffer &strings) noexcept {
        m_constantStrings = std::move(strings);
    }

    inline void addStringConstant(std::string &str) noexcept {
        m_constantStrings.push_back(std::move(str));
    }

    [[nodiscard]]
    inline size_t sizeStringPool() const noexcept {
        return m_constantStrings.size();
    }

    [[nodiscard]]
    inline const String *findString(size_t idx) const noexcept {
        if (m_constantStrings.size() <= idx) {
            return nullptr;
        } else {
            return &m_constantStrings[idx];
        }
    }

public:
    static std::unique_ptr<ObjModule> make(const String &moduleName) noexcept {
        return std::make_unique<ObjModule>(moduleName);
    }

private:
    StringBuffer m_constantStrings{};
    std::map<String, Value> m_fields{};
};
