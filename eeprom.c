#include <avr/eeprom.h>

uint8_t eeprom_read(const uint8_t * __p)
{
    while(SPMCSR & (1 << SPMEN))
    {
    }
    
    return eeprom_read_byte(__p);
}

void eeprom_update(uint8_t * __p, uint8_t __value)
{
    while(SPMCSR & (1 << SPMEN))
    {
    }

    eeprom_update_byte(__p, __value);
}
