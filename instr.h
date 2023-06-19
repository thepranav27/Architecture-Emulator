#ifndef _INSTR_H_
#define _INSTR_H_

#include <stdint.h>
#include <stdbool.h>
#include "reg.h"
#include "mem.h"

#define EXTRACT(src, mask, shift) (((src) & (mask)) >> (shift))
#define GETBF(src, frompos, width) (((src) & (((1 << (width)) - 1) << (frompos))) >> (frompos))

typedef enum opcode {
    OP_NONE,
    OP_ADD,
    OP_ADRP,
    OP_MOV,
    OP_MOVZ,
    OP_LDR,
    OP_STRB,
    OP_LDRB,
    OP_CBNZ,
    OP_RET,
    OP_CMP_SHIFT,
    OP_SUBS_SHIFT,
    OP_BCOND,
    OP_NOP,
    OP_B,
    OP_CMP_IMM,
    OP_SUBS_IMM,
    OP_BL,
    OP_BLR,
    OP_BR,
    OP_SUB_IMM,
    OP_CSEL,
    OP_MOVN,
    OP_SUB_SHIFT,
    OP_ORR_SHIFT,
    OP_MOV_SHIFT,
    OP_AND,
    OP_LDRP,
    OP_STR,
    OP_CBZ,
    OP_LDR3,
    OP_ERROR = -1
} opcode_t;

typedef enum cond {
    C_EQ,
    C_NE,
    C_CS,
    C_CC,
    C_MI,
    C_PL,
    C_VS,
    C_VC,
    C_HI,
    C_LS,
    C_GE,
    C_LT,
    C_GT,
    C_LE,
    C_AL,
    C_NV,
    C_ERROR = -1
} cond_t;

typedef enum proc_stage {
    S_FETCH,
    S_DECODE,
    S_EXECUTE,
    S_MEMORY,
    S_WBACK,
    S_UPDATE_PC,
    S_ERROR = -1
} proc_stage_t;

typedef struct instr {
// The following fields are relevant to FETCH.
    int32_t     insnbits;   // Bits of instruction.
// The following fields are relevant to DECODE & READ REGISTER FILE.
    opcode_t    op;         // Opcode.
    cond_t      cond;       // Branch condition. Relevant only for branch instructions.
    reg_t       *dst;       // Destination register (the one that is written in WB).
    reg_t       *src1;      // Source register 1 (source of first input operand of EX).
    reg_t       *src2;      // Source register 2 (source of second input operand of EX, or source of value for MEM write).
    int64_t     imm;        // Immediate operand (second input operand of EX).
    uint8_t     shift;      // Shift amount, if any.
    uint64_t    next_PC;    // Address of next instruction to be executed. Generally PC+4, but not for B; undefined for RET.
    uint64_t    branch_PC;  // Address of branch target, if any. Undefined for RET.
    bool        wback;      // Flag relevant for pre- and post-index memory addressing.
    bool        postindex;  // Flag relevant for pre- and post-index memory addressing.
    val_t       opnd1;      // From src1.
    val_t       opnd2;      // From src2 or imm.
// The following fields are relevant to EXECUTE.
    val_t       val_ex;     // Value output of ALU.
    val_t       cc;         // Condition code output of ALU.
// The following fields are relevant to ACCESS MEMORY.
    val_t       val_mem;    // Value returned by memory read.
    mrc_t       mrc;        // Return code for memory read/write.
// The following fields are relevant to WRITE BACK REGISTER FILE. (NONE)
// The following fields are relevant to UPDATE PC. (NONE)
} instr_t;

extern void fetch_instr(instr_t * const);
extern void decode_instr(instr_t *const);
extern void execute_instr(instr_t *const);
extern void memory_instr(instr_t *const);
extern void wback_instr(instr_t *const);
extern void update_pc_instr(instr_t *const);
extern void show_instr(const instr_t *, const proc_stage_t);
#endif