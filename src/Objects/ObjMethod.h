#pragma once

#include <vector>
#include <string>
#include <map>

#include <memory>
#include <list>

#include "Vm/Instruction.h"
#include "Vm/Value.h"
#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"
#include "Objects/ObjMethodBase.h"


class ObjMethod : public ObjMethodBase {
public:
    explicit ObjMethod(const ObjModuleBase &module, const String &methodName) :
            ObjMethodBase(module, "ObjMethod", methodName) {}

    explicit ObjMethod(const ObjModuleBase &module, const String &methodName, InstList &instList) :
            ObjMethodBase(module, "ObjMethod", methodName),
            m_instList(std::move(instList)) {}


    ObjMethod(ObjMethod &&method) noexcept:
            ObjMethodBase(method.m_module, "ObjMethod", method.m_methodName),
            m_instList(std::move(method.m_instList)) {}

public:
    inline void addInst(Instruction inst) noexcept {
        m_instList.push_back(inst);
    }

    [[nodiscard]]
    inline const InstList &instList() const noexcept {
        return m_instList;
    }

    [[nodiscard]]
    inline bool isNative() const noexcept override {
        return false;
    }

    VmResult apply(Vm &vm) noexcept override;

public:
    static std::unique_ptr<ObjMethodBase> make(const ObjModuleBase &method,
                                               const std::string &name,
                                               InstList &instList) noexcept {
        return std::make_unique<ObjMethod>(method, name, instList);
    }

    static std::unique_ptr<ObjMethod> make(const ObjModuleBase &method, const String &name) noexcept {
        return std::make_unique<ObjMethod>(method, name);
    }

public:
    InstList m_instList;
};
