/*
Pour enregistrer les valeurs données par minicom :
minicom -D /dev/ttyACM0 -C frequence.dat
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "VirtualSerial.h"
#include <util/delay.h>

#define Kp 29
#define Ki 25

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

	init_PWM();
	init_ICP();

	// Active le chien de garde
	wdt_enable(WDTO_15MS);

	char timer_delais_consigne = 0;
	char flag_consigne_prise = 0;
	unsigned short consigne = 0;
	long erreur_actuelle = 0;
	long erreur_precedente = 0;
	short commande = 0;

	// Pour déclencher le watchdog de force
	//char timer_watchdog = 0;

	while (1) {
		// Send the ICP measure
		if (flag_ICP == 1) {
			// Récupérer la valeur de la consigne lors de la première mesure
			if (flag_consigne_prise == 0) {
				if (timer_delais_consigne < 10) {
					timer_delais_consigne++;
				}
				else {
					flag_consigne_prise = 1;
					consigne = nbr_clk_ICP;
					fprintf(&USBSerialStream, "Consigne : %d\n\r", consigne);
				}
			}
			else {
				erreur_actuelle = consigne - nbr_clk_ICP;

				// Calcul de la commande
				commande = (Kp * (erreur_actuelle - erreur_precedente) + Ki * erreur_actuelle + commande);

				// Limite la commande
				if (commande < -5000) {
					commande = -5000;
				}
				if (commande > 5000) {
					commande = 5000;
				}

				erreur_precedente = erreur_actuelle;

				// Application de la commande
				set_PWM_duty_cycle(512 + commande/100);

				// Envoie des données
				fprintf(&USBSerialStream, "%ld,%ld,%d\n\r", nbr_clk_ICP, erreur_actuelle, commande/100);

				/*
				// Pour déclencher le watchdog
				timer_watchdog++;
				if (timer_watchdog == 5) {
					_delay_ms(100);
				}
				*/
			}

			// Réinitialise le drapeau pour pouvoir réaliser une nouvelle mesure
			flag_ICP = 0;
		}
		// Réinitialise le chien de garde
		wdt_reset();

		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}
