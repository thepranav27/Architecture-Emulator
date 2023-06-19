#ifndef _BCOND_H_
#define _BCOND_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_BCOND(instr_t * const);
extern void execute_BCOND(instr_t * const);
extern void memory_BCOND(instr_t * const);
extern void wback_BCOND(instr_t * const);
extern void update_pc_BCOND(instr_t * const);
#endif