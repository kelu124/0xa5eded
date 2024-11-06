//!
//! \file       i2c.c
//! \author     Abdelrahman Ali
//! \date       2024-09-08
//!
//! \brief      i2c function.
//!

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------

#include "i2c.h"

//---------------------------------------------------------------------------
// GLOBAL VARIABLES
//---------------------------------------------------------------------------

uint16_t input;

//---------------------------------------------------------------------------
// I2C INIT FUNCTION
//---------------------------------------------------------------------------
void pio_i2c_init()
{
    i2c_init(I2C_PORT, I2C_FREQUENCY);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    gpio_init(GPIO20);
    gpio_set_dir(GPIO20, GPIO_OUT);
    gpio_put(GPIO20, 0);
}

//---------------------------------------------------------------------------
// I2C WRITE FUNCTION
//---------------------------------------------------------------------------
void pio_i2c_write(uint8_t data)
{
    if (data % 2 == 0)
    {
        gpio_put(GPIO20, 0);
    }
    else
    {
        gpio_put(GPIO20, 1);
    }
    uint8_t data_to_send[1];
    data_to_send[0] = (uint8_t)(data * 14);
    i2c_write_blocking(I2C_PORT, DEVICE_ADDRESS, data_to_send, 1, false);
}

//---------------------------------------------------------------------------
// I2C MAIN FUNCTION
//---------------------------------------------------------------------------
void i2c_trigger()
{
    while (1)
    {
        printf("Enter a number between 0 and 9: ");
        input = getchar();
        printf("%d\n", input - '0');
        if (input >= '0' && input <= '9')
        {
            input = input - '0';
            break;
        }
    }

    pio_i2c_write((uint8_t)input);
}

//---------------------------------------------------------------------------
// END OF FILE
//---------------------------------------------------------------------------
