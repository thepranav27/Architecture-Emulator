#ifndef _ADD_IMM_64_H_
#define _ADD_IMM_64_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ADD_IMM_64(instr_t * const);
extern void execute_ADD_IMM_64(instr_t * const);
extern void memory_ADD_IMM_64(instr_t * const);
extern void wback_ADD_IMM_64(instr_t * const);
extern void update_pc_ADD_IMM_64(instr_t * const);
#endif