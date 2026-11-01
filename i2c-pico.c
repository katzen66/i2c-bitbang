#include "i2c-bitbang.h"
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <pico/time.h>
#include <stdint.h>
#include <sys/types.h>
uint8_t sda_pin, scl_pin, I2C_del;
void pin_release(uint8_t pin)
{
  gpio_set_dir(pin, GPIO_IN);
  gpio_pull_up(pin);
}
void scl_wait_released(void)
{
  while (!gpio_get(scl_pin)) sleep_us(I2C_del);
}
void pin_low(uint8_t pin)
{
  gpio_put(pin, 0);
  gpio_set_dir(pin, GPIO_OUT);
}
void i2c_init(uint8_t pin_sda, uint8_t pin_scl, uint8_t delay_I2C)
{
  sda_pin = pin_sda, scl_pin=pin_scl, I2C_del = delay_I2C;
  gpio_init(sda_pin); gpio_init(scl_pin);
  pin_release(sda_pin);
  pin_release(scl_pin);
}
void i2c_start(void)
{
  pin_release(sda_pin); sleep_us(I2C_del);
  pin_release(scl_pin); sleep_us(I2C_del);
  scl_wait_released();

  pin_low(sda_pin);
  sleep_us(I2C_del);
  pin_low(scl_pin);
  sleep_us(I2C_del);
}
void i2c_stop(void)
{
  pin_low(sda_pin); sleep_us(I2C_del);

  pin_release(scl_pin); sleep_us(I2C_del);
  scl_wait_released();
  pin_release(sda_pin); sleep_us(I2C_del);
}
static inline void write_bit(bool value)
{
  if(value) pin_release(sda_pin);
  else pin_low(sda_pin);
  sleep_us(I2C_del);

  pin_release(scl_pin); scl_wait_released();
  
  sleep_us(2*I2C_del);

  pin_low(scl_pin);
  sleep_us(I2C_del);
}
bool read_bit(void)
{
  pin_release(sda_pin); sleep_us(I2C_del);
  pin_release(scl_pin); scl_wait_released();
  sleep_us(I2C_del);
  bool val = gpio_get(sda_pin); sleep_us(I2C_del);
  pin_low(scl_pin); sleep_us(I2C_del);
  return val;
}
bool i2c_write_byte(uint8_t byte)
{
  for(uint8_t i = 0 ; i < 8; ++i)
  {
    write_bit(byte & 0x80);
    byte = byte << 1;
  }
  return !read_bit();
}
