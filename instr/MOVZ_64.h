#ifndef _MOVZ_64_H_
#define _MOVZ_64_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_MOVZ_64(instr_t * const);
extern void execute_MOVZ_64(instr_t * const);
extern void memory_MOVZ_64(instr_t * const);
extern void wback_MOVZ_64(instr_t * const);
extern void update_pc_MOVZ_64(instr_t * const);
#endif