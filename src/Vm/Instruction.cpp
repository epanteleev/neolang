#include <Vm/Instruction.h>
#include <Vm/Vm.h>

Instruction Instruction::LDC(const std::string &stringLiteral) {
    ObjString string = ObjString::from(stringLiteral.substr(1, stringLiteral.size() - 2));

    size_t pos = Vm::strings()
            .push(std::move(string));

    return Instruction(OpCode::LDC, Value(pos, Value::Type::REF));
}

Instruction Instruction::PUTFIELD(const std::string &fieldName) {
    size_t pos = Vm::findStr(fieldName.c_str());
    return Instruction(OpCode::PUTFIELD, Value(pos, Value::Type::REF));
}

Instruction Instruction::GETFIELD(const std::string &fieldName) {
    size_t pos = Vm::findStr(fieldName.c_str());
    return Instruction(OpCode::GETFIELD, Value(pos, Value::Type::REF));
}

Instruction Instruction::NEW(const std::string &className) {
    size_t pos = Vm::strings()
            .push(className.c_str());

    return Instruction(OpCode::NEW, Value(pos, Value::Type::REF));
}

Instruction Instruction::CALL(const std::string &module, const std::string &method) {
    ObjString str = ObjString::from(module);
    size_t posCn = Vm::strings()
            .push(std::move(str));

    ObjString str1 = ObjString::from(method);
    size_t posCm = Vm::strings()
            .push(std::move(str1));

    return Instruction(OpCode::CALL, Value(posCn, Value::Type::REF), Value(posCm, Value::Type::REF));
}
