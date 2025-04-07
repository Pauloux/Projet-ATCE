#include <avr/io.h>

#include "VirtualSerial.h"
#include <util/delay.h>

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

void init_PWM () {
	// Déclaration du PORTD7 en sortie
	DDRD |= (1 << PORTD7);

	// Clear on up-counting and set on down-counting 
	TCCR4C |= (1 << COM4D1) | (1 << PWM4D);

	// Phase and Frequency Correct PWM
	TCCR4D |= (1 << WGM40);

	// Frequency
	OCR4C = 255;
	// Duty cycle
	OCR4D = 64;

	// Start timer (prescaler = 1)
	TCCR4B |= (1 << CS40);
}

int main(void) {
	// Initialisation USB
	SetupHardware();
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	GlobalInterruptEnable();

	init_PWM();

	while (1) {

	}
}
