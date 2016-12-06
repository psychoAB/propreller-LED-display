#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1 << PD3);
    
    uint8_t ledState = 0;

    while(1)
    {
        if(ledState)
        {
            PORTD |= (1 << PD3);
        }
        else
        {
            PORTD &= !(1 << PD3);
        }
        ledState = !ledState;
        _delay_ms(500);
    }

    return 0;
}
