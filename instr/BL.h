#ifndef _BL_H_
#define _BL_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_BL(instr_t * const);
extern void execute_BL(instr_t * const);
extern void memory_BL(instr_t * const);
extern void wback_BL(instr_t * const);
extern void update_pc_BL(instr_t * const);
#endif