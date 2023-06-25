AS=nasm
ASMFLAGS+=-g -f elf32
CFLAGS ?= -O2 -g
CFLAGS += -std=gnu99
CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value
CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error
CC += -m32 -no-pie -fno-pie

.PHONY: all

all: integral

integral: integral.o hw6.o
	$(CC) $(CFLAGS) $^ -o $@

integral.o: integral.c
	$(CC) $(CFLAGS) $^ -c -o $@

hw6.o: hw6.asm
	$(AS) $(ASMFLAGS) $^ -o $@



clean:
	rm -rf *.o integral

test: integral
	./integral --test-root 1:2:1.0:2.0:0.0001:1.279353
	./integral --test-root 1:3:-3.0:-1.0:0.0001:-2.522223
	./integral --test-root 2:3:0.65049:1.0:0.0001:0.650519
	./integral --test-integral 1:-2.522223:1.279353:0.0001:7.05229
	./integral --test-integral 2:0.650519:1.279353:0.0001:0.718157
	./integral --test-integral 3:-2.522223:0.650519:0.0001:2.04732
