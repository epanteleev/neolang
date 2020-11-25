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

inline static bool parseCallStatic(ObjModule &module, ObjMethod &method, Reader &reader) noexcept {
    std::string className, methodName;
    reader.part(className)
            .expect(Keyword::COLON)
            .expect(Keyword::COLON)
            .part(methodName);
    if (!reader.success()) {
        return false;
    }
    if(methodName.empty() || className.empty()) {
        std::cout << "Error parse call static." << std::endl;
        return false;
    }
    ObjString cn = ObjString::from(className);
    ObjString mn = ObjString::from(methodName);
    size_t posCn = module.addStringConstant(cn);
    size_t posCm = module.addStringConstant(mn);
    method.addInst(Instruction(OpCode::CALLSTATIC, Value(posCn, Type::REF), Value(posCm, Type::REF)));
    return true;
}

bool parseLabel(LabelBuffer& labels, size_t ip, Reader& reader) noexcept {
    std::string label;
    reader.expect(Keyword::DOT)
        .part(label)
        .expect(Keyword::COLON);

    if (reader.error()) {
        std::cout << "Error label parse." << std::endl;
        return false;
    } else if (reader.noMatch()) {
        reader.reset();
        return true;
    }
    labels.add(label, ip);
    return true;
}

static bool parseInsts(ObjModule &module, ObjMethod &method, Reader &reader) noexcept {
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
            reader.part(string);
            if (string.empty()) {
                std::cout << "LDC: expected argument." << std::endl;
                return false;
            }
            ObjString str = ObjString::from(string);
            size_t pos = module.addStringConstant(str);
            method.addInst(Instruction(OpCode::LDC, Value(pos, Type::REF)));
        } else if (instName == IF_EQ) {
            std::string string;
            reader.part(string);
            if (string.empty()) {
                std::cout << "IF_EQ: expected argument." << std::endl;
                return false;
            }
            size_t pos = labels.insert(string);
            method.addInst(Instruction(OpCode::IF_EQ, Value(pos, Type::UNDEFINED)));
        } else if (instName == GOTO) {
            std::string string;
            reader.part(string);
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
        parseLabel(labels, ip, reader);
        instName = reader.getWord();
    }
    resolveLabels(labels, method);
    return true;
}

static bool parseMethod(ObjModule &module, Reader &reader) noexcept {
    std::string methodName;
    reader.expect(Keyword::DEF)
            .part(methodName)
            .expect(Keyword::EQ)
            .expect(Keyword::OPEN_BRACE);
    if (reader.error()) {
        return false;
    } else if (reader.noMatch()) {
        return true;
    }

    auto method = ObjMethod::make(module, methodName.data());
    parseInsts(module, *method, reader);
    module.addMethod(method);

    reader.expect(Keyword::CLOSE_BRACE);
    if (!reader.success()) {
        return false;
    }
    return true;
}

static bool parseModule(Vm &vm, Reader &reader) noexcept {
    std::string className;
    reader.expect(Keyword::CLASS).part(className).expect(Keyword::OPEN_BRACE);
    if (reader.error()) {
        return false;
    } else if (reader.noMatch()) {
        return true;
    }

    auto module = ObjModule::make(ObjString::from(className));
    while (!reader.noMatch()) {
        parseMethod(*module, reader);
    }
    reader.expect(Keyword::CLOSE_BRACE);
    if (reader.error()) {
        return false;
    }
    vm.addModule(module);
    return true;
}

bool Parser::parse(Vm &vm, const std::filesystem::path &path) noexcept {
    Reader reader;
    if (!reader.open(path.string())) {
        std::cerr << "File " << path << " wasn't open." << std::endl;
        return false;
    }
    if (!parseModule(vm, reader)) {
        std::cerr << "Parse error." << std::endl;
        return false;
    }
    return true;
}
