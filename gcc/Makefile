# Makefile template derived from:
# 	* [WinAVR](https://sourceforge.net/p/winavr/code/HEAD/tree/trunk/Mfile/data/makefile_template.winavr)
# 	* [hexagon5un's makefile](https://github.com/hexagon5un/AVR-Programming/blob/master/setupProject/Makefile)


# Target file name (without extension).
#TARGET = AtmelStart
## Or name it automatically after the enclosing directory
TARGET = $(lastword $(subst /, ,$(CURDIR)))

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the 
#     processor frequency. You can then use this symbol in your source code to 
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#     Typical values are:
#         F_CPU =  1000000
#         F_CPU = 16000000
#         F_CPU = 20000000
F_CPU = 3333333

# MCU name
MCU = atmega809

# Optimization level, can be [0, 1, 2, 3, s]. 
#     0 = turn off optimization. s = optimize for size.
#     (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Compiler flag to set the C Standard level.
#     c89   = "ANSI" C
#     gnu89 = c89 plus GCC extensions
#     c99   = ISO C99 standard (not yet fully implemented)
#     gnu99 = c99 plus GCC extensions
CSTANDARD = -std=gnu99

# List Assembler source files here.
#     Make them always end in a capital .S.  Files ending in a lowercase .s
#     will not be considered source files but generated files (assembler
#     output from the compiler), and will be deleted upon "make clean"!
#     Even though the DOS/Win* filesystem matches both .s and .S the same,
#     it will preserve the spelling of the filenames, and gcc itself does
#     care about how the name is spelled on its command-line.
ASRC = ../src/protected_io.S

# List C source files here. (C dependencies are automatically generated.)
SRC=$(wildcard ../src/*.c ../*.c ../examples/src/*.c)

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRAINCDIRS = \
../config \
../examples/include \
../include \
../utils \
 ../utils/assembler \
 ../

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = .

################################################################################
# You shouldn't be editing stuff below this line...
################################################################################

#---------------- Compiler Options C ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS =  -x c $(CDEFS) -DDEBUG -ffunction-sections -g3 -Wall -D__mega809__ $(patsubst %,-I$(QUOTE)%$(QUOTE),$(EXTRAINCDIRS))
CFLAGS += -B "$(MAKEFILE_DIR)../gcc/dev/atmega809"
CFLAGS += -O$(OPT)
CFLAGS += $(CSTANDARD)

#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -adhlns:   create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex 
#       dump that will be displayed for a given single line of source input.
ASFLAGS = $(ADEFS) -DDEBUG -ffunction-sections -g3 -Wall -D__mega809__ $(patsubst %,-I$(QUOTE)%$(QUOTE),$(EXTRAINCDIRS))
ASFLAGS += -B "$(MAKEFILE_DIR)../gcc/dev/atmega809"
ASFLAGS += -O$(OPT)
ASFLAGS += $(CSTANDARD)

# Define programs and commands.
#TOOLCHAIN_FOLDER = ~/.local/bin
TOOLCHAIN_FOLDER = ~/.platformio/packages/toolchain-atmelavr/bin

# There's no decent USB support in WSL, so we use the native Windows avrdude.exe from an existing Windows PlatformIO installation.
AVRDUDE = /mnt/c/Users/32470/.platformio/packages/tool-avrdude-megaavr/avrdude.exe
OBJCOPY = $(TOOLCHAIN_FOLDER)/avr-objcopy
OBJDUMP = $(TOOLCHAIN_FOLDER)/avr-objdump
SIZE = $(TOOLCHAIN_FOLDER)/avr-size
CC = $(TOOLCHAIN_FOLDER)/avr-gcc
REMOVE = rm -f
REMOVEDIR = rm -rf
MK_DIR = mkdir

 # Place -D or -U options here for C sources
CDEFS = -DF_CPU=$(F_CPU)UL

# Place -D or -U options here for ASM sources
ADEFS = -DF_CPU=$(F_CPU)

# Place -D or -U options here for C++ sources
CPPDEFS = -DF_CPU=$(F_CPU)UL
#CPPDEFS += -D__STDC_LIMIT_MACROS
#CPPDEFS += -D__STDC_CONSTANT_MACROS

# Compiler flags to generate dependency files.
# https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html
GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_CPPFLAGS = -mmcu=$(MCU) -I. -x c++ $(CPPFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS) $(GENDEPFLAGS)

#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
MATH_LIB = -lm
LDFLAGS = -Wl,--start-group -Wl,--end-group -Wl,-Map="$(TARGET).map" -Wl,--gc-sections -mmcu=$(MCU)
LDFLAGS += -B "$(MAKEFILE_DIR)../gcc/dev/atmega809"
#LDFLAGS += -L"../gcc/dev/atmega809/avrxmega3/short-calls"
#LDFLAGS += -l:libatmega809.a
LDFLAGS += $(MATH_LIB)

#---------------- Programming Options (avrdude) ----------------

# Programming hardware
# Type: avrdude -c ?
# to get a full listing.
#
AVRDUDE_PROGRAMMER = jtag2updi

# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT =  COM20
AVRDUDE_BAUDRATE = 115200
AVRDUDE_CONFIG_FILE="C:\Users\32470\.platformio\packages\tool-avrdude-megaavr\avrdude.conf"

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude> 
# to submit bug reports.
#AVRDUDE_VERBOSE = -v -v

AVRDUDE_FLAGS = -p $(MCU) -b $(AVRDUDE_BAUDRATE) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)
AVRDUDE_FLAGS += -C $(AVRDUDE_CONFIG_FILE)

# # List the object files
OBJS = $(SRC:%.c=$(OBJDIR)/%.o) $(CPPSRC:%.cpp=$(OBJDIR)/%.o) $(ASRC:%.S=$(OBJDIR)/%.o) 

MAKEFILE_DIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
QUOTE := "

# Default target
all: gccversion build sizeafter

# Change the build target to build a HEX file or a library.
build: elf hex eep lss

elf: $(TARGET).elf
hex: $(TARGET).hex
eep: $(TARGET).eep
lss: $(TARGET).lss

# Linker target
%.elf: $(OBJS)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker
	$(CC) --output $@ $(OBJS) $(LDFLAGS)
	@echo Finished building target: $@
	@echo

# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature  -R .user_signatures $< $@

%.eep: %.elf
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0

# Create extended listing file from ELF output file.
%.lss: %.elf
	$(OBJDUMP) -h -S -z $< > $@

# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) --mcu=$(MCU) --format=avr $(TARGET).elf

# Display compiler version information.
gccversion : 
	@$(CC) --version

sizeafter:
	@if test -f $(TARGET).elf; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); \
	2>/dev/null; echo; fi

# Program the device.  
upload: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)


# Compiler target(s)

# Compile: create object files from C source files.
$(OBJDIR)/%.o : %.c
	@echo Building file: $<
	@echo AVR/GNU C Compiler
	$(CC) -c $(ALL_CFLAGS) "$<" -o "$@"
	@echo Finished building: $<
	@echo

# Assemble: create object files from assembler source files.
$(OBJDIR)/%.o: %.S
	@echo Building file: $<
	@echo AVR/GNU Preprocessing Assembler
	$(CC) -c $(ALL_ASFLAGS) "$<" -o "$@" 
	@echo Finished building: $<
	@echo

# Create object files directory
$(shell mkdir $(OBJDIR) 2>/dev/null)

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

clean:
	$(REMOVE) $(OBJS)
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) $(ASRC:.S=.d)
	$(REMOVE) $(TARGET).a $(TARGET).hex $(TARGET).lss $(TARGET).eep $(TARGET).map $(TARGET).srec
	$(REMOVEDIR) .dep

# Listing of phony targets. (i.e. targets not associated with file names)
.PHONY : all begin finish end sizebefore sizeafter gccversion \
build elf hex eep lss sym coff extcoff \
clean clean_list program debug gdb-config