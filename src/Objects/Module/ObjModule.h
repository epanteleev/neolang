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
    explicit ObjModule(ObjString moduleName) : ObjModuleBase(std::move(moduleName)) {}

    ObjModule(ObjModule &&module) noexcept:
            ObjModuleBase(module.moduleName()) {}

    ObjModule(ObjModule &) = delete;

    ~ObjModule() override = default;

public:
    inline void addMethod(std::unique_ptr<ObjMethod> &&method) noexcept {
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
    inline std::size_t fieldsSize() const noexcept {
        return m_fields.size();
    }

    [[nodiscard]]
    std::size_t offset(std::size_t id) const noexcept {
        auto filter = [&](const ObjField &el) {
            return el.nameId == id;
        };
        auto el = std::find_if(m_fields.begin(), m_fields.end(), filter);
        return el->offset;
    }

public:
    static std::unique_ptr<ObjModule> make(ObjString &&moduleName) noexcept {
        return std::make_unique<ObjModule>(std::move(moduleName));
    }

private:
    std::list<ObjField> m_fields;
};
