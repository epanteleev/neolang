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
        {OpCode::RET,        Ret::apply}
};

bool Interpret::apply(const std::string& moduleName, Vm &vm) {
    ObjMethod* method = vm.modules().findMethod(moduleName, "main");
    vm.callStack().push(Frame(*method));
    while (true) {
        auto& frame = vm.frame();
        if (!frame.hasNext()) {
            return true;
        }
        if (!handlers[frame.inst().code()](vm)) {
            return false;
        }
        frame.next();
    }
}

bool CallStatic::apply(Vm &vm) noexcept {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const ObjModule& module = frame.method().module();
    const ObjStringLiteral* moduleName = module.findString(inst.arg0().value());
    TRACE(vm, moduleName != nullptr, "No found module name.");
    const ObjStringLiteral* methodName = module.findString(inst.arg1().value());
    TRACE(vm, methodName != nullptr, "No found method name.");
    ObjMethod* method = vm.modules().findMethod(moduleName->str(), methodName->str());
    TRACE(vm, method != nullptr, "Unresolved method " + moduleName->str() + "::" + methodName->str());
    vm.callStack().push(Frame(*method));
}
