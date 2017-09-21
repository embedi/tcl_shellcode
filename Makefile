#
# Makefile
#
PROG    = shellcode

# you can use command "export CROSS_COMPILE=powerpc-eabi-" instead of
CROSS_COMPILE = powerpc-eabi-

#
AS      = $(CROSS_COMPILE)as
LD      = $(CROSS_COMPILE)ld
CC      = $(CROSS_COMPILE)gcc
CPP     = $(CROSS_COMPILE)g++
AR      = $(CROSS_COMPILE)ar
NM      = $(CROSS_COMPILE)nm
STRIP   = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
STRIP   = $(CROSS_COMPILE)strip

LDSTATIC  = -static
ELF2ECOFF = ${OBJCOPY} -O ecoff-bigmips
ELF2BIN   = ${OBJCOPY} -O binary

TEXTADDR  = 0

# strip debug
LINKFLAGS = -Map ${PROG}.map \
            --omagic \
            --discard-all \
            --strip-all \
            ${LDBUG} \
            -Ttext ${TEXTADDR} \
            --entry=_start \
            ${GP} \
            -T raw.ld \
			-nostdlib -nodefaultlibs


# HAS_STDARG, DUSE_PROTOTYPE, USE_TCL_STUBS are Tcl's macro 
DEFS	= -D__ASSEMBLY__ -DHAS_STDARG -DUSE_PROTOTYPE -DUSE_TCL_STUBS -DTCL_CISCO

SUBDIRS =

OBJS	= crt0.o ${PROG}.o

INCLUDES = -I include/ -I include/libc
LIBS    =  lib/libc.a

CFLAGS  = -Os -mcpu=powerpc -Wa,-mregnames \
          -mrelocatable \
          -fpic \
          -std=c99 \
          -fno-keep-inline-functions \
          -fomit-frame-pointer \
          -nostdinc \
          -ffreestanding \
          -Wall \
          $(INCLUDES)

CPPFLAGS  = -O3 -mcpu=powerpc -Wa,-mregnames\
          -fpic \
          -fno-keep-inline-functions \
          -nostdinc \
          -Wall \
          $(INCLUDES)

ASFLAGS = -x c -traditional-cpp -mregnames

COMPILE = $(CC) $(DEFS) $(INCLUDES) $(CFLAGS) $(ASFLAGS)
CPPCOMPILE = $(CPP) $(INCLUDES) $(CPPFLAGS)

%.o: %.c
	$(COMPILE) -c $<

%.o: %.cpp
	$(CPPCOMPILE) -c $<

%.o: %.S
	$(AS) -mregnames -mrelocatable $< -o $@

${PROG}: crt0.o ${PROG}.o
	${LD} ${LINKFLAGS} -o ${PROG}.elf ${OBJS} $(LIBS)
	${ELF2BIN} ${PROG}.elf ${PROG}.bin

sub:	
	@list='$(SUBDIRS)'; \
	for subdir in $$list; do \
	echo "Making all in $$subdir"; \
	(cd $$subdir && $(MAKE)) \
	done;

clean:
	rm -f *.o *.core ${PROG}.map ${PROG}.elf ${PROG}.bin

