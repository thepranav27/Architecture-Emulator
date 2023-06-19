#ifndef _STR_IMM_UOFF_32_H_
#define _STR_IMM_UOFF_32_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_STR_IMM_UOFF_32(instr_t * const);
extern void execute_STR_IMM_UOFF_32(instr_t * const);
extern void memory_STR_IMM_UOFF_32(instr_t * const);
extern void wback_STR_IMM_UOFF_32(instr_t * const);
extern void update_pc_STR_IMM_UOFF_32(instr_t * const);
#endif