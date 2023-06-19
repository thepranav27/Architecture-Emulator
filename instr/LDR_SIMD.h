#ifndef _LDR_SIMD_H_
#define _LDR_SIMD_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_LDR_SIMD(instr_t * const);
extern void execute_LDR_SIMD(instr_t * const);
extern void memory_LDR_SIMD(instr_t * const);
extern void wback_LDR_SIMD(instr_t * const);
extern void update_pc_LDR_SIMD(instr_t * const);
#endif