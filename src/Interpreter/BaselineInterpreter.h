#pragma once

#include "Vm/Allocator/DefaultAllocator.h"
#include "Interpreter/Interpreter.h"
#include "Objects/ObjString.h"
#include "Vm/Environment.h"
#include "Vm/Common.h"
#include "Vm/Vm.h"

/**
 * @author minium2
 */
class BaselineInterpreter final: public Interpreter {
public:
    /**
     * BaselineInterpreter module with name "module name" in virtual machine.
     * Module must have method "main".
     * @return execution result.
     */
    VmResult apply(const ObjString& moduleName);

    void trace();

public:
    BaselineInterpreter() = default;

    BaselineInterpreter(BaselineInterpreter&) = delete;

    BaselineInterpreter operator=(BaselineInterpreter&) = delete;

public:
    VmResult iAdd() override;
    VmResult iSub() override;
    VmResult iMul() override;
    VmResult iPush(Value arg) override;
    VmResult iDiv() override;
    VmResult iStore(Value arg) override;
    VmResult iLoad(Value arg) override;
    VmResult iRet() override;
    VmResult i2f() override;
    VmResult CallStatic(Value arg0, Value arg1) override;
    VmResult Ret() override;
    VmResult Invoke() override;
    VmResult New(Value arg) noexcept override;
    VmResult fAdd() override;
    VmResult fSub() override;
    VmResult fDiv() override;
    VmResult fMult() override;
    VmResult fPush(Value arg) override;
    VmResult fLoad(Value arg) override;
    VmResult fStore(Value arg) override;
    VmResult fRet() override;
    VmResult ldc(Value arg) override;
    VmResult swap() override;
    VmResult rPush(Value arg) override;
    VmResult rStore(Value arg) override;
    VmResult rLoad(Value arg) override;
    VmResult Cmp() override;
    VmResult CmpnEq() override;
    VmResult Jump(Value arg) override;
    VmResult Goto(Value arg) override;
    VmResult And() override;
    VmResult Or() override;
    VmResult PutField(Value arg) override;
    VmResult GetField(Value arg) override;
    VmResult RRet() override;
    VmResult Dup() override;
private:
    VmResult callInstruction(Instruction instruction) noexcept;

    VmResult callMethod(const ObjString &moduleName, const ObjString &methodName);

private:
    ApiStack stack;
    Locals m_local;
    CallStack callStack;
    DefaultAllocator allocator;
};