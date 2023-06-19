#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "err_handler.h"
#include "instr.h"
#include "machine.h"
#include "instructions.h"

extern machine_t guest;

/*
 * Fetch.
 */

void fetch_instr(instr_t *const insn) {
    insn->insnbits = mem_read_I(guest.proc->PC.bits->xval);
    return;
}

/*
 * Decode and read operands: Level 0.
 * Lower levels are in the instr/ subdirectory.
 */

void decode_instr(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    // bits 28:25 (C4.1)
    unsigned char op0 = EXTRACT(instr, 0x1E000000U, 25);

    switch (op0) {
        case 0: MISSING(); break;
        case 1: break;
        case 2: MISSING(); break;
        case 3: break;
        case 8: case 9: decode_DPI(insn); break;
        case 10: case 11: decode_B_EG_SYS(insn); break;
        case 4: case 6: case 12: case 14: decode_LD_ST(insn); break;
        case 5: case 13: decode_DPR(insn); break;
        case 7: case 15: MISSING(); break;
        default: assert(false); break;
    }
    return;
}

/*
 * Execute.
 */

void execute_instr(instr_t *const insn) {
    switch(insn->op) {
        case OP_ADD:    execute_ADD_IMM_64(insn); break;
        case OP_ADRP:   execute_ADRP(insn); break;
        case OP_MOV: 
        case OP_MOVZ:   switch(insn->insnbits >> 31) {
                            case 0: execute_MOVZ_32(insn); break;
                            case -1: execute_MOVZ_64(insn); break;
                        }
                        break;
        case OP_LDR:    execute_LDR_IMM_UOFF_64(insn); break;
        case OP_STRB:   execute_STRB_IMM_UOFF_32(insn); break;
        case OP_LDRB:   execute_LDRB_IMM_PRE_INDEX_32(insn); break;
        case OP_CBNZ:   execute_CBNZ_32(insn); break;
        case OP_RET:    execute_RET(insn); break;
        case OP_CMP_SHIFT:
        case OP_SUBS_SHIFT: execute_SUBS_32_SHIFT(insn); break;
        case OP_BCOND: execute_BCOND(insn); break;
        case OP_NOP: execute_NOP(insn); break;
        case OP_B: execute_B(insn); break;
        case OP_CMP_IMM:
        case OP_SUBS_IMM: execute_SUBS_32_IMM(insn); break;
        case OP_BL: execute_BL(insn); break;
        case OP_BLR: execute_BLR(insn); break;
        case OP_BR: execute_BR(insn); break;
        case OP_SUB_IMM: execute_SUB_32_IMM(insn); break;
        case OP_MOVN: execute_MOVN_32(insn); break;
        case OP_CSEL: execute_CSEL_32(insn); break;
        case OP_SUB_SHIFT: execute_SUB_32_SHIFT(insn); break;
        case OP_MOV_SHIFT:
        case OP_ORR_SHIFT: execute_ORR_SHIFT(insn); break;
        case OP_AND: execute_AND_32_IMM(insn); break;
        case OP_LDRP: execute_LDR_IMM_POST_32(insn); break;
        case OP_STR: execute_STR_IMM_UOFF_32(insn); break;
        case OP_CBZ: execute_CBZ_32(insn); break;
        case OP_LDR3: execute_LDR_IMM_UOFF_32(insn); break;
        case OP_NONE:
        case OP_ERROR:  assert(false); break;
    }
}

/*
 * Access memory.
 */

void memory_instr(instr_t *const insn) {
    switch(insn->op) {
        case OP_ADD:    memory_ADD_IMM_64(insn); break;
        case OP_ADRP:   memory_ADRP(insn); break;
        case OP_MOV: 
        case OP_MOVZ:   switch(insn->insnbits >> 31) {
                            case 0: memory_MOVZ_32(insn); break;
                            case -1: memory_MOVZ_64(insn); break;
                        }
                        break;
        case OP_LDR:    memory_LDR_IMM_UOFF_64(insn); break;
        case OP_STRB:   memory_STRB_IMM_UOFF_32(insn); break;
        case OP_LDRB:   memory_LDRB_IMM_PRE_INDEX_32(insn); break;
        case OP_CBNZ:   memory_CBNZ_32(insn); break;
        case OP_RET:    memory_RET(insn); break;
        case OP_CMP_SHIFT:
        case OP_SUBS_SHIFT: memory_SUBS_32_SHIFT(insn); break;
        case OP_BCOND: memory_BCOND(insn); break;
        case OP_NOP: memory_NOP(insn); break;
        case OP_B: memory_B(insn); break;
        case OP_CMP_IMM:
        case OP_SUBS_IMM: memory_SUBS_32_IMM(insn); break;
        case OP_BL: memory_BL(insn); break;
        case OP_BLR: memory_BLR(insn); break;
        case OP_BR: memory_BR(insn); break;
        case OP_SUB_IMM: memory_SUB_32_IMM(insn); break;
        case OP_MOVN: memory_MOVN_32(insn); break;
        case OP_CSEL: memory_CSEL_32(insn); break;
        case OP_SUB_SHIFT: memory_SUB_32_SHIFT(insn); break;
        case OP_MOV_SHIFT:
        case OP_ORR_SHIFT: memory_ORR_SHIFT(insn); break;
        case OP_AND: memory_AND_32_IMM(insn); break;
        case OP_LDRP: memory_LDR_IMM_POST_32(insn); break;
        case OP_STR: memory_STR_IMM_UOFF_32(insn); break;
        case OP_CBZ: memory_CBZ_32(insn); break;
        case OP_LDR3: memory_LDR_IMM_UOFF_32(insn); break;
        case OP_NONE:
        case OP_ERROR:  assert(false); break;
    }
}

/*
 * Write back to register file.
 */

void wback_instr(instr_t *const insn) {
    switch(insn->op) {
        case OP_ADD:    wback_ADD_IMM_64(insn); break;
        case OP_ADRP:   wback_ADRP(insn); break;
        case OP_MOV: 
        case OP_MOVZ:   switch(insn->insnbits >> 31) {
                            case 0: wback_MOVZ_32(insn); break;
                            case -1: wback_MOVZ_64(insn); break;
                        }
                        break;
        case OP_LDR:    wback_LDR_IMM_UOFF_64(insn); break;
        case OP_STRB:   wback_STRB_IMM_UOFF_32(insn); break;
        case OP_LDRB:   wback_LDRB_IMM_PRE_INDEX_32(insn); break;
        case OP_CBNZ:   wback_CBNZ_32(insn); break;
        case OP_RET:    wback_RET(insn); break;
        case OP_CMP_SHIFT:
        case OP_SUBS_SHIFT: wback_SUBS_32_SHIFT(insn); break;
        case OP_BCOND: wback_BCOND(insn); break;
        case OP_NOP: wback_NOP(insn); break;
        case OP_B: wback_B(insn); break;
        case OP_CMP_IMM:
        case OP_SUBS_IMM: wback_SUBS_32_IMM(insn); break;
        case OP_BL: wback_BL(insn); break;
        case OP_BLR: wback_BLR(insn); break;
        case OP_BR: wback_BR(insn); break;
        case OP_SUB_IMM: wback_SUB_32_IMM(insn); break;
        case OP_MOVN: wback_MOVN_32(insn); break;
        case OP_CSEL: wback_CSEL_32(insn); break;
        case OP_SUB_SHIFT: wback_SUB_32_SHIFT(insn); break;
        case OP_MOV_SHIFT:
        case OP_ORR_SHIFT: wback_ORR_SHIFT(insn); break;
        case OP_AND: wback_AND_32_IMM(insn); break;
        case OP_LDRP: wback_LDR_IMM_POST_32(insn); break;
        case OP_STR: wback_STR_IMM_UOFF_32(insn); break;
        case OP_CBZ: wback_CBZ_32(insn); break;
        case OP_LDR3: wback_LDR_IMM_UOFF_32(insn); break;
        case OP_NONE:
        case OP_ERROR:  assert(false); break;
    }
}

/*
 * Update PC.
 */

void update_pc_instr(instr_t *const insn) {
    switch(insn->op) {
        case OP_ADD:    update_pc_ADD_IMM_64(insn); break;
        case OP_ADRP:   update_pc_ADRP(insn); break;
        case OP_MOV: 
        case OP_MOVZ:   switch(insn->insnbits >> 31) {
                            case 0: update_pc_MOVZ_32(insn); break;
                            case -1: update_pc_MOVZ_64(insn); break;
                        }
                        break;
        case OP_LDR:    update_pc_LDR_IMM_UOFF_64(insn); break;
        case OP_STRB:   update_pc_STRB_IMM_UOFF_32(insn); break;
        case OP_LDRB:   update_pc_LDRB_IMM_PRE_INDEX_32(insn); break;
        case OP_CBNZ:   update_pc_CBNZ_32(insn); break;
        case OP_RET:    update_pc_RET(insn); break;
        case OP_CMP_SHIFT:
        case OP_SUBS_SHIFT: update_pc_SUBS_32_SHIFT(insn); break;
        case OP_BCOND: update_pc_BCOND(insn); break;
        case OP_NOP: update_pc_NOP(insn); break;
        case OP_B: update_pc_B(insn); break;
        case OP_CMP_IMM:
        case OP_SUBS_IMM: update_pc_SUBS_32_IMM(insn); break;
        case OP_BL: update_pc_BL(insn); break;
        case OP_BLR: update_pc_BLR(insn); break;
        case OP_BR: update_pc_BR(insn); break;
        case OP_SUB_IMM: update_pc_SUB_32_IMM(insn); break;
        case OP_MOVN: update_pc_MOVN_32(insn); break;
        case OP_CSEL: update_pc_CSEL_32(insn); break;
        case OP_SUB_SHIFT: update_pc_SUB_32_SHIFT(insn); break;
        case OP_MOV_SHIFT:
        case OP_ORR_SHIFT: update_pc_ORR_SHIFT(insn); break;
        case OP_AND: update_pc_AND_32_IMM(insn); break;
        case OP_LDRP: update_pc_LDR_IMM_POST_32(insn); break;
        case OP_STR: update_pc_STR_IMM_UOFF_32(insn); break;
        case OP_CBZ: update_pc_CBZ_32(insn); break;
        case OP_LDR3: update_pc_LDR_IMM_UOFF_32(insn); break;
        case OP_NONE:
        case OP_ERROR:  assert(false); break;
    }
}

//#ifdef DEBUG
static char *opcode_names[] = {
    "OP_NONE",
    "OP_ADD",
    "OP_ADRP",
    "OP_MOV",
    "OP_MOVZ",
    "OP_LDR",
    "OP_STRB",
    "OP_LDRB",
    "OP_CBNZ",
    "OP_RET",
    "OP_CMP_SHIFT",
    "OP_SUBS_SHIFT",
    "OP_BCOND",
    "OP_NOP",
    "OP_B",
    "OP_CMP_IMM",
    "OP_SUBS_IMM",
    "OP_BL",
    "OP_BLR",
    "OP_BR",
    "OP_SUB_IMM",
    "OP_CSEL",
    "OP_MOVN",
    "OP_SUB_SHIFT",
    "OP_ORR_SHIFT",
    "OP_MOV_SHIFT",
    "OP_AND",
    "OP_LDRP",
    "OP_STR",
    "OP_CBZ",
    "OP_LDR3",
    "OP_ERROR" 
};

static char *cond_names[] = {
    "EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", 
    "HI", "LS", "GE", "LT", "GT", "LE", "AL", "NV"
};
//#endif

void show_instr(const instr_t * insn, const proc_stage_t stage) {
//#ifdef DEBUG
    switch (stage) {
        case S_FETCH:
            printf("F:[%08lX  %08X]\n", guest.proc->PC.bits->xval, insn->insnbits);
            break;
        case S_DECODE:
            printf("D:\t\t\t[%s\t%s\t%s\t%s\t%s\t%016lX\t%d\t%c\t%c]\n", 
                opcode_names[insn->op], 
                insn->cond ? cond_names[insn->cond] : "--",
                insn->dst ? insn->dst->name : "---",
                insn->src1 ? insn->src1->name : "---",
                insn->src2 ? insn->src2->name : "---",
                insn->imm, 
                insn->shift,
                insn->wback ? 'Y' : 'N',
                insn->postindex ? 'Y' : 'N');
            break;

        case S_EXECUTE: break;
        case S_MEMORY: break;
        case S_WBACK: break;
        case S_UPDATE_PC: break;
        default: assert(false); break;
    }
//#endif
    return;
}