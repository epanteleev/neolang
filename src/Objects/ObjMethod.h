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

/**
 * Represent method of programming language.
 * @author minium2
 */
class ObjMethod : public ObjMethodBase {
public:
    explicit ObjMethod(const ObjModuleBase &module, ObjString methodName) :
            ObjMethodBase(module, std::move(methodName)) {}

    explicit ObjMethod(const ObjModuleBase &module, ObjString methodName, InstList &instList) :
            ObjMethodBase(module, std::move(methodName)),
            m_instList(std::move(instList)) {}

    ObjMethod(ObjMethod &&method) noexcept:
            ObjMethodBase(std::move(method)) {}

public:
    inline void addInst(Instruction inst) noexcept {
        m_instList.push_back(inst);
    }

    [[nodiscard]]
    inline InstList &instList() noexcept {
        return m_instList;
    }

    [[nodiscard]]
    inline bool isNative() const noexcept override {
        return false;
    }

    VmResult apply(Vm &vm) noexcept override;

public:
    static std::unique_ptr<ObjMethod> make(const ObjModuleBase &method, ObjString name,
                                               InstList &instList) noexcept {
        return std::make_unique<ObjMethod>(method, std::move(name), instList);
    }

    static std::unique_ptr<ObjMethod> make(const ObjModuleBase &method, ObjString name) noexcept {
        return std::make_unique<ObjMethod>(method, std::move(name));
    }

private:
    InstList m_instList;
};

