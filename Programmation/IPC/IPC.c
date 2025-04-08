/*
Pour enregistrer les valeurs données par minicom :
minicom -D /dev/ttyACM0 -C frequence.dat
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "VirtualSerial.h"
#include <util/delay.h>

extern USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface;
extern FILE USBSerialStream;

// ICP
volatile short nbr_cycle_ICP_temp = 0;
volatile short nbr_cycle_ICP = 0;
volatile long nbr_clk_ICP = 0;
volatile char flag_ICP = 0;

// Lorsqu'un cycle complet est réalisé
ISR (TIMER1_OVF_vect) {
	nbr_cycle_ICP_temp++;
}

// Lorsque le front montant du 1PPS est détecté
ISR (TIMER1_CAPT_vect) {
	// Stocke le nombre de cycles réalisés
	nbr_cycle_ICP = nbr_cycle_ICP_temp;
	nbr_cycle_ICP_temp = 0;

	// Stocke la valeur du compteur actuelle
	nbr_clk_ICP = ICR1;

	// Active le drapeau pour le traiter dans la boucle principale
	flag_ICP = 1;
	
	// Réinitialise le compteur
	TCNT1 = 0;
}

void init_ICP () {
	// Déclaration du PORTD4 en entrée
	DDRD &= ~(1 << PORTD4);

	// Sélection de la détection sur front montant
	TCCR1B |= (1 << ICES1);	

	// Active les interruptions pour l'overflow et l'ICP
	TIMSK1 |= ((1 << ICIE1) | (1 << TOIE1));

	// Active le timer (prescaler = 1)
	TCCR1B |= (1 << CS10);
}

int main(void) {
	// Initialisation USB
	SetupHardware();
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	GlobalInterruptEnable();

	init_ICP();

	while (1) {
		if (flag_ICP == 1) {
			//fprintf(&USBSerialStream, "%d cycles complets + %ld coups d'horloges\n\r", nbr_cycle_ICP_display, nbr_clk_ICP_display);
			fprintf(&USBSerialStream, "%d,%ld\n\r", nbr_cycle_ICP, nbr_clk_ICP);

			// Réinitialise le drapeau pour pouvoir réaliser une nouvelle mesure
			flag_ICP = 0;
		}
		
		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}
