#include <map>
#include "Interpret.h"
#include "Object.h"
#include "ObjString.h"

static std::map<OpCode, Interpret::Actions> handlers = {
        {OpCode::iADD,   iAdd::apply},
        {OpCode::iPUSH,  iPush::apply},
        {OpCode::iSTORE, iStore::apply},
        {OpCode::CALL,   Call::apply},
        {OpCode::iMULT,  iMult::apply},
        {OpCode::iSUB,   iSub::apply}
};

void Interpret::apply(Vm &vm) {
    for (; vm.hasNext(); vm.next()) {
        handlers[vm.currentInst().code()](vm);
    }
}

void Call::apply(Vm &vm) noexcept {
    Instruction inst = vm.currentInst();
    std::string &name = const_cast<std::string &>(((ObjString *) inst.val().toObject())->str());
    NativeFunc f = vm.findFunc(name);
    f(&vm);
}
