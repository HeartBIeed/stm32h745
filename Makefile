TARGET    = main
MCPU      = cortex-m7
STARTUP   = startup_stm32h745zitx
LOADER    = STM32H745ZITX_FLASH.ld
OBJCOPY   = arm-none-eabi-objcopy
CC        = arm-none-eabi-gcc

INC_DRV  = Drivers/CMSIS/Include
ST_INCL  = Core/Startup
INC_HDRS = inc

SRC       := $(wildcard *.c)
OBJ       := $(patsubst %.c,build/%.o,$(SRC))

SYS_SRC   = Core/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.c
SYS_OBJ   = build/system_stm32h7xx_dualcore_boot_cm4_cm7.o

CFLAGS = -mcpu=$(MCPU) -g3 --specs=nano.specs -mthumb -mfloat-abi=soft -Wall -std=gnu11 \
-I$(INC_HDRS) -I$(INC_DRV) \
-DSTM32H745xx -DCORE_CM7 

all: $(TARGET).hex

build/%.o: %.c | build
	$(CC) $(CFLAGS) -c -Os -ffunction-sections -fdata-sections -fstack-usage -o $@ $<

$(SYS_OBJ): $(SYS_SRC)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(STARTUP).o: $(ST_INCL)/$(STARTUP).s | build
	$(CC) $(CFLAGS) -c -x assembler-with-cpp -o $@ $<

build/$(TARGET).elf: $(OBJ) $(SYS_OBJ) $(STARTUP).o $(LOADER)
	$(CC) -o $@ $(OBJ) $(SYS_OBJ) $(STARTUP).o \
	-mcpu=$(MCPU) -T"$(LOADER)" \
	-Wl,-Map=build/$(TARGET).map \
	-Wl,--gc-sections \
	-Wl,--start-group -lc -lm \
	-Wl,--end-group \
	--specs=nosys.specs \
    --specs=nano.specs \
	-mfloat-abi=soft -mthumb 

	@/bin/echo -e "\033[1;33m Success...\n"

	arm-none-eabi-size $@

	@/bin/echo -e "\033[0m"

$(TARGET).hex: build/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@
