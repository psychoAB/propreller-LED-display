TARGET=main
MCU=atmega168
F_CPU=16000000
CFLAGS=-mmcu=$(MCU) -O -DF_CPU=$(F_CPU) -Ilib -Iusbdrv -I.
OBJS= led_board.o eeprom.o usbdrv/usbdrv.o usbdrv/usbdrvasm.o

.SECONDARY:

all: $(TARGET).hex

flash: $(TARGET).flash

clean:
	-rm -f *.o *.elf *.hex

%.flash: %.hex
	avrdude -p $(MCU) -c usbasp -u -U flash:w:$<

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

%.elf: %.o $(OBJS)
	avr-gcc $(CFLAGS) -o $@ $^

%.o: %.c
	avr-gcc $(CFLAGS) -c -o $@ $<
