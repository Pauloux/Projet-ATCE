MCU	= atmega32u4
TARGET = Hello_world
EMPLACEMENT_LUFA=/home/pauloux/Documents/0CMI/0Semestre6/Électronique_Programmable/Microcontrôleur/TP/LUFA

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(TARGET).o
	avr-gcc -mmcu=$(MCU) -L$(EMPLACEMENT_LUFA)/VirtualSerial_lib $(TARGET).o -o $(TARGET).elf -lVirtualSerial

$(TARGET).o: $(TARGET).c
	avr-gcc -c -mmcu=$(MCU) -Wall -I$(EMPLACEMENT_LUFA)/lufa-LUFA-140928 -I$(EMPLACEMENT_LUFA)/VirtualSerial_example -DF_USB=16000000UL -DF_CPU=16000000UL -Os -std=gnu99  $(TARGET).c

clean:
	rm *.o *.elf

DFU=dfu-programmer

flash:
	@$(DFU) $(MCU) erase
	@$(DFU) $(MCU) flash $(TARGET).hex
	@$(DFU) $(MCU) reset
