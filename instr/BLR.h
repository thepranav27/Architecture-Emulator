#ifndef _BLR_H_
#define _BLR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_BLR(instr_t * const);
extern void execute_BLR(instr_t * const);
extern void memory_BLR(instr_t * const);
extern void wback_BLR(instr_t * const);
extern void update_pc_BLR(instr_t * const);
#endif