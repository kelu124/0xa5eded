//!
//! \file       main.c
//! \author     Abdelrahman Ali
//! \date       2024-09-08
//!
//! \brief      adc i2c main entry.
//!

//---------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------
#include "adc/adc.h"
#include "i2c/i2c.h"

//---------------------------------------------------------------------------
// MAIN FUNCTION
//---------------------------------------------------------------------------

int main()
{
    stdio_init_all();
    sleep_ms(100);
    pio_i2c_init();
    sleep_ms(100);
    pio_adc_init();
    sleep_ms(100);
    while (1)
    {
        i2c_trigger();
        sleep_ms(100);
        adc_trigger();
        sleep_ms(100);
    }
}
