#include <assert.h>
#include "BCOND.h"
#include "../machine.h"

extern machine_t guest;

void decode_BCOND(instr_t * const insn) {
    assert(GETBF(insn->insnbits, 24, 8) == 0x54U);
    assert(GETBF(insn->insnbits, 4, 1) == 0x0U);

    unsigned char cond = GETBF(insn->insnbits, 0, 4);
    uint64_t imm19 = GETBF(insn->insnbits, 5, 19) << 2;

    insn->op = OP_BCOND;
    if (imm19 >> 18 & 1) {
        insn->imm = imm19 | 0xFFFFFFFFFFF80000U;
    }
    else {
        insn->imm = imm19;
    }

    switch(cond) {
        case 0: insn->cond = C_EQ; break;
        case 1: insn->cond = C_NE; break;
        case 2: assert(false); break;
        case 3: assert(false); break;
        case 4: assert(false); break;
        case 5: assert(false); break;
        case 6: assert(false); break;
        case 7: assert(false); break;
        case 8: assert(false); break;
        case 9: assert(false); break;
        case 10: insn->cond = C_GE; break;
        case 11: insn->cond = C_LT; break;
        case 12: insn->cond = C_GT; break;
        case 13: insn->cond = C_LE; break;
        case 14: assert(false); break;
        case 15: assert(false); break;
        default: assert(false); break; 
    }

}

void execute_BCOND(instr_t * const insn) {
    bool j;
    switch(insn->cond) {
        case C_EQ: if((guest.proc->NZCV.bits->sval >> 2 & 1)) {
            j = true;
        } break;
        case C_NE: if((!(guest.proc->NZCV.bits->sval >> 2 & 1))) {
            j = true;
        } break;
        case C_GE: if(((guest.proc->NZCV.bits->sval >> 3 & 1) == (guest.proc->NZCV.bits->sval & 1))) {
            j = true;
        } break;
        case C_LT: if((!((guest.proc->NZCV.bits->sval >> 3 & 1) == (guest.proc->NZCV.bits->sval & 1)))) {
            j = true;
        } break;
        case C_GT: if((((guest.proc->NZCV.bits->sval >> 3 & 1) == (guest.proc->NZCV.bits->sval & 1)) && !(guest.proc->NZCV.bits->sval >> 2 & 1))) {
            j = true;
        } break;
        case C_LE: if((!(((guest.proc->NZCV.bits->sval >> 3 & 1) == (guest.proc->NZCV.bits->sval & 1)) && !(guest.proc->NZCV.bits->sval >> 2 & 1)))) {
            j = true;
        } break;
        default: j = false; break;
    }
    if (j == true) {
        insn->branch_PC = guest.proc->PC.bits->xval + insn->imm;
    }
    else {
        insn->branch_PC = guest.proc->PC.bits->xval + 4;
    }
}

void memory_BCOND(instr_t * const insn) {
    return;
}

void wback_BCOND(instr_t * const insn) {
    return;    
}

void update_pc_BCOND(instr_t * const insn) {
    guest.proc->PC.bits->xval = insn->branch_PC;
}