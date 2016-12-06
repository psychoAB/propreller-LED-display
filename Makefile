TARGET=main
MCU=atmega168
F_CPU=16000000
CFLAGS=-mmcu=$(MCU) -O -DF_CPU=$(F_CPU)

.SECONDARY:

all: $(TARGET).hex

flash: $(TARGET).flash

clean:
	-rm -f *.o *.elf *.hex

%.flash: %.hex
	avrdude -p $(MCU) -c usbasp -u -U flash:w:$<

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

%.elf: %.o
	avr-gcc $(CFLAGS) -o $@ $<

%.o: %.c
	avr-gcc $(CFLAGS) -c -o $@ $<
