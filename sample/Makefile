GCC = aarch64-linux-gnu-gcc
OPTFLAG = -O2

OBJDUMP = aarch64-linux-gnu-objdump
OD = od
RM = /bin/rm -f
CHMOD = chmod go+rx

all:
	docker build -t arm .
	docker run -v `pwd`:/work -t arm

binaries: gcd hello helloint qsort test_switch vecsum 

helloint: Makefile helloint.c
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
	${CHMOD} $@ $@.${OD} $@-noopt $@-noopt.${OD}

hello: Makefile hello.c
	@echo "+-------+"
	@echo "| hello |"
	@echo "+-------+"
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
	${CHMOD} $@ $@.${OD} $@-noopt $@-noopt.${OD}

vecsum: Makefile vecsum.c
	@echo "+--------+"
	@echo "| vecsum |"
	@echo "+--------+"
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
	${CHMOD} $@ $@.${OD} $@-noopt $@-noopt.${OD}

gcd: Makefile gcd.c
	@echo "+-----+"
	@echo "| gcd |"
	@echo "+-----+"
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
	${CHMOD} $@ $@.${OD} $@-noopt $@-noopt.${OD}

test_switch: Makefile test_switch.c
	@echo "+-------------+"
	@echo "| test_switch |"
	@echo "+-------------+"
	$(GCC) $(OPTFLAG) --param case-values-threshold=1 -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	$(GCC) -O0 --param case-values-threshold=1 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
	${CHMOD} $@ $@.${OD} $@-noopt $@-noopt.${OD}

qsort: Makefile qsort.c
	@echo "+-------+"
	@echo "| qsort |"
	@echo "+-------+"
	$(GCC) $(OPTFLAG) -e start -nostdlib -nostdinc -static -o $@ $@.c
	$(OBJDUMP) -D $@ > $@.${OD}
	$(GCC) -O0 -e start -nostdlib -nostdinc -static -o $@-noopt $@.c
	$(OBJDUMP) -D $@-noopt > $@-noopt.${OD}
	${CHMOD} $@ $@.${OD} $@-noopt $@-noopt.${OD}

clean:
	${RM} *.o *.so *.bak
	${RM} gcd hello qsort test_switch vecsum 
	${RM} gcd-noopt hello-noopt qsort-noopt test_switch-noopt vecsum-noopt 