#ifndef _ADRP_H_
#define _ADRP_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ADRP(instr_t * const);
extern void execute_ADRP(instr_t * const);
extern void memory_ADRP(instr_t * const);
extern void wback_ADRP(instr_t * const);
extern void update_pc_ADRP(instr_t * const);
#endif