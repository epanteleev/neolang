#include <map>
#include "Interpreter/Interpret.h"
#include "Objects/Object.h"
#include "Objects/ObjStringLiteral.h"

typedef bool (*Actions)(Vm &vm) noexcept;

static std::map<OpCode, Actions> handlers = {
        {OpCode::iADD,       iAdd::apply},
        {OpCode::iPUSH,      iPush::apply},
        {OpCode::iSTORE,     iStore::apply},
        {OpCode::CALLSTATIC, CallStatic::apply},
        {OpCode::iMULT,      iMult::apply},
        {OpCode::iSUB,       iSub::apply},
        {OpCode::RET,        Ret::apply},
        {OpCode::INVOKE,     Invoke::apply},
        {OpCode::NEW,        New::apply}
};

static bool callMethod(Vm& vm, const std::string& moduleName, const std::string& methodName) noexcept {
    ObjMethodBase* method = vm.modules().findMethod(moduleName, methodName);
    TRACE(vm, method != nullptr, "Unresolved method " + moduleName + "::" + methodName);
    return method->apply(vm);
}

bool Interpret::apply(const std::string& moduleName, Vm &vm) {
    ObjMethodBase* method = vm.modules().findMethod(moduleName, "main");
    vm.callStack().push(Frame(*method));
    while (true) {
        auto& frame = vm.frame();
        if (!frame.hasNext()) {
            return true;
        }
        ASSERT(handlers.contains(frame.inst().code()), "Invalid instruction.");
        if (!handlers[frame.inst().code()](vm)) {
            return false;
        }
        frame.next();
    }
}

bool Invoke::apply(Vm &vm) noexcept {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const ObjModule& module = static_cast<const ObjModule&>(frame.method().module());

    const std::string& moduleName = vm.stack().top().toObject()->objectName();

    const ObjStringLiteral* methodName = module.findString(inst.arg0().value());
    TRACE(vm, methodName != nullptr, "No found method name.");

    return callMethod(vm, moduleName, methodName->str());
}

bool CallStatic::apply(Vm &vm) noexcept {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const ObjModule& module = static_cast<const ObjModule&>(frame.method().module());

    const ObjStringLiteral* moduleName = module.findString(inst.arg0().value());
    TRACE(vm, moduleName != nullptr, "No found module name.");

    const ObjStringLiteral* methodName = module.findString(inst.arg1().value());
    TRACE(vm, methodName != nullptr, "No found method name.");

    return callMethod(vm, moduleName->str(), methodName->str());
}

bool New::apply(Vm &vm) noexcept {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const ObjModule& module = static_cast<const ObjModule&>(frame.method().module());

    const ObjStringLiteral* moduleName = module.findString(inst.arg0().value());
    TRACE(vm, moduleName != nullptr, "No found module name.");

    return callMethod(vm, moduleName->str(), "<new>");
}

bool Ret::apply(Vm &vm) noexcept {
    TRACE(vm, !vm.callStack().empty(), "CallStack is empty.");
    vm.callStack().pop();
    return true;
}

bool iStore::apply(Vm &vm) noexcept{
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
    return true;
}

bool iPush::apply(Vm &vm) noexcept {
    const auto inst = vm.frame().inst();
    vm.stack().push(inst.arg0());
    return true;
}

bool iMult::apply(Vm &vm) noexcept {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toInt32() * b.toInt32();
    vm.stack().push(Value(result));
    return true;
}

bool iSub::apply(Vm &vm) noexcept {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toInt32() - b.toInt32();
    vm.stack().push(Value(result));
    return true;
}

bool iAdd::apply(Vm &vm) noexcept {
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    const auto result = a.toInt32() + b.toInt32();
    vm.stack().push(Value(result));
    return true;
}
