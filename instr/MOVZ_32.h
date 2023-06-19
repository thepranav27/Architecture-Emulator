#ifndef _MOVZ_32_H_
#define _MOVZ_32_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_MOVZ_32(instr_t * const);
extern void execute_MOVZ_32(instr_t * const);
extern void memory_MOVZ_32(instr_t * const);
extern void wback_MOVZ_32(instr_t * const);
extern void update_pc_MOVZ_32(instr_t * const);
#endif