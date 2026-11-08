/*
 * Lab 1: Blink an LED
 * COMPE 375, Fall 2025
 * Created: 9/4/2025
 * Author : Lia Surguladze
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include "avr/iom328pb.h"
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << DDB5);              /* PB5 (built-in LED) as output */

    while (1)
    {
        PORTB |= (1 << PORTB5);       /* LED on  */
        _delay_ms(100);
        PORTB &= ~(1 << PORTB5);      /* LED off */
        _delay_ms(100);
    }
}
