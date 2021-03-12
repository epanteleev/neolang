#include <iostream>
#include <filesystem>
#include "Parser/Parser.h"

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

    Identifier add(std::string &labelName, size_t ip) noexcept {
        size_t pos = insert(labelName);
        m_labelMap.insert(std::make_pair(pos, ip));
        return pos;
    }

    Identifier insert(std::string& labelName) noexcept {
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
    InstList& list = module.instList();
    for (auto& i: list) {
        if (i.code() == OpCode::IF_EQ) {
            i = Instruction(OpCode::IF_EQ, Value(labels.position(i.arg0().value()), Type::REF));
        } else if (i.code() == OpCode::GOTO) {
            i = Instruction(OpCode::GOTO, Value(labels.position(i.arg0().value()), Type::REF));
        }
    }
    return true;
}

inline static bool parseCallStatic(ObjModule &module, ObjMethod &method, Reader &reader) {
    std::string className, methodName;
    reader.expectId(className)
            .expect(Keywords::COLON)
            .expect(Keywords::COLON)
            .expectId(methodName);

    if(methodName.empty() || className.empty()) {
        std::cout << "Error parse call static." << std::endl;
        return false;
    }
    ObjString cn = ObjString::from(className);
    ObjString mn = ObjString::from(methodName);
    size_t posCn = module.addStringConstant(std::move(cn));
    size_t posCm = module.addStringConstant(std::move(mn));
    method.addInst(Instruction(OpCode::CALLSTATIC, Value(posCn, Type::REF), Value(posCm, Type::REF)));
    return true;
}

bool parseLabel(LabelBuffer& labels, size_t ip, Reader& reader) {
    std::string label;
    if (!reader.match(Keywords::DOT)) {
        return true;
    }
    reader.expectId(label)
        .expect(Keywords::COLON);

    labels.add(label, ip);
    reader.expect(Keywords::NEWLINE);
    return true;
}

static bool parseInsts(ObjModule &module, ObjMethod &method, Reader &reader) {
    size_t ip = 0;
    LabelBuffer labels;
    parseLabel(labels, ip, reader);
    std::string instName = reader.getWord();
    while (!instName.empty()) {
        if (instName == iADD) {
            method.addInst(Instruction(OpCode::iADD));
        } else if (instName == iSUB) {
            method.addInst(Instruction(OpCode::iSUB));
        } else if (instName == iDIV) {
            method.addInst(Instruction(OpCode::iDIV));
        } else if (instName == iMUL) {
            method.addInst(Instruction(OpCode::iMUL));
        } else if (instName == iPUSH) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::iPUSH, i));
        } else if (instName == iLOAD) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::iLOAD, i));
        } else if (instName == iSTORE) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::iSTORE, i));
        } else if (instName == iRET) {
            method.addInst(Instruction(OpCode::iRET));
        } else if (instName == fADD) {
            method.addInst(Instruction(OpCode::fADD));
        } else if (instName == fSUB) {
            method.addInst(Instruction(OpCode::fSUB));
        } else if (instName == fMUL) {
            method.addInst(Instruction(OpCode::fMUL));
        } else if (instName == fDIV) {
            method.addInst(Instruction(OpCode::fDIV));
        } else if (instName == fPUSH) {
            float i = reader.getFloat();
            method.addInst(Instruction(OpCode::fPUSH, i));
        } else if (instName == fSTORE) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::fSTORE, i));
        } else if (instName == fLOAD) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::fLOAD, i));
        } else if (instName == fRET) {
            method.addInst(Instruction(OpCode::fRET));
        } else if (instName == rSTORE) {
            auto i = reader.getULong();
            method.addInst(Instruction(OpCode::rSTORE, Value(i, Type::REF)));
        } else if (instName == rPUSH) {
            uint64_t i = reader.getULong();
            method.addInst(Instruction(OpCode::rPUSH, Value(i, Type::REF)));
        } else if (instName == CALLSTATIC) {
            if (!parseCallStatic(module, method, reader)) {
                return false;
            }
        } else if (instName == RET) {
            method.addInst(Instruction(OpCode::RET));
        } else if (instName == LDC) {
            std::string string;
            reader.expectId(string);
            if (string.empty()) {
                std::cout << "LDC: expected argument." << std::endl;
                return false;
            }
            ObjString str = ObjString::from(string);
            size_t pos = module.addStringConstant(std::move(str));
            method.addInst(Instruction(OpCode::LDC, Value(pos, Type::REF)));
        } else if (instName == IF_EQ) {
            std::string string;
            reader.expectId(string);
            if (string.empty()) {
                std::cout << "IF_EQ: expected argument." << std::endl;
                return false;
            }
            size_t pos = labels.insert(string);
            method.addInst(Instruction(OpCode::IF_EQ, Value(pos, Type::UNDEFINED)));
        } else if (instName == GOTO) {
            std::string string;
            reader.expectId(string);
            if (string.empty()) {
                std::cout << "GOTO: expected argument." << std::endl;
                return false;
            }
            size_t pos = labels.insert(string);
            method.addInst(Instruction(OpCode::GOTO, Value(pos, Type::UNDEFINED)));
        } else {
            std::cerr << "Undefined instruction: " << instName << std::endl;
            UNREACHABLE();
        }
        ip++;
        reader.expect(Keywords::NEWLINE);
        parseLabel(labels, ip, reader);
        instName = reader.getWord();
    }
    resolveLabels(labels, method);
    return true;
}

static bool parseMethod(ObjModule &module, Reader &reader) {
    std::string methodName;
    if (!reader.match(Keywords::DEF)) {
        return false;
    }
    reader.expectId(methodName)
            .expect(Keywords::EQ)
            .expect(Keywords::OPEN_BRACE);
    reader.match(Keywords::NEWLINE);

    auto method = ObjMethod::make(methodName.data());
    parseInsts(module, *method, reader);
    module.addMethod(std::move(method));

    reader.expect(Keywords::CLOSE_BRACE);
    reader.match(Keywords::NEWLINE);
    return true;
}

static bool parseModule(Vm &vm, Reader &reader) {
    std::string className;
    reader.expect(Keywords::CLASS).expectId(className);
    reader.match(Keywords::NEWLINE);
    reader.expect(Keywords::OPEN_BRACE);
    reader.match(Keywords::NEWLINE);

    auto module = ObjModule::make(ObjString::from(className));

    while (parseMethod(*module, reader)) {
        reader.match(Keywords::NEWLINE);
    }

    reader.expect(Keywords::CLOSE_BRACE);

    vm.addModule(std::move(module));
    return true;
}

std::unique_ptr<Vm> Parser::parse(const std::filesystem::path &path) {
    Reader reader;
    if (!reader.open(path.string())) {
        std::cerr << "File " << path << " wasn't open." << std::endl;
        throw std::invalid_argument("File isn't exist.");
    }
    auto vm = std::make_unique<Vm>();
    parseModule(*vm, reader);
    return vm;
}
