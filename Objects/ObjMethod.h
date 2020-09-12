#pragma once

#include <vector>
#include <string>
#include <map>

#include <memory>

#include "Instruction.h"
#include "Value.h"
#include "Object.h"
#include "ObjFrwd.h"

class ObjMethod : public Object {
public:
    explicit ObjMethod(std::string name) :
            Object("ObjMethod"),
            m_methodName(std::move(name)) {}

    explicit ObjMethod(std::string name, std::vector<Instruction> &instList) :
            Object("ObjMethod"),
            m_methodName(std::move(name)),
            m_instList(instList) {}

    inline void addInst(Instruction inst) noexcept {
        m_instList.push_back(inst);
    }

public:
    static std::unique_ptr<ObjMethod> make(const std::string &name, std::vector<Instruction> &instList) noexcept {
        return std::make_unique<ObjMethod>(name, instList);
    }

    static std::unique_ptr<ObjMethod> make(const std::string &name) noexcept {
        return std::make_unique<ObjMethod>(name);
    }

public:
    std::string m_methodName;
    std::vector<Instruction> m_instList;
};