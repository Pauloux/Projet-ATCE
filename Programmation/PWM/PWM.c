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
	// 1024
	TC4H = 0x03;
	OCR4C = 0xFF;
	// Duty cycle
	// 512
	TC4H = 0x01;
	OCR4D = 0xFF;

	// Start timer (prescaler = 1)
	TCCR4B |= (1 << CS40);
}

void set_PWM_duty_cycle (short duty_cycle) {
	TC4H = (((duty_cycle) & 0x300) >> 8);
	OCR4D = (duty_cycle & 0xFF);
}

int main(void) {
	// Initialisation USB
	SetupHardware();
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	GlobalInterruptEnable();

	init_PWM();

	short i = 0;
	while (1) {
		set_PWM_duty_cycle(i);

		i = (i + 1) % 1024;
		if ((i == 0) | (i == 1023)) {
			_delay_ms(5000);
		}
		else {
			_delay_ms(10);
		}
	}
}
