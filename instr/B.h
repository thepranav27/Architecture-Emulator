#ifndef _B_H_
#define _B_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_B(instr_t * const);
extern void execute_B(instr_t * const);
extern void memory_B(instr_t * const);
extern void wback_B(instr_t * const);
extern void update_pc_B(instr_t * const);
#endif