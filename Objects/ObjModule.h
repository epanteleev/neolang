#pragma once

#include <list>
#include <memory>

#include "Objects/Object.h"
#include "Objects/ObjMethod.h"
#include "Objects/SymbolTable.h"

class ObjModule final : public Object {
public:
    explicit ObjModule(const std::string &moduleName) : Object(moduleName) {}

    ObjModule(ObjModule &&module)  noexcept :
            Object(module.moduleName()),
            m_constantStrings(std::move(module.m_constantStrings)),
            m_methods(std::move(module.m_methods)) {}

    ObjModule(ObjModule &) = delete;
    ~ObjModule() override = default;

    inline void addMethod(std::unique_ptr<ObjMethod> &method) noexcept {
        m_methods.push_back(std::move(method));
    }

    inline void addField(const std::string &fieldName, Value defaultValue) noexcept {
        ASSERT(m_fields.find(fieldName) != m_fields.end(),
               "Field is exist yet...");
        m_fields.insert(std::make_pair(fieldName, defaultValue));
    }

    inline void registerConstants(SymbolTable& strings) noexcept {
        m_constantStrings = std::move(strings);
    }

    inline ObjMethod* findMethod(const std::string &name) const noexcept {
        auto pred = [&](const std::unique_ptr<ObjMethod> &i) { return (*i).m_methodName == name; };
        return std::find_if(m_methods.begin(), m_methods.end(), pred)->get();
    }

    inline const ObjStringLiteral* findString(size_t idx) const noexcept {
        if (m_constantStrings.size() > idx) {
            return nullptr;
        } else {
            return m_constantStrings[idx].get();
        }
    }

    inline const std::string &moduleName() const noexcept {
        return objectName();
    }

public:
    static std::unique_ptr<ObjModule> make(const std::string &moduleName) noexcept {
        return std::move(std::make_unique<ObjModule>(moduleName));
    }

public:
    SymbolTable m_constantStrings{};
    std::list<std::unique_ptr<ObjMethod>> m_methods{};
    std::map<std::string, Value> m_fields{};
};

class ModuleBuffer final {
public:
    ModuleBuffer() = default;
    ModuleBuffer(ModuleBuffer&) = delete;

    ~ModuleBuffer() = default;

    ObjMethod* findMethod(const std::string& moduleName, const std::string& name) {
        auto pred = [&](std::unique_ptr<ObjModule> &i) { return (*i).moduleName() == moduleName; };
        const auto module = std::find_if(m_methods.begin(), m_methods.end(), pred);
        if (module != m_methods.end()) {
            return (*module)->findMethod(name);
        } else {
            return nullptr;
        }
    }

    inline void addModule(std::unique_ptr<ObjModule> &module) noexcept {
        m_methods.push_back(std::move(module));
    }

private:
    std::list<std::unique_ptr<ObjModule>> m_methods;
};
