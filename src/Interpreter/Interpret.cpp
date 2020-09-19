#include <map>
#include "Interpreter/Interpret.h"

#define APPLY(opCode) VmResult opCode::apply(Vm &vm) noexcept

#define CASE(opCode, handler) case OpCode::opCode: vmResult = handler::apply(vm); \
                                break;

#define INTERPRET(opCode)                       \
    class opCode : public Interpret {           \
    public:                                     \
        static VmResult apply(Vm &vm) noexcept; \
    };                                          \

INTERPRET(iAdd)
INTERPRET(iSub)
INTERPRET(iMul)
INTERPRET(iPush)
INTERPRET(iDiv)
INTERPRET(iStore)
INTERPRET(iLoad)
INTERPRET(CallStatic)
INTERPRET(Ret)
INTERPRET(Invoke)
INTERPRET(New)
INTERPRET(fAdd)
INTERPRET(fSub)
INTERPRET(fDiv)
INTERPRET(fMult)
INTERPRET(fPush)

static VmResult callMethod(Vm& vm, const String& moduleName, const String& methodName) noexcept {
    ObjMethodBase* method = vm.modules().findMethod(moduleName, methodName);
    TRACE(vm, method != nullptr, "Unresolved method " + moduleName + "::" + methodName);
    return method->apply(vm);
}

VmResult Interpret::apply(const std::string& moduleName, Vm &vm) {
    ObjMethodBase* method = vm.modules().findMethod(moduleName, "main");
    if (method == nullptr) {
        vm.vmError("Unresolved symbol " + moduleName + "::main.");
        return VmResult::TERMINATE;
    }
    vm.callStack().push(Frame(*method, 0));
    while (true) {
        auto& frame = vm.frame();
        if (!frame.hasNext()) {
            return VmResult::SUCCESS;
        }
        VmResult vmResult;
        switch (frame.inst().code()) {
            CASE(iADD,       iAdd)
            CASE(iSUB,       iSub)
            CASE(iMUL,       iMul)
            CASE(iDIV,       iDiv)
            CASE(iPUSH,      iPush)
            CASE(iSTORE,     iStore)
            CASE(iLOAD,      iLoad)
            CASE(fDIV,       fDiv)
            CASE(fADD,       fAdd)
            CASE(fSUB,       fSub)
            CASE(fMULT,      fMult)
            CASE(fPUSH,      fPush)
            CASE(RET,        Ret)
            CASE(INVOKE,     Invoke)
            CASE(CALLSTATIC, CallStatic)
            CASE(NEW,        New)
            default: TRACE(vm, false, "Undefined instruction.");
        }
        if (vmResult != VmResult::SUCCESS) {
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

    const String* methodName = module.findString(inst.arg0().value());
    TRACE(vm, methodName != nullptr, "No found method name.");

    return callMethod(vm, moduleName, *methodName);
}

APPLY(CallStatic) {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const auto& module = dynamic_cast<const ObjModule&>(frame.method().module());

    const String* moduleName = module.findString(inst.arg0().value());
    TRACE(vm, moduleName != nullptr, "No found module name.");

    const String* methodName = module.findString(inst.arg1().value());
    TRACE(vm, methodName != nullptr, "No found method name.");

    return callMethod(vm, *moduleName, *methodName);
}

APPLY(New) {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const auto& module = dynamic_cast<const ObjModule&>(frame.method().module());

    const String* moduleName = module.findString(inst.arg0().value());
    TRACE(vm, moduleName != nullptr, "No found module name.");

    return callMethod(vm, *moduleName, "<new>");
}

APPLY(Ret) {
    vm.leave();
    return VmResult::SUCCESS;
}

APPLY(iStore) {
    const auto instruction = vm.frame().inst();
    const auto variable = instruction.arg0();
    TRACE(vm, vm.stack().nonEmpty(), "ApiStack is empty.");
    TRACE(vm, variable.value() < Vm::MAX_LOCAL_VARS, "Invalid variable index.");
    const auto a = vm.stack().pop();
    TRACE(vm, a.type() == Type::INT32, "Incomparable type.");
    vm.store(a, variable.value());
    return VmResult::SUCCESS;
}

APPLY(iPush) {
    const auto inst = vm.frame().inst();
    TRACE(vm, inst.arg0().type() == Type::INT32, "Invalid type.");
    vm.stack().push(inst.arg0());
    return VmResult::SUCCESS;
}

APPLY(fPush) {
    const auto inst = vm.frame().inst();
    TRACE(vm, inst.arg0().type() == Type::FLOAT32, "Invalid type.");
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
    ZERO_DIVISION(vm, b.toFloat32() != 0);
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

APPLY(iLoad) {
    const auto instruction = vm.frame().inst();
    const auto variable = instruction.arg0();
    const auto a = vm.load(variable.value());
    vm.stack().push(a);
    return VmResult::SUCCESS;
}