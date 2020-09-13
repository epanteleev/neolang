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

class ObjMethod : public Object {
public:
    explicit ObjMethod(const ObjModule& module, std::string methodName) :
            Object("ObjMethod"),
            m_module(module),
            m_methodName(std::move(methodName)) {}

    explicit ObjMethod(const ObjModule& module, std::string name, InstList &instList) :
            Object("ObjMethod"),
            m_module(module),
            m_methodName(std::move(name)),
            m_instList(std::move(instList)) {}


    ObjMethod(ObjMethod &&method) noexcept :
            Object("ObjMethod"),
            m_module(method.m_module),
            m_methodName(std::move(method.m_methodName)),
            m_instList(std::move(method.m_instList)) {}

    inline void addInst(Instruction inst) noexcept {
        m_instList.push_back(inst);
    }

    inline const InstList &insts() const noexcept {
        return m_instList;
    }

    inline const std::string &name() const noexcept {
        return m_methodName;
    }

    inline const ObjModule& module() const noexcept {
        return m_module;
    }

    inline const std::string& methodName() const noexcept {
        return m_methodName;
    }

public:
    static std::unique_ptr<ObjMethod> make(const ObjModule &method, const std::string &name, std::vector<Instruction> &instList) noexcept {
        return std::make_unique<ObjMethod>(method, name, instList);
    }

    static std::unique_ptr<ObjMethod> make(const ObjModule &method, const std::string &name) noexcept {
        return std::make_unique<ObjMethod>(method, name);
    }

public:
    const ObjModule& m_module;
    std::string m_methodName;
    InstList m_instList;
};
