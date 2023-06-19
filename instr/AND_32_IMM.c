#include <assert.h>
#include <math.h>
#include "AND_32_IMM.h"
#include "../machine.h"

extern machine_t guest;

//C6.2.12 AND IMM PG 793

void decode_AND_32_IMM(instr_t * const insn){

    uint32_t instr = insn->insnbits;

    unsigned char d = GETBF(instr, 0, 5);
    unsigned char n = GETBF(instr, 5, 5);
    uint8_t imms = GETBF(instr, 10, 6);
    uint8_t immr = GETBF(instr, 16, 6);
    uint16_t imm12 = (imms << 6) | immr;

    insn->op = OP_AND;
    insn->dst = (d == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names32 + d);
    insn->src1 = guest.proc->GPR.names32 + n;

    uint8_t nimms = ~imms;
    int len = 0;
    while(nimms != 0){
        nimms = nimms >> 1;
        len++;
    }
   
    uint8_t levels = (1 << len) - 1;

    uint8_t S = imms & levels;
    uint8_t R = immr & levels; 
    uint8_t diff = S - R;

    uint8_t esize = 1 << len;
    
    uint32_t welem = (1 << (S+1)) - 1;
    
    if(R == 0)
        insn->imm = welem;
    else{
        uint8_t m = R % 32;
        insn->imm = (welem >> m) | (welem >> (32-m));
    }

    insn->opnd1.wval = insn->src1->bits->wval;
    insn->opnd2.wval = insn->imm;
    insn->next_PC = guest.proc->PC.bits->xval + 4;

    insn->val_ex.wval = insn->opnd1.wval & insn->opnd2.wval;
    insn->dst->bits->wval = insn->val_ex.wval;
    guest.proc->PC.bits->xval = insn->next_PC;

}

void execute_AND_32_IMM(instr_t * const insn){
}

void memory_AND_32_IMM(instr_t * const insn){
}

void wback_AND_32_IMM(instr_t * const insn){
}

void update_pc_AND_32_IMM(instr_t * const insn){
}