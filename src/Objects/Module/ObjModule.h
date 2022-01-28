#pragma once

#include <list>
#include <memory>

#include "Objects/Object.h"
#include "Objects/Method/ObjMethod.h"
#include "Objects/StringBuffer.h"
#include "ObjModuleBase.h"
#include "ObjField.h"

/**
 * Represent module of programming language.
 * @author minium2
 */
class ObjModule final : public ObjModuleBase {
public:
    using Pointer = std::unique_ptr<ObjModule>;
    using Fields = std::list<ObjField>;
    using size_type = Fields::size_type;

public:
    explicit ObjModule(ObjString moduleName, Fields fields) :
        ObjModuleBase(std::move(moduleName)),
        m_fields(std::move(fields))
        {}

    ObjModule(ObjModule &&module) noexcept:
            ObjModuleBase(module.moduleName()) {}

    ObjModule(ObjModule &) = delete;

    ~ObjModule() override = default;

public:
    inline void addMethod(ObjMethod::Pointer method) noexcept {
        method->setModule(this);
        m_methods.push_back(std::move(method));
    }

    template<typename...Args>
    inline void addField(Args &&...field) noexcept {
        m_fields.emplace_back(std::forward<Args>(field)...);
    }

    [[nodiscard]]
    inline const ObjModule &asModule() const noexcept override {
        return *this;
    }

    [[nodiscard]]
    inline const ObjNativeModule &asNativeModule() const noexcept override {
        UNREACHABLE();
    }

    [[nodiscard]]
    ModuleType moduleType() const noexcept override {
        return ModuleType::OBJ;
    }

    [[nodiscard]]
    inline size_type fieldsSize() const noexcept {
        return m_fields.size();
    }

    [[nodiscard]]
    size_type offset(size_type id) const noexcept {
        auto filter = [&](const ObjField &el) {
            return el.nameId == id;
        };
        auto el = std::find_if(m_fields.begin(), m_fields.end(), filter);
        return el->offset;
    }

public:
    static Pointer make(ObjString &&moduleName, Fields fields) noexcept {
        return std::make_unique<ObjModule>(std::move(moduleName), std::move(fields));
    }

private:
    Fields m_fields;
};
