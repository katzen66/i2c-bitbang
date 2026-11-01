#include "i2c-bitbang.h"
#include "pico/stdlib.h"
uint8_t sda_pin, scl_pin, I2C_del;
void i2c_init(uint8_t pin_sda, uint8_t pin_scl, uint8_t delay_I2C)
{
  sda_pin = pin_sda, scl_pin=pin_scl, I2C_del = delay_I2C;
}
