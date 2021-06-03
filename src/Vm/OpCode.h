#pragma once

#include <cstdint>

/**
 * Represent opcodes of virtual machine.
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
    I2F,
    fADD,
    fSUB,
    fMUL,
    fDIV,
    fPUSH,
    fSTORE,
    fLOAD,
    fRET,
    CALL,
    INVOKE,
    NEW,
    LDC,
    SWAP,
    rPUSH,
    rSTORE,
    RET,
    CMPEQ,
    JUMP,
    GOTO,
    AND,
    OR
};

constexpr const char *iADD       = "iADD";
constexpr const char *iSUB       = "iSUB";
constexpr const char *iMUL       = "iMUL";
constexpr const char *iDIV       = "iDIV";
constexpr const char *iPUSH      = "iPUSH";
constexpr const char *iSTORE     = "iSTORE";
constexpr const char *iLOAD      = "iLOAD";
constexpr const char *iRET       = "iRET";
constexpr const char *I2F        = "I2F";
constexpr const char *fADD       = "fADD";
constexpr const char *fSUB       = "fSUB";
constexpr const char *fMUL       = "fMUL";
constexpr const char *fDIV       = "fDIV";
constexpr const char *fPUSH      = "fPUSH";
constexpr const char *fSTORE     = "fSTORE";
constexpr const char *fLOAD      = "fLOAD";
constexpr const char *fRET       = "fRET";
constexpr const char *CALL       = "CALL";
constexpr const char *INVOKE     = "INVOKE";
constexpr const char *NEW        = "NEW";
constexpr const char *RET        = "RET";
constexpr const char *LDC        = "LDC";
constexpr const char *SWAP       = "swap";
constexpr const char *rPUSH      = "rPUSH";
constexpr const char *rSTORE     = "rSTORE";
constexpr const char *CMPEQ      = "CMPEQ";
constexpr const char *UNDEFINED  = "UNDEFINED";
constexpr const char *JUMP       = "JUMP";
constexpr const char *GOTO       = "GOTO";
constexpr const char *AND        = "AND";
constexpr const char *OR         = "OR";

inline constexpr const char *opCodeToString(OpCode opcode) noexcept {
    switch (opcode) {
        case OpCode::iADD:       return iADD;
        case OpCode::iSUB:       return iSUB;
        case OpCode::iMUL:       return iMUL;
        case OpCode::iDIV:       return iDIV;
        case OpCode::iPUSH:      return iPUSH;
        case OpCode::iSTORE:     return iSTORE;
        case OpCode::iRET:       return iRET;
        case OpCode::I2F:        return I2F;
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
        case OpCode::JUMP:       return JUMP;
        case OpCode::RET:        return RET;
        case OpCode::CMPEQ:      return CMPEQ;
        case OpCode::GOTO:       return GOTO;
        case OpCode::AND:        return AND;
        case OpCode::OR:         return OR;
        default:                 return UNDEFINED;
    }
}
