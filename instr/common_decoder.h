#ifndef _COMMON_DECODER_H_
#define _COMMON_DECODER_H_
#include "../instr.h"

extern void decode_DPI(instr_t * const);
extern void decode_B_EG_SYS(instr_t * const);
extern void decode_LD_ST(instr_t * const);
extern void decode_DPR(instr_t * const);
#endif