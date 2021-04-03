#include <iostream>
#include <filesystem>
#include "Parser.h"

class LabelBuffer final {
public:
    LabelBuffer() = default;
    ~LabelBuffer() = default;
    LabelBuffer(const LabelBuffer &) = delete;

public:
    using InstPointer = size_t;
    using Identifier = size_t;

public:
    inline std::string &operator[](size_t idx) noexcept {
        ASSERT(m_labels.size() > idx, "Out of boundary.");
        return m_labels[idx];
    }

    Identifier add(std::string &&labelName, size_t ip) noexcept {
        size_t pos = insert(std::move(labelName));
        m_labelMap.insert(std::make_pair(pos, ip));
        return pos;
    }

    Identifier insert(std::string&& labelName) noexcept {
        auto pos = index(labelName);
        if (pos == npos) {
            m_labels.push_back(std::move(labelName));
            return m_labels.size() - 1;
        } else {
            return pos;
        }
    }

    [[nodiscard]]
    Identifier index(const std::string& labelName) const noexcept {
        for (size_t i = 0; i < m_labels.size(); i++) {
            if (m_labels[i] == labelName) return i;
        }
        return npos;
    }

    [[nodiscard]]
    InstPointer position(size_t id) noexcept {
        return m_labelMap[id];
    }

public:
    static constexpr size_t npos = std::numeric_limits<size_t>::max();

private:
    std::vector<std::string> m_labels;
    std::map<Identifier, InstPointer> m_labelMap;
};

bool resolveLabels(LabelBuffer& labels, ObjMethod& module) noexcept {
    InstructionList& list = module.instList();
    for (auto& i: list) {
        if (i.code() == OpCode::JUMP) {
            i = Instruction(OpCode::JUMP, Value(labels.position(i.arg0().value()), Type::REF));
        }
    }
    return true;
}

Instruction Parser::parseCallStatic() {
    std::string className, methodName;
    reader.expectId(className)
            .expect(Keywords::COLON)
            .expect(Keywords::COLON)
            .expectId(methodName);

    size_t posCn = m_vm.addStringConstant(ObjString::from(className));
    size_t posCm = m_vm.addStringConstant(ObjString::from(methodName));
    return Instruction(OpCode::CALLSTATIC, Value(posCn, Type::REF), Value(posCm, Type::REF));
}

std::string Parser::parseLabel() {
    std::string label;

    reader.expectId(label)
        .expect(Keywords::COLON);

    reader.expect(Keywords::NEWLINE);
    return label;
}

InstructionList Parser::parseInstructions(LabelBuffer& labels) {
    size_t ip = 0;
    InstructionList instList;
    while (true) {
        if (reader.match(Keywords::DOT)) {
            labels.add(parseLabel(), ip);
        }
        std::string instName = reader.getWord();
        if (instName.empty()) {
            break;
        }
        if (instName == iADD) {
            instList.emplace_back(OpCode::iADD);
        } else if (instName == iSUB) {
            instList.emplace_back(OpCode::iSUB);
        } else if (instName == iDIV) {
            instList.emplace_back(OpCode::iDIV);
        } else if (instName == iMUL) {
            instList.emplace_back(OpCode::iMUL);
        } else if (instName == iPUSH) {
            int i = reader.getInt();
            instList.emplace_back(OpCode::iPUSH, i);
        } else if (instName == iLOAD) {
            int i = reader.getInt();
            instList.emplace_back(OpCode::iLOAD, i);
        } else if (instName == iSTORE) {
            int i = reader.getInt();
            instList.emplace_back(OpCode::iSTORE, i);
        } else if (instName == iRET) {
            instList.emplace_back(OpCode::iRET);
        } else if (instName == fADD) {
            instList.emplace_back(OpCode::fADD);
        } else if (instName == fSUB) {
            instList.emplace_back(OpCode::fSUB);
        } else if (instName == fMUL) {
            instList.emplace_back(OpCode::fMUL);
        } else if (instName == fDIV) {
            instList.emplace_back(OpCode::fDIV);
        } else if (instName == fPUSH) {
            float i = reader.getFloat();
            instList.emplace_back(OpCode::fPUSH, i);
        } else if (instName == fSTORE) {
            int i = reader.getInt();
            instList.emplace_back(OpCode::fSTORE, i);
        } else if (instName == fLOAD) {
            int i = reader.getInt();
            instList.emplace_back(OpCode::fLOAD, i);
        } else if (instName == fRET) {
            instList.emplace_back(OpCode::fRET);
        } else if (instName == rSTORE) {
            auto i = reader.getULong();
            instList.emplace_back(OpCode::rSTORE, Value(i, Type::REF));
        } else if (instName == rPUSH) {
            uint64_t i = reader.getULong();
            instList.emplace_back(OpCode::rPUSH, Value(i, Type::REF));
        } else if (instName == CALLSTATIC) {
            instList.emplace_back(parseCallStatic());
        } else if (instName == RET) {
            instList.emplace_back(OpCode::RET);
        } else if (instName == LDC) {
            std::string string;
            reader.expectId(string);
            size_t pos = m_vm.addStringConstant(ObjString::from(string));
            instList.emplace_back(OpCode::LDC, Value(pos, Type::REF));
        } else if (instName == JUMP) {
            std::string string;
            reader.expectId(string);
            size_t pos = labels.insert(std::move(string));
            instList.emplace_back(OpCode::JUMP, Value(pos, Type::UNDEFINED));
        } else if (instName == CMPEQ) {
            instList.emplace_back(OpCode::CMPEQ);
        } else {
            std::cerr << "Undefined instruction: " << instName << std::endl;
            UNREACHABLE();
        }

        ip += 1;
        reader.expect(Keywords::NEWLINE);
    }
    return instList;
}

bool Parser::parseMethod(ObjModule &module) {
    std::string methodName;
    if (!reader.match(Keywords::DEF)) {
        return false;
    }
    reader.expectId(methodName)
            .expect(Keywords::EQ)
            .expect(Keywords::OPEN_BRACE);
    reader.match(Keywords::NEWLINE);

    LabelBuffer labels;
    auto insts = parseInstructions(labels);

    auto method = ObjMethod::make(ObjString::from(methodName), std::move(insts));
    resolveLabels(labels, *method);

    module.addMethod(std::move(method));

    reader.expect(Keywords::CLOSE_BRACE);
    reader.match(Keywords::NEWLINE);
    return true;
}

bool Parser::parseModule() {
    std::string className;
    reader.expect(Keywords::CLASS).expectId(className);
    reader.match(Keywords::NEWLINE);
    reader.expect(Keywords::OPEN_BRACE);
    reader.match(Keywords::NEWLINE);

    auto module = ObjModule::make(ObjString::from(className));

    while (parseMethod(*module)) {
        reader.match(Keywords::NEWLINE);
    }

    reader.expect(Keywords::CLOSE_BRACE);

    m_vm.addModule(std::move(module));
    return true;
}

std::unique_ptr<Vm> Parser::parse(const std::filesystem::path &path) {
    auto vm = std::make_unique<Vm>();
    Parser(path, *vm).parseModule();
    return vm;
}

Parser::Parser(const std::filesystem::path &path, Vm& vm) : m_vm(vm) {
    if (!reader.open(path.string())) {
        throw std::invalid_argument("File isn't exist.");
    }
}
