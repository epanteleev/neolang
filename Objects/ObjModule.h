#pragma once

#include <list>
#include <memory>

#include "Object.h"
#include "ObjMethod.h"
#include "SymbolTable.h"

class ObjModule final : public Object {
public:
    ObjModule() : Object("ObjModule") {}
    ~ObjModule() = default;

    inline void addMethod(std::unique_ptr<ObjMethod>& method) noexcept {
        m_methods.push_back(std::move(method));
    }

    inline void addField(const std::string &name, Value value) noexcept {
        ASSERT(m_fields.find(name) != m_fields.end(),
               "Field is exist yet...");
        m_fields.insert(std::make_pair(name, value));
    }

    inline ObjMethod *findMethod(const std::string &name) noexcept {
        auto pred = [&](std::unique_ptr<ObjMethod> &i) { return (*i).m_methodName == name; };
        return std::find_if(m_methods.begin(), m_methods.end(), pred)->get();
    }

public:
    static std::unique_ptr<ObjModule> make() noexcept {
        return std::make_unique<ObjModule>();
    }

public:
    std::list<std::unique_ptr<ObjMethod>> m_methods{};
    std::map<std::string, Value> m_fields{};
};
