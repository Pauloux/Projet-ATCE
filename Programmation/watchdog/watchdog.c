#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/wdt.h>     // Pour le watchdog
#include <util/delay.h>  // Pour _delay_ms()
#include <avr/interrupt.h>
#include "VirtualSerial.h"

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

int main(void)
{
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
    SetupHardware();
    CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
    GlobalInterruptEnable();
    DDRF |= (1 << PF1) | (1 << PF4) | (1 << PF5) | (1 << PF6) ;
    PORTF |= (1 << PF1);    
    PORTF &= ~(1 << PF4);   
    PORTF &= ~(1 << PF5);
    PORTF &= ~(1 << PF6);

    _delay_ms(1000); 
    wdt_enable(WDTO_120MS);  
    
    for (uint8_t i = 0; i < 100; i++)
            {
                PORTF ^= (1 << PF4);   
                _delay_ms(100);
                wdt_reset();    
            }
    while (1)
    {
        CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
	CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
	USB_USBTask();
    }

    return 0;
}

