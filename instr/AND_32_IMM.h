#ifndef _AND_32_IMM_H_
#define _AND_32_IMM_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_AND_32_IMM(instr_t * const);
extern void execute_AND_32_IMM(instr_t * const);
extern void memory_AND_32_IMM(instr_t * const);
extern void wback_AND_32_IMM(instr_t * const);
extern void update_pc_AND_32_IMM(instr_t * const);
#endif