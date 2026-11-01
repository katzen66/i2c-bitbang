#ifndef I2CBITBANG_H
#define I2CBITBANG_H
#include "pico/stdlib.h"
extern uint8_t sda_pin;
extern uint8_t scl_pin;
extern uint8_t I2C_del;
void i2c_init(uint8_t pin_sda, uint8_t pin_scl, uint8_t delay_I2C);
bool i2c_isidle(void);
void i2c_start(void);
void i2c_stop(void);
bool i2c_write_byte(void);
#endif/* I2CBITBANG_H */

