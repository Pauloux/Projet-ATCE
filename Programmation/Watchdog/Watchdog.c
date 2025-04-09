#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/wdt.h>     // Pour le watchdog
#include <util/delay.h> 
#include <avr/interrupt.h>
#include "VirtualSerial.h"

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

int main(void) {
	// Désactivation du JTAG pour utiliser toutes les LEDs
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);

	SetupHardware();
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	GlobalInterruptEnable();

	DDRF |= (1 << PORTF1) | (1 << PORTF4);
	PORTF |= (1 << PORTF1);    
	PORTF &= ~(1 << PORTF4);   

	_delay_ms(1000); 
	wdt_enable(WDTO_120MS);

	for (uint8_t i = 0; i < 100; i++) {
		PORTF ^= (1 << PORTF4);   
		wdt_reset();    
		_delay_ms(100);
	}

	while (1) {
		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}

    return 0;
}

