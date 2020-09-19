#include <map>
#include "Interpreter/Interpret.h"

#define APPLY(opCode) VmResult opCode::apply(Vm &vm) noexcept \

typedef VmResult (*Actions)(Vm &vm) noexcept;

static std::map<OpCode, Actions> handlers = {
        {OpCode::iADD,       iAdd::apply},
        {OpCode::iPUSH,      iPush::apply},
        {OpCode::iSTORE,     iStore::apply},
        {OpCode::CALLSTATIC, CallStatic::apply},
        {OpCode::iMUL,       iMul::apply},
        {OpCode::iSUB,       iSub::apply},
        {OpCode::RET,        Ret::apply},
        {OpCode::INVOKE,     Invoke::apply},
        {OpCode::NEW,        New::apply},
        {OpCode::iDIV,       iDiv::apply},
        {OpCode::fADD,       fAdd::apply},
        {OpCode::fSUB,       fSub::apply},
        {OpCode::fMULT,      fMult::apply},
        {OpCode::fDIV,       fDiv::apply}
};

static VmResult callMethod(Vm& vm, const ObjStringLiteral& moduleName, const ObjStringLiteral& methodName) noexcept {
    ObjMethodBase* method = vm.modules().findMethod(moduleName, methodName);
    TRACE(vm, method != nullptr, "Unresolved method " + moduleName + "::" + methodName);
    return method->apply(vm);
}


VmResult Interpret::apply(const std::string& moduleName, Vm &vm) {
    ObjMethodBase* method = vm.modules().findMethod(moduleName, "main");
    if (method == nullptr) {
        vm.vmError("Unresolved symbol " + moduleName + "::main");
        return VmResult::TERMINATE;
    }
    vm.callStack().push(Frame(*method));
    while (true) {
        auto& frame = vm.frame();
        if (!frame.hasNext()) {
            return VmResult::SUCCESS;
        }
        ASSERT(handlers.contains(frame.inst().code()), "Invalid instruction.");
        if (handlers[frame.inst().code()](vm) == VmResult::TERMINATE) {
            return VmResult::TERMINATE;
        }
        frame.next();
    }
}

APPLY(Invoke) {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const auto& module = dynamic_cast<const ObjModule&>(frame.method().module());

    const std::string& moduleName = vm.stack().top().toObject()->objectName();

    const ObjStringLiteral* methodName = module.findString(inst.arg0().value());
    TRACE(vm, methodName != nullptr, "No found method name.");

    return callMethod(vm, moduleName, *methodName);
}

APPLY(CallStatic) {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const auto& module = dynamic_cast<const ObjModule&>(frame.method().module());

    const ObjStringLiteral* moduleName = module.findString(inst.arg0().value());
    TRACE(vm, moduleName != nullptr, "No found module name.");

    const ObjStringLiteral* methodName = module.findString(inst.arg1().value());
    TRACE(vm, methodName != nullptr, "No found method name.");

    return callMethod(vm, *moduleName, *methodName);
}

APPLY(New) {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const auto& module = dynamic_cast<const ObjModule&>(frame.method().module());

    const ObjStringLiteral* moduleName = module.findString(inst.arg0().value());
    TRACE(vm, moduleName != nullptr, "No found module name.");

    return callMethod(vm, *moduleName, "<new>");
}

APPLY(Ret) {
    TRACE(vm, !vm.callStack().empty(), "CallStack is empty.");
    vm.callStack().pop();
    return VmResult::SUCCESS;
}

APPLY(iStore) {
    const auto instruction = vm.frame().inst();
    const auto variable = instruction.arg0();
    TRACE(vm, vm.stack().nonEmpty(), "ApiStack is empty.");
    TRACE(vm, variable < 4, "Invalid variable index.");
    const auto a = vm.stack().pop();
    if (a.type() == Type::INT32) {
        vm.store(a, variable.value());
    } else {
        TRACE(vm, false, "Incomparable type.");
    }
    return VmResult::SUCCESS;
}

APPLY(iPush) {
    const auto inst = vm.frame().inst();
    vm.stack().push(inst.arg0());
    return VmResult::SUCCESS;
}

APPLY(iMul) {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toInt32() * b.toInt32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}

APPLY(iSub) {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toInt32() - b.toInt32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}

APPLY(iAdd) {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toInt32() + b.toInt32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}

APPLY(iDiv) {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toInt32() / b.toInt32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}

APPLY(fAdd) {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toFloat32() + b.toFloat32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}

APPLY(fSub) {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toFloat32() - b.toFloat32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}

APPLY(fDiv) {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    TRACE(vm, b.toFloat32() != 0, "Zero division.");
    const auto result = a.toFloat32() / b.toFloat32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}

APPLY(fMult) {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toFloat32() * b.toFloat32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}