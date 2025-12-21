#include "oled_ssd1306.h"
#include <string.h>
#include "font5x7.h"

static int i2c_tx(oled_t *o, const uint8_t *data, uint32_t len) {
  alt_avalon_i2c_master_target_set(o->i2c, o->addr);
  return alt_avalon_i2c_master_tx(o->i2c, (alt_u8*)data, (alt_u32)len, 0) == ALT_AVALON_I2C_SUCCESS;
}

static int oled_cmd(oled_t *o, uint8_t cmd) {
  uint8_t buf[2] = {0x00, cmd};
  return i2c_tx(o, buf, 2);
}

static int oled_data_bytes(oled_t *o, const uint8_t *p, uint32_t n) {
  uint8_t pkt[1 + 16];
  pkt[0] = 0x40;
  while (n) {
    uint32_t k = (n > 16) ? 16 : n;
    memcpy(&pkt[1], p, k);
    if (!i2c_tx(o, pkt, 1 + k)) return 0;
    p += k; n -= k;
  }
  return 1;
}

int oled_begin(oled_t *o, ALT_AVALON_I2C_DEV_t *i2c, uint8_t addr) {
  o->i2c = i2c;
  o->addr = addr;

  if (!oled_cmd(o, 0xAE)) return 0;

  //init clasico de SSD1306
  oled_cmd(o, 0xD5); oled_cmd(o, 0x80);
  oled_cmd(o, 0xA8); oled_cmd(o, 0x3F);
  oled_cmd(o, 0xD3); oled_cmd(o, 0x00);
  oled_cmd(o, 0x40);
  oled_cmd(o, 0x8D); oled_cmd(o, 0x14);
  oled_cmd(o, 0x20); oled_cmd(o, 0x00); //horizontal
  oled_cmd(o, 0xA1);
  oled_cmd(o, 0xC8);
  oled_cmd(o, 0xDA); oled_cmd(o, 0x12);
  oled_cmd(o, 0x81); oled_cmd(o, 0xCF);
  oled_cmd(o, 0xD9); oled_cmd(o, 0xF1);
  oled_cmd(o, 0xDB); oled_cmd(o, 0x40);
  oled_cmd(o, 0xA4);
  oled_cmd(o, 0xA6);
  oled_cmd(o, 0xAF);

  oled_clear(o);
  return 1;
}

int oled_begin_auto(oled_t *o, ALT_AVALON_I2C_DEV_t *i2c) {
  if (oled_begin(o, i2c, 0x3C)) return 1;
  if (oled_begin(o, i2c, 0x3D)) return 1;
  return 0;
}

void oled_set_cursor(oled_t *o, uint8_t page, uint8_t col) {
  oled_cmd(o, 0xB0 | (page & 0x07));
  oled_cmd(o, 0x00 | (col & 0x0F));
  oled_cmd(o, 0x10 | ((col >> 4) & 0x0F));
}

void oled_clear(oled_t *o) {
  //full window
  oled_cmd(o, 0x21); oled_cmd(o, 0); oled_cmd(o, 127);
  oled_cmd(o, 0x22); oled_cmd(o, 0); oled_cmd(o, 7);

  uint8_t z[16]; memset(z, 0, sizeof(z));
  for (int i = 0; i < (128 * 64 / 8) / 16; i++) {
    oled_data_bytes(o, z, 16);
  }
}

void oled_putc(oled_t *o, char c) {
  //map a tabla
  uint8_t uc = (uint8_t)c;
  if (uc < 32 || uc > 127) uc = (uint8_t)'?';
  const uint8_t *g = FONT5X7[uc - 32];

  oled_data_bytes(o, g, 5);
  uint8_t sp = 0x00;
  oled_data_bytes(o, &sp, 1);
}

void oled_print(oled_t *o, const char *s) {
  while (*s) oled_putc(o, *s++);
}

void oled_print_line(oled_t *o, uint8_t line, const char *s) {
  if (line > 7) line = 7;
  oled_set_cursor(o, line, 0);

  for (int i = 0; i < 21 && s[i]; i++) {
    oled_putc(o, s[i]);
  }
}
