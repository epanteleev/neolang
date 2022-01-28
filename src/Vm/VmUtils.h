#pragma once


namespace vm::instruction {
    Instruction LDC(Vm& vm, const std::string &stringLiteral) {
        ObjString string = ObjString::from(stringLiteral);

        size_t pos = vm.strings()
                .push(std::move(string));

        return Instruction(OpCode::LDC, Value(pos, Value::Type::REF));
    }

    Instruction PUTFIELD(Vm& vm, const std::string &fieldName) {
        size_t pos = vm.findStr(fieldName.c_str());
        return Instruction(OpCode::PUTFIELD, Value(pos, Value::Type::REF));
    }

    Instruction GETFIELD(Vm& vm, const std::string &fieldName) {
        std::size_t pos = vm.findStr(fieldName.c_str());
        return Instruction(OpCode::GETFIELD, Value(pos, Value::Type::REF));
    }

    Instruction NEW(Vm& vm, const std::string &className) {
        size_t pos = vm.strings()
                .push(className.c_str());

        return Instruction(OpCode::NEW, Value(pos, Value::Type::REF));
    }

    Instruction CALL(Vm& vm, const std::string &module, const std::string &method) {
        ObjString str = ObjString::from(module);
        size_t posCn = vm.strings()
                .push(std::move(str));

        ObjString str1 = ObjString::from(method);
        size_t posCm = vm.strings()
                .push(std::move(str1));

        return Instruction(OpCode::CALL, Value(posCn, Value::Type::REF), Value(posCm, Value::Type::REF));
    }
}