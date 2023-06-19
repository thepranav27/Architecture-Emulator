#ifndef _ORR_SHIFT_H_
#define _ORR_SHIFT_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ORR_SHIFT(instr_t * const);
extern void execute_ORR_SHIFT(instr_t * const);
extern void memory_ORR_SHIFT(instr_t * const);
extern void wback_ORR_SHIFT(instr_t * const);
extern void update_pc_ORR_SHIFT(instr_t * const);
#endif