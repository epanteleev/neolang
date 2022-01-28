#include "Parser.h"
#include "vm/VmUtils.h"
#include <fstream>

using namespace detail::lexer;

class LabelBuffer final {
public:
    LabelBuffer() = default;

    ~LabelBuffer() = default;

    LabelBuffer(const LabelBuffer &) = delete;

public:
    using InstPointer = std::size_t;
    using Identifier = std::size_t;

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

    Identifier insert(std::string &&labelName) noexcept {
        auto pos = index(labelName);
        if (pos == npos) {
            m_labels.push_back(std::move(labelName));
            return m_labels.size() - 1;
        } else {
            return pos;
        }
    }

    [[nodiscard]]
    Identifier index(const std::string &labelName) const noexcept {
        for (size_t i = 0; i < m_labels.size(); i++) {
            if (m_labels[i] == labelName) return i;
        }
        return npos;
    }

    [[nodiscard]]
    InstPointer position(std::size_t id) noexcept {
        return m_labelMap[id];
    }

public:
    void resolveLabels(InstructionList &list) noexcept {
        for (auto &i: list) {
            if (i.code() == OpCode::JUMP) {
                i = Instruction(OpCode::JUMP, Value(position(i.arg0().value()), Value::Type::REF));
            } else if (i.code() == OpCode::GOTO) {
                i = Instruction(OpCode::GOTO, Value(position(i.arg0().value()), Value::Type::REF));
            }
        }
    }

public:
    static constexpr size_t npos = std::numeric_limits<size_t>::max();

private:
    std::vector<std::string> m_labels;
    std::map<Identifier, InstPointer> m_labelMap;
};

void Parser::parse(Vm& vm, const std::filesystem::path &path) {
    std::ifstream stream;
    stream.open(path);
    if (!stream.is_open()) {
        throw std::invalid_argument("File was not opened.");
    }

    std::ostringstream s{};
    s << stream.rdbuf();
    auto m = Parser(vm, s.str()).parseModule();
    vm.registerModule(std::move(m));
}

ObjModule::Pointer Parser::parseModule() {
    std::string name;
    std::vector<ObjMethod::Pointer> methods;
    FieldList fields;
    if (lex.is<Tok::CLASS>() && lex.skipSpaces() && lex.is<Tok::STRING>()) {
        name = lex.peek<Tok::STRING>();
        lex.skipSpaces();

        if (!lex.is<Tok::OPEN_BRACE>()) {
            throw LexError(lex, "expect '{'");
        }

        lex.skipSpaces();
        fields = parseFields();
        lex.skipSpaces();
        methods = parseFunctions();
        if (!lex.is<Tok::CLOSE_BRACE>()) {
            throw LexError(lex, "expect '}'");
        }
    } else {
        throw LexError(lex, "expect class declaration");
    }

    auto m = ObjModule::make(ObjString::from(name), std::move(fields));
    for (auto &i: methods) {
        m->addMethod(std::move(i)); //todo
    }
    return m;
}

Parser::FieldList Parser::parseFields() {
    std::size_t offset{};
    FieldList list;
    while (lex.is<Tok::FIELD>()) {
        lex.skipSpaces();
        if (!lex.is<Tok::STRING>()) {
            throw LexError(lex, "expect field type");
        }

        auto type = lex.peek<Tok::STRING>();
        auto t = Value::stringToType(type.c_str());

        if (!lex.is<Tok::COLON>()) {
            throw LexError(lex, "expect ':'");
        }
        lex.skipSpaces();
        if (!lex.is<Tok::STRING>()) {
            throw LexError(lex, "expect field name");
        }
        auto name = lex.peek<Tok::STRING>();
        auto pos = vm.strings().push(name.c_str());

        list.emplace_back(pos, offset, t);
        lex.skipSpaces();
    }
    return list;
}

Parser::MethodsList Parser::parseFunctions() {
    MethodsList funs{};
    while (lex.is<Tok::DEF>()) {
        lex.skipSpaces();
        if (!lex.is<Tok::STRING>()) {
            throw LexError(lex, "expect function name");
        }

        auto name = lex.peek<Tok::STRING>();

        lex.skipSpaces();
        if (!lex.is<Tok::OPEN_BRACE>()) {
            throw LexError(lex, "expect '{'");
        }

        lex.skipSpaces();

        auto i = parseInstructions();

        auto f = ObjMethod::make(ObjString::from(name), std::move(i));
        lex.skipSpaces();
        funs.push_back(std::move(f));
    }
    return funs;
}

InstructionList Parser::parseInstructions() {
    InstructionList list;
    LabelBuffer labels;
    std::int64_t ip = -1;

    while (true) {
        lex.skipSpaces();
        if (lex.is<Tok::POINT>()) {
            if (!lex.is<Tok::STRING>()) {
                throw LexError(lex, "expect label name");
            }
            labels.add(lex.peek<Tok::STRING>(), ip);
            if (!lex.is<Tok::COLON>()) {
                throw LexError(lex, "expect ':'");
            }
            continue;
        }
        ip += 1;
        if (expect(OpCode::AND)) {
            list.emplace_back(OpCode::AND);
            continue;
        } else if (expect(OpCode::iPUSH)) {
            lex.skipSpaces();

            auto intgr = get<Tok::INTEGER>("expect u32 value");
            list.emplace_back(OpCode::iPUSH, (int) intgr); //Todo unsafe cast

            continue;
        } else if (expect(OpCode::iADD)) {
            list.emplace_back(OpCode::iADD);
            continue;
        } else if (expect(OpCode::iSUB)) {
            list.emplace_back(OpCode::iSUB);
            continue;
        } else if (expect(OpCode::iMUL)) {
            list.emplace_back(OpCode::iMUL);
            continue;
        } else if (expect(OpCode::iDIV)) {
            list.emplace_back(OpCode::iDIV);
            continue;
        } else if (expect(OpCode::iSTORE)) {
            lex.skipSpaces();
            auto intgr = get<Tok::INTEGER>("expect u32 value");
            list.emplace_back(OpCode::iSTORE, (int) intgr); //Todo unsafe cast

            continue;
        } else if (expect(OpCode::iLOAD)) {
            lex.skipSpaces();
            auto intgr = get<Tok::INTEGER>("expect u32 value");
            list.emplace_back(OpCode::iLOAD, (int) intgr); //Todo unsafe cast

            continue;
        } else if (expect(OpCode::iRET)) {
            list.emplace_back(OpCode::iRET);
            continue;
        } else if (expect(OpCode::fPUSH)) {
            lex.skipSpaces();

            auto intgr = get<Tok::FLOAT>("expect float value");
            list.emplace_back(OpCode::fPUSH, (float) intgr); //Todo unsafe cast

            continue;
        } else if (expect(OpCode::fADD)) {
            list.emplace_back(OpCode::fADD);
            continue;
        } else if (expect(OpCode::fSUB)) {
            list.emplace_back(OpCode::fSUB);
            continue;
        } else if (expect(OpCode::fMUL)) {
            list.emplace_back(OpCode::fMUL);
            continue;
        } else if (expect(OpCode::fDIV)) {
            list.emplace_back(OpCode::fDIV);
            continue;
        } else if (expect(OpCode::fSTORE)) {
            lex.skipSpaces();
            auto intgr = get<Tok::INTEGER>("expect u32 value");
            list.emplace_back(OpCode::fSTORE, (int) intgr); //Todo unsafe cast

            continue;
        } else if (expect(OpCode::fLOAD)) {
            lex.skipSpaces();
            auto intgr = get<Tok::INTEGER>("expect u32 value");
            list.emplace_back(OpCode::fLOAD, (int) intgr); //Todo unsafe cast

            continue;
        } else if (expect(OpCode::fRET)) {
            list.emplace_back(OpCode::fRET);
            continue;
        } else if (expect(OpCode::RET)) {
            list.emplace_back(OpCode::RET);
            continue;
        } else if (expect(OpCode::CALL)) {
            lex.skipSpaces();
            std::string module = get<Tok::STRING>("expect module name");

            if (!(lex.is<Tok::COLON>() && lex.is<Tok::COLON>())) {
                throw LexError(lex, "expect '::'");
            }

            std::string method = get<Tok::STRING>("expect method name");

            list.emplace_back(vm::instruction::CALL(vm, module, method));
            continue;
        } else if (expect(OpCode::RRET)) {
            list.emplace_back(OpCode::RRET);
            continue;
        } else if (expect(OpCode::rSTORE)) {
            lex.skipSpaces();
            auto intgr = get<Tok::INTEGER>("expect u32 value");
            list.emplace_back(OpCode::rSTORE, (int) intgr); //Todo unsafe cast
            continue;

        } else if (expect(OpCode::rLOAD)) {
            lex.skipSpaces();
            auto intgr = get<Tok::INTEGER>("expect u32 value");
            list.emplace_back(OpCode::rLOAD, (int) intgr); //Todo unsafe cast
            continue;

        } else if (expect(OpCode::LDC)) {
            lex.skipSpaces();
            auto intgr = get<Tok::STRING_LITERAL>("expect string literal");
            list.emplace_back(vm::instruction::LDC(vm, intgr)); //Todo unsafe cast
            continue;

        } else if (expect(OpCode::SWAP)) {
            lex.skipSpaces();
            list.emplace_back(OpCode::SWAP);
            continue;

        } else if (expect(OpCode::JUMP)) {
            lex.skipSpaces();
            auto s = get<Tok::STRING>("expect label name");
            std::size_t pos = labels.insert(std::move(s));
            list.emplace_back(OpCode::JUMP, Value(pos, Value::Type::UNDEFINED));
            continue;
        } else if (expect(OpCode::GOTO)) {
            lex.skipSpaces();
            auto s = get<Tok::STRING>("expect label name");
            std::size_t pos = labels.insert(std::move(s));
            list.emplace_back(OpCode::GOTO, Value(pos, Value::Type::UNDEFINED));
            continue;
        } else if (expect(OpCode::CMPEQ)) {
            list.emplace_back(OpCode::CMPEQ);
            continue;
        } else if (expect(OpCode::CMPNEQ)) {
            list.emplace_back(OpCode::CMPNEQ);
            continue;
        } else if (expect(OpCode::PUTFIELD)) {
            lex.skipSpaces();
            auto s = get<Tok::STRING>("expect field name");
            list.emplace_back(vm::instruction::PUTFIELD(vm, s));
            continue;
        } else if (expect(OpCode::GETFIELD)) {
            lex.skipSpaces();
            auto s = get<Tok::STRING>("expect field name");
            list.emplace_back(vm::instruction::GETFIELD(vm, s));
            continue;
        } else if (expect(OpCode::NEW)) {
            lex.skipSpaces();
            auto s = get<Tok::STRING>("expect class name");
            list.emplace_back(vm::instruction::NEW(vm, s));
            continue;
        } else if (expect(OpCode::DUP)) {
            list.emplace_back(OpCode::DUP);
            continue;
        }

        if (lex.is<Tok::CLOSE_BRACE>()) {
            break;
        } else {
            throw LexError(lex, "undefined instruction");
        }
    }
    labels.resolveLabels(list);
    return list;
}
