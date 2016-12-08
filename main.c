#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "led_board.h"
#include "eeprom.h"
#include "usbdrv.h"

#define COLUMN_PER_CHAR 5
#define RQ_EEPROM_UPDATE 0
#define RQ_EEPROM_READ 1

usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
    usbRequest_t *rq = (void *)data;

    static uint8_t requested_eeprom_value;

    if(rq->bRequest == RQ_EEPROM_UPDATE)
    {
        uint8_t eeprom_address = rq->wIndex.bytes[0];
        uint8_t eeprom_value = rq->wValue.bytes[0];

        eeprom_update((uint8_t *) (uintptr_t)eeprom_address, eeprom_value);

        return 0;
    }
    
    else if(rq->bRequest == RQ_EEPROM_READ)
    {
        uint8_t eeprom_address = rq->wIndex.bytes[0];

        uint8_t requested_eeprom_value=  eeprom_read((uint8_t *) (uintptr_t)eeprom_address);
        set_led_column(requested_eeprom_value);
        usbMsgPtr = &requested_eeprom_value;
        return sizeof(requested_eeprom_value);
    }

    return 0;
}

int main(void)
{
    init_led_board();

    usbInit();

    usbDeviceDisconnect();
    _delay_ms(300);
    usbDeviceConnect();

    sei();

    uint8_t text_legnth = eeprom_read((uint8_t *)0);

    while(1)
    {
        usbPoll();

        uint8_t current_char;
        for(current_char = 0; current_char < text_legnth; current_char++)
        {
            uint8_t current_column;
            for(current_column = 1; current_column <= COLUMN_PER_CHAR; current_column++)
            {
                set_led_column(eeprom_read((uint8_t *) (uintptr_t)current_column + COLUMN_PER_CHAR * current_char));
                _delay_ms((int)(1.0 / 16 / 20 * 1000));
            }
        
            for(current_column = 1; current_column <= COLUMN_PER_CHAR; current_column++)
            {
                set_led_column(0);
                _delay_ms((int)(1.0 / 16 / 20 * 1000));
            }
        }
    }

    return 0;
}
