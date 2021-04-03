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
            ObjModuleBase(module.moduleName()) {}

    ObjModule(ObjModule &) = delete;

    ~ObjModule() override = default;

public:
    inline void addMethod(std::unique_ptr<ObjMethod> &&method) noexcept {
        method->setModule(this);
        m_methods.push_back(std::move(method));
    }

public:
    static std::unique_ptr<ObjModule> make(ObjString&& moduleName) noexcept {
        return std::make_unique<ObjModule>(std::move(moduleName));
    }
};
