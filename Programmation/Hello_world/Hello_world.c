#include <avr/io.h>

#include "VirtualSerial.h"
#include <util/delay.h>

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

int main(void) {
	// Initialisation USB
	SetupHardware();
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	GlobalInterruptEnable();

	// Déclaration
    DDRF |= (1 << PORTF1);

	while (1) {
		PORTF ^= (1 << PORTF1);

		// Prend du temps et fausse les durées
		//fprintf(&USBSerialStream,"Hello world\n\r");

		//   les 3 lignes ci-dessous pour accepter les signaux venant du PC 
		//CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
		//CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		//USB_USBTask();

		_delay_ms(500);
	}
}
