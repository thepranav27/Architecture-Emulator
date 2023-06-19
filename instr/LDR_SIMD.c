#include <assert.h>
#include "LDR_SIMD.h"
#include "../machine.h"

extern machine_t guest;

// Main: C6.2.44 CBNZ
void decode_LDR_SIMD(instr_t * const insn) {
    assert(EXTRACT(insn->insnbits, 0xC00000U, 22) == 0x3U);
    assert(EXTRACT(insn->insnbits, 0x3000000U, 24) == 0x1U);
    assert(EXTRACT(insn->insnbits, 0x4000000U, 26) == 0x1U);
    assert(EXTRACT(insn->insnbits, 0x38000000U, 27) == 0x7U);
    assert(EXTRACT(insn->insnbits, 0xC0000000U, 30) == 0x0U);

    

}

void execute_LDR_SIMD(instr_t * const insn) {
}

void memory_LDR_SIMD(instr_t * const insn) {
}

void wback_LDR_SIMD(instr_t * const insn) {
}

void update_pc_LDR_SIMD(instr_t * const insn) {
}