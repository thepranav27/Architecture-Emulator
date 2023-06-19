#ifndef _CBNZ_32_H_
#define _CBNZ_32_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_CBNZ_32(instr_t * const);
extern void execute_CBNZ_32(instr_t * const);
extern void memory_CBNZ_32(instr_t * const);
extern void wback_CBNZ_32(instr_t * const);
extern void update_pc_CBNZ_32(instr_t * const);
#endif