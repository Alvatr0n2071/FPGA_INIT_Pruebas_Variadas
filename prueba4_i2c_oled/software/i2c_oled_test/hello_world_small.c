#include <stdint.h>
#include <string.h>
#include "system.h"
#include "io.h"
#include "altera_avalon_uart_regs.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_i2c.h"
#include "oled_ssd1306.h"

#define OLED_ADDR1 0x3C
#define OLED_ADDR2 0x3D
#define UART_BASE 0x90a0
#define LEDS_BASE 0x90d0
#define I2C_0_BASE 0x9040


static inline uint8_t uart_rx(void) {
  while ((IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_RRDY_MSK) == 0) {}
  return (uint8_t)IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
}
static inline void uart_tx(uint8_t b) {
  while ((IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_TRDY_MSK) == 0) {}
  IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, b);
}

int main(void) {
  ALT_AVALON_I2C_DEV_t *i2c = alt_avalon_i2c_open(I2C_0_NAME);

  oled_t oled;
  if (!i2c || !oled_begin_auto(&oled, i2c)) {
    IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 0xE);
    while (1) {}
  }

  oled_clear(&oled);
  oled_print_line(&oled, 0, "EJEMPLO UART+I2C");
  oled_print_line(&oled, 1, "MATLAB dice:");

  while (1) {
    uint8_t len = uart_rx();
    if (len == 0) {
      oled_clear(&oled);
      oled_print_line(&oled, 0, "Limpio");
      uart_tx(0xAA);
      continue;
    }

    // buffer seguro (máx 64 chars para no reventar RAM ni pantalla)
    uint8_t n = (len > 64) ? 64 : len;
    char msg[65];
    for (uint8_t i = 0; i < n; i++) msg[i] = (char)uart_rx();
    msg[n] = '\0';

    // consume bytes restantes si len>64
    for (uint8_t i = n; i < len; i++) (void)uart_rx();

    oled_clear(&oled);
    oled_print_line(&oled, 0, "MATLAB dice:");
    oled_print_line(&oled, 2, msg);

    // LEDs muestran len (4 bits)
    IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, len & 0x0F);

    uart_tx(0xAA); // ACK
  }
}
