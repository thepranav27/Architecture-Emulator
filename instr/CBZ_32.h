#ifndef _CBZ_32_H_
#define _CBZ_32_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_CBZ_32(instr_t * const);
extern void execute_CBZ_32(instr_t * const);
extern void memory_CBZ_32(instr_t * const);
extern void wback_CBZ_32(instr_t * const);
extern void update_pc_CBZ_32(instr_t * const);
#endif