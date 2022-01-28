#pragma once

#include <cstdint>
#include "eternal.h"

/**
 * Represent opcodes of virtual machine.
 * It is similar on JVM https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html.
 * @minium2
 */
enum class OpCode : uint8_t {
    UNDEFINED = 0,
    iADD,
    iSUB,
    iMUL,
    iDIV,
    iPUSH,
    iSTORE,
    iLOAD,
    iRET,
    i2F,
    fADD,
    fSUB,
    fMUL,
    fDIV,
    fPUSH,
    fSTORE,
    fLOAD,
    fRET,
    f2I, // Unimplemented
    CALL,
    INVOKE,
    NEW,
    LDC,
    SWAP,
    rPUSH,
    rSTORE,
    rLOAD,
    RRET,
    CMPEQ,
    CMPNEQ,
    JUMP,
    GOTO,
    AND,
    OR,
    PUTFIELD,
    GETFIELD,
    DUP,
    RET,
};

constexpr const char *iADD       = "iadd";
constexpr const char *iSUB       = "isub";
constexpr const char *iMUL       = "imul";
constexpr const char *iDIV       = "idiv";
constexpr const char *iPUSH      = "ipush";
constexpr const char *iSTORE     = "istore";
constexpr const char *iLOAD      = "iload";
constexpr const char *iRET       = "iret";
constexpr const char *I2F        = "i2f";
constexpr const char *fADD       = "fadd";
constexpr const char *fSUB       = "fsub";
constexpr const char *fMUL       = "fmul";
constexpr const char *fDIV       = "fdiv";
constexpr const char *fPUSH      = "fpush";
constexpr const char *fSTORE     = "fstore";
constexpr const char *fLOAD      = "fload";
constexpr const char *fRET       = "fret";
constexpr const char *CALL       = "call";
constexpr const char *INVOKE     = "invoke";
constexpr const char *NEW        = "new";
constexpr const char *RET        = "ret";
constexpr const char *LDC        = "ldc";
constexpr const char *SWAP       = "swap";
constexpr const char *rPUSH      = "rpush";
constexpr const char *rSTORE     = "rstore";
constexpr const char *rLOAD     = "rload";
constexpr const char *CMPEQ      = "cmpeq";
constexpr const char *CMPNEQ     = "cmpneq";
constexpr const char *UNDEFINED  = "UNDEFINED";
constexpr const char *JUMP       = "jmp";
constexpr const char *GOTO       = "goto";
constexpr const char *AND        = "and";
constexpr const char *OR         = "or";
constexpr const char *PUTFIELD   = "putfield";
constexpr const char *GETFIELD   = "getfield";
constexpr const char *RRET       = "rret";
constexpr const char *DUP        = "dup";


static constexpr auto maps = constexpression::map<constexpression::eternal::string, OpCode> ({
                {iADD, OpCode::iADD},
                {iADD, OpCode::iADD},
                {iSUB, OpCode::iSUB},
                {iMUL, OpCode::iMUL},
                {iDIV, OpCode::iDIV},
                {iPUSH, OpCode::iPUSH},
                {iSTORE, OpCode::iSTORE},
                {iLOAD, OpCode::iLOAD},
                {iRET, OpCode::iRET},
                {I2F, OpCode::i2F},
                {fADD, OpCode::fADD},
                {fSUB, OpCode::fSUB},
                {fMUL, OpCode::fMUL},
                {fDIV, OpCode::fDIV},
                {fPUSH, OpCode::fPUSH},
                {fSTORE, OpCode::fSTORE},
                {fLOAD, OpCode::fLOAD},
                {fRET, OpCode::fRET},
                {CALL, OpCode::CALL},
                {INVOKE, OpCode::INVOKE},
                {NEW, OpCode::NEW},
                {LDC, OpCode::LDC},
                {SWAP, OpCode::SWAP},
                {rPUSH, OpCode::rPUSH},
                {rSTORE, OpCode::rSTORE},
                {rLOAD, OpCode::rLOAD},
                {JUMP, OpCode::JUMP},
                {RET, OpCode::RET},
                {CMPEQ, OpCode::CMPEQ},
                {CMPNEQ, OpCode::CMPNEQ},
                {GOTO, OpCode::GOTO},
                {AND, OpCode::AND},
                {OR, OpCode::OR},
                {PUTFIELD, OpCode::PUTFIELD},
                {GETFIELD, OpCode::GETFIELD},
                {RRET, OpCode::RRET},
                {DUP, OpCode::DUP},
        });

constexpr OpCode findOpCode(const char* instr) {
    return maps.at(instr);
}

inline constexpr const char *opCodeToString(OpCode opcode) noexcept {
    switch (opcode) {
        case OpCode::iADD:       return iADD;
        case OpCode::iSUB:       return iSUB;
        case OpCode::iMUL:       return iMUL;
        case OpCode::iDIV:       return iDIV;
        case OpCode::iPUSH:      return iPUSH;
        case OpCode::iSTORE:     return iSTORE;
        case OpCode::iLOAD:      return iLOAD;
        case OpCode::iRET:       return iRET;
        case OpCode::i2F:        return I2F;
        case OpCode::fADD:       return fADD;
        case OpCode::fSUB:       return fSUB;
        case OpCode::fMUL:       return fMUL;
        case OpCode::fDIV:       return fDIV;
        case OpCode::fPUSH:      return fPUSH;
        case OpCode::fSTORE:     return fSTORE;
        case OpCode::fLOAD:      return fLOAD;
        case OpCode::fRET:       return fRET;
        case OpCode::CALL:       return CALL;
        case OpCode::INVOKE:     return INVOKE;
        case OpCode::NEW:        return NEW;
        case OpCode::LDC:        return LDC;
        case OpCode::SWAP:       return SWAP;
        case OpCode::rPUSH:      return rPUSH;
        case OpCode::rSTORE:     return rSTORE;
        case OpCode::rLOAD:      return rLOAD;
        case OpCode::JUMP:       return JUMP;
        case OpCode::RET:        return RET;
        case OpCode::CMPEQ:      return CMPEQ;
        case OpCode::CMPNEQ:     return CMPNEQ;
        case OpCode::GOTO:       return GOTO;
        case OpCode::AND:        return AND;
        case OpCode::OR:         return OR;
        case OpCode::PUTFIELD:   return PUTFIELD;
        case OpCode::GETFIELD:   return GETFIELD;
        case OpCode::RRET:       return RRET;
        case OpCode::DUP:        return DUP;
        default:                 return UNDEFINED;
    }
}
