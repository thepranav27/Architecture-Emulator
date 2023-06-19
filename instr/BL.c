#include <assert.h>
#include "BL.h"
#include "../machine.h"

extern machine_t guest;

void decode_BL(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0x7c000000U, 26) == 0x5U);
    assert(EXTRACT(insn->insnbits, 0x80000000U, 31) == 0x1U);

    uint64_t offset = (signed)(uint64_t)(GETBF(insn->insnbits, 0, 26));

    insn->imm = offset;
    insn->op = OP_BL;

}

void execute_BL(instr_t * const insn) {
    (guest.proc->GPR.names64+30)->bits->xval = guest.proc->PC.bits->xval + 4; //DOUBLE CHECK TO MAKE SURE THAT THIS IS PROPER WAY TO ACCESS
    insn->branch_PC = guest.proc->PC.bits->xval + insn->imm; 
}

void memory_BL(instr_t * const insn) {
    return;
}

void wback_BL(instr_t * const insn) {
    return;    
}

void update_pc_BL(instr_t * const insn) {
    guest.proc->PC.bits->xval = insn->branch_PC;
}