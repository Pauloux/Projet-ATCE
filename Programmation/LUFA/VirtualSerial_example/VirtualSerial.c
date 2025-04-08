#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "VirtualSerial.h"
#include <util/delay.h>

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

int main(void) {
	char ReportString[20] = "World";

	SetupHardware();
	/* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	GlobalInterruptEnable();

	int i = 0;
	for (;;)
	{
		i+=1;
		fprintf(&USBSerialStream,"\nHello ");
		fputs(ReportString, &USBSerialStream);
		fprintf(&USBSerialStream, " %d\n", i);
		fprintf(&USBSerialStream, "taille d'un char : %d\n", sizeof(char));
		fprintf(&USBSerialStream, "taille d'un int : %d\n", sizeof(int));
		fprintf(&USBSerialStream, "taille d'un long : %d\n", sizeof(long));

		//   les 3 lignes ci-dessous pour accepter les signaux venant du PC 
		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
		_delay_ms(500);
	}
}
