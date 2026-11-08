# Lab 2: Morse Code Blinker

Blinks any text in Morse code on the board's built-in LED, letters A–Z and numbers 0–9.

## How it works

- **Timing is built from one unit (200 ms):** dot = 1 unit, dash = 3 units, gap inside a letter = 1 unit, gap between letters = 3 units, gap between words = 7 units. These are the standard Morse code ratios.
- **Lookup table:** a 36-entry table stores the dot-dash pattern for A–Z and 0–9. A letter's position comes from `c - 'A'`, a digit's from `c - '0' + 26`.
- **Translating text:** `transmitMorse()` uppercases each character, finds its pattern, and calls `dot()` or `dash()` for each symbol. Spaces become word gaps, and unsupported characters are skipped.
- Each symbol already ends with a 1-unit pause, so the letter and word gaps subtract that unit to keep the timing exact.

## Build

Microchip Studio → new GCC C Executable project → device **ATmega328PB** → replace `main.c` → build and program the board over USB.

> The original lab blinked my name and student ID; the ID is removed here.
