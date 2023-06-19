#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "../err_handler.h"
#include "../instr.h"
#include "../machine.h"
#include "ADD_IMM_64.h"
#include "ADRP.h"
#include "CBNZ_32.h"
#include "LDR_IMM_UOFF_64.h"
#include "LDRB_IMM_PRE_INDEX_32.h"
#include "MOVZ_32.h"
#include "RET.h"
#include "STRB_IMM_UOFF_32.h"
#include "MOVZ_64.h"
#include "SUBS_32_SHIFT.h"
#include "BCOND.h"
#include "NOP.h"
#include "B.h"
#include "SUBS_32_IMM.h"
#include "BL.h"
#include "BLR.h"
#include "BR.h"
#include "SUB_32_IMM.h"
#include "MOVN_32.h"
#include "CSEL_32.h"
#include "SUB_32_SHIFT.h"
#include "ORR_SHIFT.h"
#include "AND_32_IMM.h"
#include "LDR_IMM_POST_32.h"
#include "STR_IMM_UOFF_32.h"
#include "CBZ_32.h"
#include "LDR_IMM_UOFF_32.h"

/*
 * Decode: Level 3 (leaf).
 * 
 * Implemented in individual files in instr/ subdirectory.
 */

/*
 * Decode: Level 2.
 */

// PC-rel. addressing (DPI/0, DPI/1)
static void decode_PC_REL_ADDR(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0x10000000U, 24) == 0x10U);
    
    unsigned char op = EXTRACT(instr, 0x80000000U, 31);
    switch (op) {
        case 0: MISSING(); break;
        case 1: decode_ADRP(insn); break;
        default: assert(false); break;
    }
}

// Add/subtract (immediate) (DPI/2)
static void decode_ADD_SUB_IMM(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0x1F800000U, 23) == 0x22U);
    
    unsigned char sf_op_S = EXTRACT(instr, 0xE0000000U, 29);
    switch (sf_op_S) {
        case 0: MISSING(); break;
        case 1: MISSING(); break;
        case 2: decode_SUB_32_IMM(insn); break;
        case 3: decode_SUBS_32_IMM(insn); break;
        case 4: decode_ADD_IMM_64(insn); break;
        case 5: MISSING(); break;
        case 6: MISSING(); break;
        case 7: MISSING(); break;
        default: assert(false); break;
    }
}

// Move wide (immediate) (DPI/5)
static void decode_MOVE_WIDE_IMM(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0x1F800000U, 23) == 0x25U);
    
    unsigned char sf_opc = EXTRACT(instr, 0xE0000000, 29);
    unsigned char hw = EXTRACT(instr, 0x600000U, 21);
    switch (sf_opc) {
        case 0: decode_MOVN_32(insn); break;
        case 1: MISSING(); break;
        case 2: decode_MOVZ_32(insn); break;
        case 3: MISSING(); break;
        case 4: MISSING(); break;
        case 5: MISSING(); break;
        case 6: decode_MOVZ_64(insn); break;
        case 7: MISSING(); break;
        default: assert(false); break;
    }
}

// Load/store register (immediate pre-indexed) (C4.1.4; p. C4-299)
static void decode_LD_ST_REG_IMM_PRE_INDEXED(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    unsigned char size = GETBF(instr, 30, 2);
    unsigned char V = GETBF(instr, 26, 1);
    unsigned char opc = GETBF(instr, 22, 2);
    switch (size) {
        case 0:
            switch (V) {
                case 0:
                    switch (opc) {
                        case 0: MISSING(); break;
                        case 1: decode_LDRB_IMM_PRE_INDEX_32(insn); break;
                        case 2: MISSING(); break;
                        case 3: MISSING(); break;
                        default: assert(false); break;
                    }
                    break;
                case 1: MISSING(); break;
                default: assert(false); break;
            }
            break;
        case 1: MISSING(); break;
        case 2: MISSING(); break;
        case 3: MISSING(); break;
        default: assert(false); break;
    }
}

static void decode_LD_ST_REG_IMM_POST(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    unsigned char size = GETBF(instr, 30, 2);
    unsigned char V = GETBF(instr, 26, 1);
    unsigned char opc = GETBF(instr, 22, 2);
    /*
    switch(size) {
        case 2: 
            switch (V) {
                case 0:
                    switch (opc) {
                        case 1: decode_LDR_IMM_POST_32(insn); break;
                        default: assert(false); break;
                    }
                    break;
                default: assert(false); break;
            }
            break;
        default: assert(false); break;
    }
    */

    decode_LDR_IMM_POST_32(insn); //break;    

}

// Load/store register (unsigned immediate) (C4.1.4; p. C4-309)
static void decode_LD_ST_REG_U_IMM(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    unsigned char size = GETBF((uint32_t) instr, 30, 2);
    unsigned char V = GETBF(instr, 26, 1);
    unsigned char opc = GETBF(instr, 22, 2);
    switch (size) {
        case 0: 
            switch (V) {
                case 0:
                    switch (opc) {
                        case 0: decode_STRB_IMM_UOFF_32(insn); break;
                        default: MISSING(); break;
                    }
                    break;
                case 1: MISSING(); break;
                default: assert(false); break;
            }
            break;
        case 1: MISSING(); break;
        case 2: 
            switch(opc) {
                case 0: decode_STR_IMM_UOFF_32(insn); break;
                case 1: decode_LDR_IMM_UOFF_32(insn); break;
            }
            break;
        case 3: 
            switch (V) {
                case 0: 
                    switch (opc) {
                        case 0: MISSING(); break;
                        case 1: decode_LDR_IMM_UOFF_64(insn); break;
                        default: MISSING(); break;
                    }
                    break;
                case 1: MISSING(); break;
                default: assert(false); break;
            }
            break;
        default: assert(false); break;
    }
}

// Compare and branch (immediate) (p. C4-279)
static void decode_CMP_BRANCH_IMM(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(GETBF(instr, 25, 6) == 0x1AU);

    uint8_t sf = GETBF(instr, 31, 1);
    uint8_t op = GETBF(instr, 24, 1);

    switch (sf) {
        case 1:
            switch (op) {
                case 0: MISSING(); break;
                case 1: MISSING(); break;
                default: assert(false); break;
            }
            break;
        case 0:
            switch (op) {
                case 0: decode_CBZ_32(insn); break;
                case 1: decode_CBNZ_32(insn); break;
                default: assert(false); break;
            }
            break;
        default: assert(false); break;
    }
}

// Unconditional branch (register) (p. C4-275)
static void decode_UNCOND_BRANCH_REG(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(GETBF((uint32_t) instr, 25, 7) == 0x6BU);

    unsigned char opc = GETBF(instr, 21, 4);
    unsigned char op2 = GETBF(instr, 16, 5);
    assert(op2 == 0x1FU); // Shortcut
    unsigned char op3 = GETBF(instr, 10, 6);
    unsigned char op4 = GETBF(instr, 0, 5);

    switch (opc) {
        case 0: decode_BR(insn); break;
        case 1: decode_BLR(insn); break;
        case 2:
            switch (op3) {
                case 0:
                    assert(op4 == 0x0U);
                    decode_RET(insn);
                    break;
                default: MISSING(); break;
            }
            break;
        default: MISSING(); break;
    }
}

static void decode_ADD_SUB_SHIFT_REG(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0x1F000000U, 24) == 0xBU);

    unsigned char sf = EXTRACT(instr, 0x80000000U, 31);
    unsigned char op = EXTRACT(instr, 0x40000000U, 30);
    unsigned char S = EXTRACT(instr, 0x20000000U, 29);

    switch(sf) {
        case 0: 
        switch(op) {
            case 1: 
            switch(S) {
                case 0: decode_SUB_32_SHIFT(insn); break;
                case 1: decode_SUBS_32_SHIFT(insn); break;
            }
            break;
        }
        break;
        default: assert(false); break;
    }

}

static void decode_COND_B_IMM(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0xFE000000U, 25) == 0x2AU);

    unsigned char cond = EXTRACT(instr, 0xFU, 0);
    unsigned char o0 = EXTRACT(instr, 0x10U, 4);
    unsigned char o1 = EXTRACT(instr, 0x1000000, 24);
    uint32_t imm19 = EXTRACT(insn->insnbits, 0xFFFFE0, 5);

    switch(o1) {
        case 0:
        switch(o0) {
            case 0: decode_BCOND(insn);
        }
        break;
        default: assert(false); break;
    }

}

static void decode_HINTS(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0x1FU, 0) == 0x1FU);
    assert(EXTRACT(instr, 0xFFFFF000U, 12) == 0xD5032U);

    unsigned char op2 = EXTRACT(instr, 0xE0U, 5);
    unsigned char CRm = EXTRACT(instr, 0xF00U, 12);

    switch(CRm) {
        case 0: 
        switch(op2) {
            case 0: decode_NOP(insn); break;
        }
        break;
        default: assert(false); break;
    }

}

static void decode_UNC_BRANCH_IMM(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0x7C000000U, 26) == 0x5U);

    uint64_t imm26 = EXTRACT(instr, 0x3FFFFFFU, 0);
    unsigned char op = EXTRACT(instr, 0x80000000U, 31);

    switch(op) {
        case 0: decode_B(insn); break;
        case 1: decode_BL(insn); break;
        default: assert(false); break;
    }

}

static void decode_COND_SELECT(instr_t * const insn) {
    unsigned char sf = EXTRACT(insn->insnbits, 0x80000000U, 31);
    unsigned char op = EXTRACT(insn->insnbits, 0x40000000U, 30);
    unsigned char S = EXTRACT(insn->insnbits, 0x20000000U, 29);
    unsigned char op2 = EXTRACT(insn->insnbits, 0xC00U, 10);

    switch(sf) {
        case 0: decode_CSEL_32(insn); break;
        default: assert(false); break;
    }
}

static void decode_LOG_SHIFT_REG(instr_t * const insn) {
    unsigned char sf = EXTRACT(insn->insnbits, 0x80000000U, 31);
    unsigned char opc = EXTRACT(insn->insnbits, 0x60000000U, 29);
    
    switch(sf) {
        case 0: 
        switch (opc) {
            case 1: decode_ORR_SHIFT(insn); break;
        }
        break;
        default: assert(false); break;
    }
}

static void decode_LOG_IMM(instr_t * const insn) {
    uint32_t instr = insn->insnbits;
    unsigned char sf = GETBF(instr, 31, 1);
    unsigned char opc = GETBF(instr, 29, 2);
    unsigned char N = GETBF(instr, 22, 1);

    switch(sf) {
        case 0:
        switch (opc) {
            case 0:
            switch (N) {
                case 0: decode_AND_32_IMM(insn); break;
            }
            break;
        }
        break;
        default: assert(false); break;
    }
}

/*
 * Decode: Level 1.
 */

// C4.1.2 Data Processing -- Immediate
void decode_DPI(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0x1C000000U, 26) == 0x4U);
    
    unsigned char op0 = EXTRACT(instr, 0x03800000U, 23);
    switch (op0) {
        case 0: case 1: decode_PC_REL_ADDR(insn); break;
        case 2: decode_ADD_SUB_IMM(insn); break;
        case 3: MISSING(); break;
        case 4: decode_LOG_IMM(insn); break;
        case 5: decode_MOVE_WIDE_IMM(insn); break;
        case 6: MISSING(); break;
        case 7: MISSING(); break;
        default: assert(false); break;
    }
}

void decode_DPR(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0xE000000U, 25) == 0x5U);

    unsigned char op0 = EXTRACT(instr, 0x40000000U, 30);
    unsigned char op1 = EXTRACT(instr, 0x10000000U, 28);
    unsigned char op2 = EXTRACT(instr, 0x1E00000U, 21);
    unsigned char op3 = EXTRACT(instr, 0xFC00U, 10);

    switch(op1) {
        case 0: 
        switch(op2) {
            case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            decode_LOG_SHIFT_REG(insn); break;
            case 8: case 10: case 12: case 14: 
            decode_ADD_SUB_SHIFT_REG(insn); break;
        }
        break;
        case 1: decode_COND_SELECT(insn); break;
        default: assert(false); break;
    }

}

// C4.1.4 Loads and Stores
void decode_LD_ST(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    unsigned char op0 = EXTRACT(instr, 0xF0000000U, 28);
    unsigned char op1 = EXTRACT(instr, 0x8000000U, 27);
    unsigned char op2 = EXTRACT(instr, 0x1800000U, 23);
    unsigned char op3 = EXTRACT(instr, 0x3F0000U, 16);
    unsigned char op4 = EXTRACT(instr, 0xC00U, 10);

    switch (op0) {
        case 0: case 4: MISSING(); break;
        case 13: MISSING(); break;
        case 8: case 12: MISSING(); break;
        case 1: case 5: case 9: MISSING(); break;
        case 2: case 6: case 10: case 14: MISSING(); break;
        case 3: case 7: case 11: case 15: 
            switch (op2) {
                case 0: case 1: 
                    switch (op4) {
                        case 1: decode_LD_ST_REG_IMM_POST(insn); break;
                        case 3: decode_LD_ST_REG_IMM_PRE_INDEXED(insn); break;
                        default: assert(false); break;
                    }
                    break;
                case 2: case 3: decode_LD_ST_REG_U_IMM(insn); break;
                default: assert(false); break;
            }
            break;
        default: assert(false); break;
    }
}

// C4.1.3 Branches, Exception Generating, and System Instructions
void decode_B_EG_SYS(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(GETBF(instr, 26, 3) == 0x5U);

    unsigned char op0 = GETBF((uint32_t) instr, 29, 3);
    unsigned char op1 = GETBF(instr, 25, 1); // TODO: clean up.
    unsigned char op2 = GETBF(instr, 0, 5);

    switch (op0) {
        case 0: case 4: decode_UNC_BRANCH_IMM(insn); break;
        case 2: decode_COND_B_IMM(insn); break;
        case 1: case 5:
            switch (op1) {
                case 0: decode_CMP_BRANCH_IMM(insn); break;
                case 1: MISSING(); break;
                default: assert(false); break;
            }
            break;
        case 6: 
            switch (op1) {
                case 0: decode_HINTS(insn); break; 
                case 1: decode_UNCOND_BRANCH_REG(insn); break;
                default: assert(false); break;
            }
            break;
        default: assert(false); break;
    }
}
