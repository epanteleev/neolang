#include "Interpreter/Interpret.h"
#include "Vm/OpCode.h"
#include "Vm/Instruction.h"
#include "Vm/Vm.h"

#define APPLY(opCode) VmResult opCode::apply(Vm &vm) noexcept

#define CASE(opCode, handler) case OpCode::opCode: return handler::apply(vm); \
                                break;

#define INTERPRET(opCode)                       \
    class opCode : public Interpret {           \
    public:                                     \
        static VmResult apply(Vm &vm) noexcept; \
    };                                          \

#define TERMINATE(condition, string, ...)                                              \
      do                                                                               \
      {                                                                                \
        if (!(condition))                                                              \
        {                                                                              \
          fprintf(stderr, "%s:%s():%ds " string "\n",__FILE__,                         \
                    __func__, __LINE__, ##__VA_ARGS__ );                               \
          vm.trace();                                                                  \
          return VmResult::TERMINATE;                                                  \
        }                                                                              \
      } while (false)

#define ZERO_DIVISION(vm, condition)                                           \
      do                                                                       \
      {                                                                        \
        if (!(condition))                                                      \
        {                                                                      \
          fprintf(stderr, "Zero division.");                                   \
          vm.trace();                                                          \
          return VmResult::ZERO_DIVISION;                                      \
        }                                                                      \
      } while (false)


INTERPRET(iAdd)
INTERPRET(iSub)
INTERPRET(iMul)
INTERPRET(iPush)
INTERPRET(iDiv)
INTERPRET(iStore)
INTERPRET(iLoad)
INTERPRET(iRet)
INTERPRET(i2f)
INTERPRET(CallStatic)
INTERPRET(Ret)
INTERPRET(Invoke)
INTERPRET(New)
INTERPRET(fAdd)
INTERPRET(fSub)
INTERPRET(fDiv)
INTERPRET(fMult)
INTERPRET(fPush)
INTERPRET(fLoad)
INTERPRET(fStore)
INTERPRET(fRet)
INTERPRET(ldc)
INTERPRET(rPush)
INTERPRET(rStore)
INTERPRET(IfCmp)

static VmResult callMethod(Vm &vm, const ObjString &moduleName, const ObjString &methodName) noexcept {
    ObjMethodBase *method = vm.modules().findMethod(moduleName, methodName);
    TERMINATE(method != nullptr, "Unresolved method %s::%s", moduleName.cstr(), methodName.cstr());
    return method->apply(vm);
}

inline VmResult callInstruction(Vm &vm, OpCode opcode) noexcept {
    switch (opcode) {
        CASE(iADD,       iAdd)
        CASE(iSUB,       iSub)
        CASE(iMUL,       iMul)
        CASE(iDIV,       iDiv)
        CASE(iPUSH,      iPush)
        CASE(iSTORE,     iStore)
        CASE(iLOAD,      iLoad)
        CASE(iRET,       iRet)
        CASE(I2F,        i2f)
        CASE(fDIV,       fDiv)
        CASE(fADD,       fAdd)
        CASE(fSUB,       fSub)
        CASE(fMUL,       fMult)
        CASE(fPUSH,      fPush)
        CASE(fLOAD,      fLoad)
        CASE(fSTORE,     fStore)
        CASE(fRET,       fRet)
        CASE(RET,        Ret)
        CASE(INVOKE,     Invoke)
        CASE(CALLSTATIC, CallStatic)
        CASE(NEW,        New)
        CASE(LDC,        ldc)
        CASE(rSTORE,     rStore)
        CASE(rPUSH,      rPush)
        CASE(IF_EQ,     IfCmp)
        default: TERMINATE(false, "Undefined instruction: %s", opCodeToString(opcode));
    }
}

// Todo: Rewrite it
VmResult Interpret::apply(const ObjString &moduleName, Vm &vm) {
    ObjMethodBase *method = vm.modules().findMethod(moduleName, "main");
    if (method == nullptr) {
        vm.vmError("Unresolved symbol " + moduleName + "::main.");
        return VmResult::TERMINATE;
    }
    vm.callStack().push(Frame(*method, 0));
    while (true) {
        auto &frame = vm.frame();
        VmResult vmResult = callInstruction(vm, frame.inst().code());

        if (vmResult != VmResult::SUCCESS) {
            return vmResult;
        }
        if (vm.callStack().empty()) {
            return VmResult::SUCCESS;
        }
        auto &refreshedFrame = vm.frame();
        if (!refreshedFrame.hasNext()) {
            return VmResult::TERMINATE;
        }
        frame.next();
    }
    UNREACHABLE();
}

APPLY(Invoke) {
    UNREACHABLE();
}

APPLY(CallStatic) {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const auto &module = dynamic_cast<const ObjModule &>(frame.method().module());

    const ObjString *moduleName = module.findString(inst.arg0().value());
    TERMINATE(moduleName != nullptr, "No found module name.");

    const ObjString *methodName = module.findString(inst.arg1().value());
    TERMINATE(methodName != nullptr, "No found method name.");

    return callMethod(vm, *moduleName, *methodName);
}

APPLY(New) {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const auto &module = frame.currentModule();

    const ObjString *moduleName = module.findString(inst.arg0().value());
    TERMINATE(moduleName != nullptr, "No found module name.");

    return callMethod(vm, *moduleName, "<new>");
}

APPLY(Ret) {
    vm.leave();
    return VmResult::SUCCESS;
}

APPLY(iRet) {
    const auto val = vm.stack().pop();
    TERMINATE(val.type() == Type::INT32,
              "Invalid return type. Required: %s. Found: %s.", typeToString(Type::INT32), typeToString(val.type()));
    vm.leave();
    vm.stack().push(val);
    return VmResult::SUCCESS;
}

APPLY(fRet) {
    const auto val = vm.stack().pop();
    TERMINATE(val.type() == Type::FLOAT32,
              "Invalid return type. Required: %s. Found: %s.", typeToString(Type::FLOAT32), typeToString(val.type()));
    vm.leave();
    vm.stack().push(val);
    return VmResult::SUCCESS;
}

APPLY(iStore) {
    const auto instruction = vm.frame().inst();
    const auto variable = instruction.arg0();
    TERMINATE(vm.stack().nonEmpty(), "ApiStack is empty.");
    const auto a = vm.stack().pop();
    TERMINATE(a.type() == Type::INT32,
              "Incomparable type. Required: %s. Found: %s.", typeToString(Type::INT32), typeToString(a.type()));
    vm.store(a, variable.value());
    return VmResult::SUCCESS;
}

APPLY(iPush) {
    const auto inst = vm.frame().inst();
    const auto arg = inst.arg0();
    TERMINATE(arg.type() == Type::INT32,
              "Invalid type. Required: %s. Found: %s.", typeToString(Type::INT32), typeToString(arg.type()));
    vm.stack().push(arg);
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
    ZERO_DIVISION(vm, b.toInt32() != 0);
    const auto result = a.toInt32() / b.toInt32();
    vm.stack().push(Value(result));
    return VmResult::SUCCESS;
}

APPLY(iLoad) {
    const auto instruction = vm.frame().inst();
    const auto var = instruction.arg0();
    TERMINATE(var.type() == Type::INT32,
              "Invalid type. Required: %s. Found: %s.", typeToString(Type::INT32), typeToString(var.type()));
    const auto a = vm.load(var.value());
    vm.stack().push(a);
    return VmResult::SUCCESS;
}

APPLY(i2f) {
    const auto val = vm.stack().pop();
    TERMINATE(val.type() == Type::INT32,
              "Invalid type. Required: %s. Found: %s.", typeToString(Type::INT32), typeToString(val.type()));
    vm.stack().push(Value((float)val.value()));
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

APPLY(fPush) {
    const auto inst = vm.frame().inst();
    const auto arg = inst.arg0();
    TERMINATE(arg.type() == Type::FLOAT32,
              "Invalid type. Required: %s. Found: %s.", typeToString(Type::FLOAT32), typeToString(arg.type()));
    vm.stack().push(arg);
    return VmResult::SUCCESS;
}

APPLY(fStore) {
    const auto instruction = vm.frame().inst();
    const auto variable = instruction.arg0();
    TERMINATE(vm.stack().nonEmpty(), "ApiStack is empty.");
    const auto a = vm.stack().pop();
    TERMINATE(a.type() == Type::FLOAT32,
              "Incomparable type. Required: %s. Found: %s.", typeToString(Type::FLOAT32), typeToString(a.type()));
    vm.store(a, variable.value());
    return VmResult::SUCCESS;
}

APPLY(fLoad) {
    const auto instruction = vm.frame().inst();
    const auto var = instruction.arg0();
    TERMINATE(var.type() == Type::INT32,
              "Invalid type. Required: %s. Found: %s.", typeToString(Type::INT32), typeToString(var.type()));
    const auto a = vm.load(var.value());
    vm.stack().push(a);
    return VmResult::SUCCESS;
}

APPLY(ldc) {
    Frame frame = vm.frame();
    Instruction inst = frame.inst();
    const auto &module = frame.currentModule();
    const auto *string = module.findString(inst.arg0().value());
    TERMINATE(string != nullptr, "String no found.");
    vm.stack().push(string->value());
    return VmResult::SUCCESS;
}

APPLY(rPush) {
    const auto inst = vm.frame().inst();
    const auto arg = inst.arg0();
    TERMINATE(arg.type() == Type::REF,
              "Invalid type. Required: %s. Found: %s.", typeToString(Type::REF), typeToString(arg.type()));
    vm.stack().push(inst.arg0());
    return VmResult::SUCCESS;
}

APPLY(rStore) {
    const auto instruction = vm.frame().inst();
    const auto variable = instruction.arg0();
    TERMINATE(vm.stack().nonEmpty(), "ApiStack is empty.");
    const auto a = vm.stack().pop();
    TERMINATE(a.type() == Type::REF,
              "Invalid type. Required: %s. Found: %s.", typeToString(Type::REF), typeToString(variable.type()));
    vm.store(a, variable.value());
    return VmResult::SUCCESS;
}

APPLY(IfCmp) {
    const auto instruction = vm.frame().inst();
    const auto ip = instruction.arg0();
    const auto a = vm.stack().pop();
    const auto b = vm.stack().pop();
    if (a == b) {
        vm.frame().gotoInst(ip.value() - 1);
    }
    return VmResult::SUCCESS;
}