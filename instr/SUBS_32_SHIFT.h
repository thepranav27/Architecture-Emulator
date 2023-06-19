#ifndef _SUBS_32_SHIFT_H_
#define _SUBS_32_SHIFT_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_SUBS_32_SHIFT(instr_t * const);
extern void execute_SUBS_32_SHIFT(instr_t * const);
extern void memory_SUBS_32_SHIFT(instr_t * const);
extern void wback_SUBS_32_SHIFT(instr_t * const);
extern void update_pc_SUBS_32_SHIFT(instr_t * const);
#endif