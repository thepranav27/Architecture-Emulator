#ifndef _STRB_IMM_UOFF_32_H_
#define _STRB_IMM_UOFF_32_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_STRB_IMM_UOFF_32(instr_t * const);
extern void execute_STRB_IMM_UOFF_32(instr_t * const);
extern void memory_STRB_IMM_UOFF_32(instr_t * const);
extern void wback_STRB_IMM_UOFF_32(instr_t * const);
extern void update_pc_STRB_IMM_UOFF_32(instr_t * const);
#endif