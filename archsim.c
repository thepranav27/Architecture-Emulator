#include "archsim.h"

machine_t guest;
FILE *infile, *outfile, *errfile;
char *ae_prompt;

int main(int argc, char* argv[]) {
    // handle_args(argc, argv);
    init();
    
    uint64_t entry = loadElf(argv[1]);
    int ret = runElf(entry);
    
    finalize();
    
    return ret;
}
