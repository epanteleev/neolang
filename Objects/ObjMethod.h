#pragma once

#include <utility>
#include <vector>
#include <string>
#include <map>
#include <Instruction.h>

#include "Value.h"
#include "Object.h"
#include "ObjFrwd.h"

class ObjMethod : public Object {
public:
    ObjMethod() = default;

    explicit ObjMethod(std::string name, std::vector<Instruction> &instList) :
            Object("ObjMethod"),
            m_methodName(std::move(name)),
            m_instList(instList) {}

public:
    static ObjMethod *make(const std::string &name, std::vector<Instruction> &instList) noexcept {
        return new ObjMethod(name, instList);
    }

public:
    std::string m_methodName;
    std::vector<Instruction> m_instList;
};