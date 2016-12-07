#include <avr/io.h>
#include "led_board.h"

void init_led_board()
{
    DDRD |= (1 << PD3);
    DDRC |= PORTC_LED;
    DDRB |= PORTB_LED;

    PORTD |= (1 << PD3);
    PORTC = PORTC_LED;
    PORTB = PORTB_LED;
}

void set_led_column(uint8_t value)
{
    PORTC = PORTC_LED & ~value;
    PORTB = ((PORTB_LED << 6) & ~value) >> 6;
}
