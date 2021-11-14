#pragma once
#include "Vm/Vm.h"

/**
 * Base class for all interpreters.
 * @author minium2
 */
class Interpreter {
public:
    virtual VmResult iAdd() = 0;
    virtual VmResult iSub() = 0;
    virtual VmResult iMul() = 0;
    virtual VmResult iPush(Value arg) = 0;
    virtual VmResult iDiv() = 0;
    virtual VmResult iStore(Value arg) = 0;
    virtual VmResult iLoad(Value arg) = 0;
    virtual VmResult iRet() = 0;
    virtual VmResult i2f() = 0;
    virtual VmResult CallStatic(Value arg0, Value arg1) = 0;
    virtual VmResult Ret() = 0;
    virtual VmResult Invoke() = 0;
    virtual VmResult New(Value arg) noexcept = 0;
    virtual VmResult fAdd() = 0;
    virtual VmResult fSub() = 0;
    virtual VmResult fDiv() = 0;
    virtual VmResult fMult() = 0;
    virtual VmResult fPush(Value arg) = 0;
    virtual VmResult fLoad(Value arg) = 0;
    virtual VmResult fStore(Value arg) = 0;
    virtual VmResult fRet() = 0;
    virtual VmResult ldc(Value arg) = 0;
    virtual VmResult swap() = 0;
    virtual VmResult rPush(Value arg) = 0;
    virtual VmResult rStore(Value arg) = 0;
    virtual VmResult rLoad(Value arg) = 0;
    virtual VmResult Cmp() = 0;
    virtual VmResult CmpnEq() = 0;
    virtual VmResult Jump(Value arg) = 0;
    virtual VmResult Goto(Value arg) = 0;
    virtual VmResult And() = 0;
    virtual VmResult Or() = 0;
    virtual VmResult PutField(Value arg) = 0;
    virtual VmResult GetField(Value arg) = 0;
    virtual VmResult RRet() = 0;
    virtual VmResult Dup() = 0;
};
