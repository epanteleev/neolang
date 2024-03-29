#include "Interpreter/BaselineInterpreter.h"
#include "Vm/Instance.h"

#define TERMINATE(condition, string, ...)                                              \
      do                                                                               \
      {                                                                                \
        if (!(condition))                                                              \
        {                                                                              \
          fprintf(stderr, "%s:%s():%ds " string "\n",__FILE__,                         \
                    __func__, __LINE__, ##__VA_ARGS__ );                               \
          return VmResult::TERMINATE;                                                  \
        }                                                                              \
      } while (false)

#define ZERO_DIVISION(vm, condition)                                           \
      do                                                                       \
      {                                                                        \
        if (!(condition))                                                      \
        {                                                                      \
          fprintf(stderr, "Zero division.");                                   \
          return VmResult::ZERO_DIVISION;                                      \
        }                                                                      \
      } while (false)

VmResult BaselineInterpreter::callMethod(const ObjString &moduleName, const ObjString &methodName) {
    ObjMethodBase *method = vm.modules().findMethod(moduleName, methodName);
    TERMINATE(method != nullptr, "Unresolved method %s::%s", moduleName.cstr(), methodName.cstr());
    Environment env(stack, m_local, callStack);
    return method->apply(env);
}

inline VmResult BaselineInterpreter::callInstruction(Instruction inst) noexcept {
    switch (inst.code()) {
        case OpCode::iADD:
            return iAdd();
        case OpCode::iSUB:
            return iSub();
        case OpCode::iMUL:
            return iMul();
        case OpCode::iDIV:
            return iDiv();
        case OpCode::iPUSH:
            return iPush(inst.arg0());
        case OpCode::iSTORE:
            return iStore(inst.arg0());
        case OpCode::iLOAD:
            return iLoad(inst.arg0());
        case OpCode::iRET:
            return iRet();
        case OpCode::i2F:
            return i2f();
        case OpCode::fDIV:
            return fDiv();
        case OpCode::fADD:
            return fAdd();
        case OpCode::fSUB:
            return fSub();
        case OpCode::fMUL:
            return fMult();
        case OpCode::fPUSH:
            return fPush(inst.arg0());
        case OpCode::fLOAD:
            return fLoad(inst.arg0());
        case OpCode::fSTORE:
            return fStore(inst.arg0());
        case OpCode::fRET:
            return fRet();
        case OpCode::RET:
            return Ret();
        case OpCode::INVOKE:
            return Invoke();
        case OpCode::CALL:
            return CallStatic(inst.arg0(), inst.arg1());
        case OpCode::NEW:
            return New(inst.arg0());
        case OpCode::LDC:
            return ldc(inst.arg0());
        case OpCode::SWAP:
            return swap();
        case OpCode::rSTORE:
            return rStore(inst.arg0());
        case OpCode::rLOAD:
            return rLoad(inst.arg0());
        case OpCode::rPUSH:
            return rPush(inst.arg0());
        case OpCode::CMPEQ:
            return Cmp();
        case OpCode::CMPNEQ:
            return CmpnEq();
        case OpCode::JUMP:
            return Jump(inst.arg0());
        case OpCode::GOTO:
            return Goto(inst.arg0());
        case OpCode::AND:
            return And();
        case OpCode::OR:
            return Or();
        case OpCode::PUTFIELD:
            return PutField(inst.arg0());
        case OpCode::GETFIELD:
            return GetField(inst.arg0());
        case OpCode::RRET:
            return RRet();
        case OpCode::DUP:
            return Dup();
        default:
            TERMINATE(false, "Undefined instruction: %s", inst.toString().c_str());
    }
}

// Todo: Rewrite it
VmResult BaselineInterpreter::apply(const ObjString &moduleName) {
    ObjMethodBase *method = vm.modules().findMethod(moduleName, "main");
    TERMINATE(method != nullptr, "Unresolved symbol ", moduleName.cstr(), "::main.");

    callStack.enter(*method);
    while (true) {
        auto &frame = callStack.frame();
        VmResult vmResult = callInstruction(frame.inst());

        if (vmResult != VmResult::SUCCESS) {
            return vmResult;
        }
        if (callStack.empty()) {
            return VmResult::SUCCESS;
        }
        Frame &refreshedFrame = callStack.frame();
        if (!refreshedFrame.hasNext()) {
            return VmResult::TERMINATE;
        }
        frame.next();
    }
    UNREACHABLE();
}

void BaselineInterpreter::trace() {
    fprintf(stderr, "[Vm stacktrace]\n");
    fprintf(stderr, "[Api stack]\n");
    for (auto &i : stack) {
        fprintf(stderr, "\t%lu:%s\n", i.value(), i.typeToString());
    }
    fprintf(stderr, "[Call stack]\n");
    callStack.stacktrace();
}

VmResult BaselineInterpreter::Invoke() {
    UNREACHABLE();
}

VmResult BaselineInterpreter::CallStatic(Value arg0, Value arg1) {

    const ObjString &moduleName = vm.findString(arg0.value());
    const ObjString &methodName = vm.findString(arg1.value());

    return callMethod(moduleName, methodName);
}

VmResult BaselineInterpreter::New(Value arg) noexcept {
    const ObjString &moduleName = vm.findString(arg.value());

    auto &module = vm.modules().findModule(moduleName)->asModule();
    auto size = module.fieldsSize();

    auto inst = static_cast<Instance *>(allocator.allocate(sizeof(Instance) + size));
    inst->clazz = (ObjModuleBase *) &module;
    stack.push(Value(reinterpret_cast<std::size_t>(inst), Value::Type::REF));
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::Ret() {
    auto frame = callStack.leave();
    TERMINATE(stack.size() == frame.savedSp(), "Frame non empty.");
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::iRet() {
    const auto val = stack.pop();
    TERMINATE(val.type() == Value::Type::INT32,
              "Invalid return type. Required: %s. Found: %s.", Value::I32, val.typeToString());

    auto frame = callStack.leave();
    TERMINATE(stack.size() == frame.savedSp(), "Frame non empty.");

    stack.push(val);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::fRet() {
    const auto val = stack.pop();
    TERMINATE(val.type() == Value::Type::FLOAT32,
              "Invalid return type. Required: %s. Found: %s.", Value::F32, val.typeToString());

    auto frame = callStack.leave();
    TERMINATE(stack.size() == frame.savedSp(), "Frame non empty.");

    stack.push(val);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::iStore(Value arg) {
    TERMINATE(stack.nonEmpty(), "ApiStack is empty.");
    const auto a = stack.pop();
    TERMINATE(a.type() == Value::Type::INT32,
              "Incomparable type. Required: %s. Found: %s.", Value::I32, a.typeToString());
    m_local.store(a, arg.value());
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::iPush(Value arg) {
    TERMINATE(arg.type() == Value::Type::INT32,
              "Invalid type. Required: %s. Found: %s.", Value::I32, arg.typeToString());
    stack.push(arg);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::iMul() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    const auto result = a.toInt32() * b.toInt32();
    stack.emplace(result);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::iSub() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    const auto result = b.toInt32() - a.toInt32();
    stack.emplace(result);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::iAdd() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    const auto result = a.toInt32() + b.toInt32();
    stack.emplace(result);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::iDiv() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    ZERO_DIVISION(vm, b.toInt32() != 0);
    const auto result = a.toInt32() / b.toInt32();
    stack.emplace(result);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::iLoad(Value arg) {
    TERMINATE(arg.type() == Value::Type::INT32,
              "Invalid type. Required: %s. Found: %s.", Value::I32, arg.typeToString());
    const auto a = m_local.load(arg.value());
    stack.push(a);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::i2f() {
    const auto val = stack.pop();
    TERMINATE(val.type() == Value::Type::INT32,
              "Invalid type. Required: %s. Found: %s.", Value::I32, val.typeToString());

    stack.emplace((float) val.value());
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::fAdd() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    const auto result = a.toFloat32() + b.toFloat32();
    stack.emplace(result);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::fSub() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    const auto result = a.toFloat32() - b.toFloat32();
    stack.emplace(result);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::fDiv() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    ZERO_DIVISION(vm, b.toFloat32() != 0);
    const auto result = a.toFloat32() / b.toFloat32();
    stack.emplace(result);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::fMult() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    const auto result = a.toFloat32() * b.toFloat32();
    stack.emplace(result);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::fPush(Value arg) {
    TERMINATE(arg.type() == Value::Type::FLOAT32,
              "Invalid type. Required: %s. Found: %s.", Value::F32, arg.typeToString());
    stack.push(arg);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::fStore(Value arg) {
    const auto a = stack.pop();
    TERMINATE(a.type() == Value::Type::FLOAT32,
              "Invalid type. Required: %s. Found: %s.", Value::F32, a.typeToString());
    m_local.store(a, arg.value());
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::fLoad(Value arg) {
    TERMINATE(arg.type() == Value::Type::INT32,
              "Invalid type. Required: %s. Found: %s.", Value::I32, arg.typeToString());
    const auto a = m_local.load(arg.value());
    stack.push(a);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::ldc(Value arg) {
    const auto &string = vm.findString(arg.value());
    stack.push(string.value());
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::rPush(Value arg) {
    TERMINATE(arg.type() == Value::Type::REF,
              "Invalid type. Required: %s. Found: %s.", Value::REF, arg.typeToString());
    stack.push(arg);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::rStore(Value arg) {
    TERMINATE(stack.nonEmpty(), "ApiStack is empty.");
    const auto a = stack.pop();
    TERMINATE(a.type() == Value::Type::REF,
              "Invalid type. Required: %s. Found: %s.", Value::REF, a.typeToString());
    m_local.store(a, arg.value());
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::Cmp() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    stack.emplace(a == b, Value::Type::BOOL);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::CmpnEq() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    stack.emplace(a != b, Value::Type::BOOL);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::Jump(Value arg) {
    const auto cond = stack.pop();
    if (cond.toBool()) {
        callStack.frame().jump(arg.value());
    }
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::Goto(Value arg) {
    callStack.frame().jump(arg.value());
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::And() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    stack.emplace(a.toBool() && b.toBool(), Value::Type::BOOL);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::Or() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    stack.emplace(a.toBool() || b.toBool(), Value::Type::BOOL);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::swap() {
    const auto a = stack.pop();
    const auto b = stack.pop();
    stack.push(a);
    stack.push(b);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::PutField(Value arg) {
    const auto value = stack.pop();
    const auto ref = stack.pop();

    TERMINATE(ref.type() == Value::Type::REF,
              "Invalid type. Required: %s. Found: %s.", Value::REF, ref.typeToString());

    const auto& module = callStack
            .frame()
            .method()
            .module()
            .asModule();

    auto offset = module.offset(arg.value());

    auto inst = reinterpret_cast<Instance *>(ref.value());
    inst->fields[offset] = value;
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::GetField(Value arg) {
    const auto ref = stack.pop();

    TERMINATE(ref.type() == Value::Type::REF,
              "Invalid type. Required: %s. Found: %s.", Value::REF, ref.typeToString());

    const auto& module = callStack
            .frame()
            .method()
            .module()
            .asModule();

    auto offset = module.offset(arg.value());

    auto inst = reinterpret_cast<Instance *>(ref.value());
    stack.push(inst->fields[offset]);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::rLoad(Value arg) {
    TERMINATE(arg.type() == Value::Type::INT32,
              "Invalid type. Required: %s. Found: %s.", Value::I32, arg.typeToString());
    const auto a = m_local.load(arg.value());
    stack.push(a);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::RRet() {
    const auto val = stack.pop();
    TERMINATE(val.type() == Value::Type::REF,
              "Invalid return type. Required: %s. Found: %s.", Value::REF, val.typeToString());

    auto frame = callStack.leave();
    TERMINATE(stack.size() == frame.savedSp(), "Frame non empty.");

    stack.push(val);
    return VmResult::SUCCESS;
}

VmResult BaselineInterpreter::Dup() {
    const auto val = stack.top();
    stack.push(val);
    return VmResult::SUCCESS;
}