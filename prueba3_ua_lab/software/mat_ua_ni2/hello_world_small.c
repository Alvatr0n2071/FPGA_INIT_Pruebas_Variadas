#include <stdint.h>
#include "system.h"
#include "io.h"
#include "altera_avalon_uart_regs.h"
#include "altera_avalon_pio_regs.h"

#define UART_BASE 0x5020
#define LED_PIO_BASE 0x5050


static inline uint8_t uart_getc_blocking(void)
{
    while ((IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) &
            ALTERA_AVALON_UART_STATUS_RRDY_MSK) == 0) { }
    return (uint8_t)IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
}

static inline void uart_putc(uint8_t c)
{
    while ((IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) &
            ALTERA_AVALON_UART_STATUS_TRDY_MSK) == 0) { }
    IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, c);
}

int main(void)
{
    IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, 0x0);

    while (1)
    {
        uint8_t a = uart_getc_blocking();
        uint8_t b = uart_getc_blocking();

        uint8_t sum = (uint8_t)(a + b);

        IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, sum & 0x0F);

        uart_putc(sum);
    }
}
