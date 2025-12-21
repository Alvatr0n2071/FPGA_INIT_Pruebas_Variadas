#include <stdint.h>
#include <unistd.h>   // usleep
#include "system.h"
#include "altera_avalon_uart_regs.h"
#include "altera_avalon_pio_regs.h"
#include "io.h"

#define OLED_ADDR1 0x3C
#define OLED_ADDR2 0x3D
#define UART_BASE 0x90a0
#define LEDS_BASE 0x90d0
#define I2C_0_BASE 0x9040


static inline void uart_tx(uint8_t b)
{
    while ((IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) &
            ALTERA_AVALON_UART_STATUS_TRDY_MSK) == 0) {}
    IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, b);
}

int main(void)
{
    uint8_t x = 0;

    while (1) {
        uart_tx(0x55);  // SYNC
        uart_tx(x);     // sample

        IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, x & 0x0F); // debug visual
        x++;

        usleep(100000);  // 10 ms -> 100 samples/seg aprox
    }
}
