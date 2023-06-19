#include "archsim.h"

extern machine_t guest;

int runElf(const uint64_t entry) {
    logging(LOG_INFO, "Running ELF executable");
    guest.proc->PC.bits->xval = entry;
    guest.proc->SP.bits->xval = guest.mem->seg_start_addr[KERNEL_SEG]-8;
    guest.proc->NZCV.bits->sval = 0;
    guest.proc->GPR.bits[30].xval = RET_FROM_MAIN_ADDR;

#ifdef DEBUG
    printf("\n%s%s   Addr      Instr       Op  \tCond\tDest\tSrc1\tSrc2\tImmval   \t\tShift\tWback\tPostindex%s\n", 
           ANSI_BOLD, ANSI_COLOR_RED, ANSI_RESET);
#endif
    do {
        instr_t *insn = calloc(1, sizeof(instr_t));
        fetch_instr(insn); //show_instr(insn, S_FETCH);
        decode_instr(insn); //show_instr(insn, S_DECODE);
        execute_instr(insn); show_instr(insn, S_EXECUTE);
        memory_instr(insn); show_instr(insn, S_MEMORY);
        wback_instr(insn); show_instr(insn, S_WBACK);
        update_pc_instr(insn); show_instr(insn, S_UPDATE_PC);
        free(insn);
    } while (guest.proc->PC.bits->xval != RET_FROM_MAIN_ADDR);
    return EXIT_SUCCESS;
}