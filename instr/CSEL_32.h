#ifndef _CSEL_32_H_
#define _CSEL_32_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_CSEL_32(instr_t * const);
extern void execute_CSEL_32(instr_t * const);
extern void memory_CSEL_32(instr_t * const);
extern void wback_CSEL_32(instr_t * const);
extern void update_pc_CSEL_32(instr_t * const);
#endif