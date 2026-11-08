/*
 * Lab 2: Morse code blinker
 * COMPE 375, Fall 2025
 * Created: 9/18/2025
 * Author : Lia Surguladze
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>
#include <stddef.h>   /* for NULL */

/* LED setup */
#define LED_PORT PORTB       /* LED is on PORTB */
#define LED_DDR  DDRB        /* Data Direction Register for PORTB */
#define LED_PIN  PB5         /* Built-in LED */

/* Morse code timing: everything is a multiple of one time unit */
#define TIME_UNIT_MS   200                  /* 1 unit = 200 ms */
#define DOT_TIME       (1 * TIME_UNIT_MS)   /* dot = 1 unit */
#define DASH_TIME      (3 * TIME_UNIT_MS)   /* dash = 3 units */
#define INTRA_CHAR_GAP (1 * TIME_UNIT_MS)   /* gap between dots/dashes in a letter */
#define INTER_CHAR_GAP (3 * TIME_UNIT_MS)   /* gap between letters */
#define INTER_WORD_GAP (7 * TIME_UNIT_MS)   /* gap between words */

void led_on(void)  { LED_PORT |=  (1 << LED_PIN); }
void led_off(void) { LED_PORT &= ~(1 << LED_PIN); }

/* Dot: LED on for 1 unit, then off for 1 unit */
void dot(void)
{
    led_on();
    _delay_ms(DOT_TIME);
    led_off();
    _delay_ms(INTRA_CHAR_GAP);
}

/* Dash: LED on for 3 units, then off for 1 unit */
void dash(void)
{
    led_on();
    _delay_ms(DASH_TIME);
    led_off();
    _delay_ms(INTRA_CHAR_GAP);
}

/* Translate a string to Morse code and blink it */
void transmitMorse(const char *str)
{
    /* Lookup table: A-Z, then 0-9 */
    const char *morse_table[36] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",   /* A-I */
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", /* J-R */
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",        /* S-Z */
        "-----", ".----", "..---", "...--", "....-", ".....",            /* 0-5 */
        "-....", "--...", "---..", "----."                               /* 6-9 */
    };

    for (int i = 0; str[i] != '\0'; i++) {
        char c = toupper(str[i]);

        /* Space between words: the last symbol already waited 1 unit */
        if (c == ' ') {
            _delay_ms(INTER_WORD_GAP - INTRA_CHAR_GAP);
            continue;
        }

        const char *code = NULL;
        if (c >= 'A' && c <= 'Z') {
            code = morse_table[c - 'A'];
        } else if (c >= '0' && c <= '9') {
            code = morse_table[c - '0' + 26];
        } else {
            continue;   /* skip unsupported characters */
        }

        for (int j = 0; code[j] != '\0'; j++) {
            if (code[j] == '.') {
                dot();
            } else {
                dash();
            }
        }

        /* Gap between letters (minus the 1 unit already waited) */
        _delay_ms(INTER_CHAR_GAP - INTRA_CHAR_GAP);
    }
}

int main(void)
{
    LED_DDR |= (1 << LED_PIN);   /* LED pin as output */

    const char message[] = "LIA SURGULADZE";

    while (1) {
        transmitMorse(message);
        _delay_ms(3 * INTER_WORD_GAP);   /* long pause before repeating */
    }
    return 0;
}
