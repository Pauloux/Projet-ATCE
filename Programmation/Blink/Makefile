# nom de la cible (ici, le programme s'appelle "led")
TARGET = led

# microcontrôleur utilisé
MCU = atmega32u4

# fréquence CPU (16 MHz ici)
F_CPU = 16000000UL

# compilateur AVR et options de compilation (options simples pour un débutant)
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -Wall -std=c99

# outil pour générer le fichier HEX
OBJCOPY = avr-objcopy

# cible par défaut : générer le fichier hex
all: $(TARGET).hex

# compilation du fichier source en binaire exécutable
$(TARGET).out: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).c

# création du fichier hex à partir de l'exécutable
$(TARGET).hex: $(TARGET).out
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).out $(TARGET).hex

# nettoyage des fichiers générés
clean:
	rm -f $(TARGET).out $(TARGET).hex

# cible flash pour programmer la puce via dfu-programmer
flash: $(TARGET).hex
	dfu-programmer $(MCU) erase
	dfu-programmer $(MCU) flash $(TARGET).hex
	dfu-programmer $(MCU) reset

