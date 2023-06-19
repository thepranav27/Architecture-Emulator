#ifndef _NOP_H_
#define _NOP_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_NOP(instr_t * const);
extern void execute_NOP(instr_t * const);
extern void memory_NOP(instr_t * const);
extern void wback_NOP(instr_t * const);
extern void update_pc_NOP(instr_t * const);
#endif