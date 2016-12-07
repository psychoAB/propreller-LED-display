#include <avr/io.h>
#include <util/delay.h>

#include "led_board.h"

int main(void)
{
    init_led_board();

    while(1)
    {
        set_led_column(159);
    }

    return 0;
}
