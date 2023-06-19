#ifndef _LDRB_IMM_PRE_INDEX_32_
#define _LDRB_IMM_PRE_INDEX_32_
#include <stdint.h>
#include "../instr.h"

extern void decode_LDRB_IMM_PRE_INDEX_32(instr_t * const);
extern void execute_LDRB_IMM_PRE_INDEX_32(instr_t * const);
extern void memory_LDRB_IMM_PRE_INDEX_32(instr_t * const);
extern void wback_LDRB_IMM_PRE_INDEX_32(instr_t * const);
extern void update_pc_LDRB_IMM_PRE_INDEX_32(instr_t * const);
#endif