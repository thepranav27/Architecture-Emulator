#include <assert.h>
#include "RET.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.219 RET
void decode_RET(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0x1FU, 0) == 0x0);    
    assert(EXTRACT(insn->insnbits, 0x400U, 10) == 0x0);
    assert(EXTRACT(insn->insnbits, 0x800U, 11) == 0x0);
    assert(EXTRACT(insn->insnbits, 0xF000U, 12) == 0x0);
    assert(EXTRACT(insn->insnbits, 0x1F0000U, 16) == 0x1F);
    assert(EXTRACT(insn->insnbits, 0x600000U, 21) == 0x02);
    assert(EXTRACT(insn->insnbits, 0x800000U, 23) == 0x0);
    assert(EXTRACT(insn->insnbits, 0x1000000U, 24) == 0x0);
    assert(EXTRACT(insn->insnbits, 0xFE000000U, 25) == 0x6B);
 
    uint8_t n = EXTRACT(insn->insnbits, 0x3E0U, 5);
    insn->op = OP_RET;
    insn->src1 = guest.proc->GPR.names64 + n;

}

void execute_RET(instr_t * const insn) {

}

void memory_RET(instr_t * const insn) {
    return;
}

void wback_RET(instr_t * const insn) {
    return;
}

void update_pc_RET(instr_t * const insn) {
    guest.proc->PC.bits->xval = insn->src1->bits->xval;    
}