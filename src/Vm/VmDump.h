#pragma once
#include "Vm/Buffer.h"
#include "Objects/Module/ModuleBuffer.h"

class VmDump final {
public:
    VmDump() :
            m_buf(nullptr, 0, 100) {}

private:
    void append(const ObjString& data) {
        m_buf.vprint("%s\n", data.cstr());
    }
public:
    void dump(ModuleBuffer& modules) {
        m_buf.vprint("Loaded modules:\n");
        for (auto& i: modules) {
            if (i->moduleType() == ModuleType::OBJ) {
                m_buf.vprint("Type: obj. ");
            } else {
                m_buf.vprint("Type: native. ");
            }
            m_buf.vprint("Name: %s\n", i->moduleName().cstr());
        }
    }

    void dump(StringBuffer& modules) {
        m_buf.vprint("String buffer:\n");

    }
public:
    Buffer m_buf;
};
