#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
    // configurer PF1 comme sortie
    DDRF |= (1 << PF1);
    
    // allumer la LED en mettant PF1 à l'état haut
    PORTF |= (1 << PF1);
    
    // boucle infinie pour maintenir le programme en exécution
    while (1)
    {
        // on peut ajouter un petit délai si besoin
        _delay_ms(1000);
    }
    
    return 0;
}

