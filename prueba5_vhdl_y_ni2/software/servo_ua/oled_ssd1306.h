#ifndef OLED_SSD1306_H
#define OLED_SSD1306_H

#include <stdint.h>
#include "altera_avalon_i2c.h"

typedef struct {
  ALT_AVALON_I2C_DEV_t *i2c;
  uint8_t addr;   // 0x3C o 0x3D
} oled_t;

int  oled_begin(oled_t *o, ALT_AVALON_I2C_DEV_t *i2c, uint8_t addr);
int  oled_begin_auto(oled_t *o, ALT_AVALON_I2C_DEV_t *i2c); // prueba 0x3C y 0x3D
void oled_clear(oled_t *o);
void oled_set_cursor(oled_t *o, uint8_t page, uint8_t col);
void oled_putc(oled_t *o, char c);
void oled_print(oled_t *o, const char *s);
void oled_print_line(oled_t *o, uint8_t line, const char *s); // line 0..7

#endif
