#ifndef _SUB_32_SHIFT_H_
#define _SUB_32_SHIFT_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_SUB_32_SHIFT(instr_t * const);
extern void execute_SUB_32_SHIFT(instr_t * const);
extern void memory_SUB_32_SHIFT(instr_t * const);
extern void wback_SUB_32_SHIFT(instr_t * const);
extern void update_pc_SUB_32_SHIFT(instr_t * const);
#endif