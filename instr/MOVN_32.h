#ifndef _MOVN_32_H_
#define _MOVN_32_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_MOVN_32(instr_t * const);
extern void execute_MOVN_32(instr_t * const);
extern void memory_MOVN_32(instr_t * const);
extern void wback_MOVN_32(instr_t * const);
extern void update_pc_MOVN_32(instr_t * const);
#endif