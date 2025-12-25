#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "system.h"
#include "io.h"
#include "altera_avalon_uart_regs.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_i2c.h"
#include "oled_ssd1306.h"

// DEFINICIONES (Iguales que antes)
#define I2C_DEVICE_NAME "/dev/i2c_0"
#define SERVO_PIO_BASE  PIO_0_BASE
#define UART_BASE       UART_0_BASE

// Función para leer UART (bloqueante)
uint8_t uart_rx(void)
{
    while (!(IORD_ALTERA_AVALON_UART_STATUS(UART_BASE)
           & ALTERA_AVALON_UART_STATUS_RRDY_MSK));
    return IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
}

int main(void)
{
    // 1. INICIALIZACIÓN DE HARDWARE
    ALT_AVALON_I2C_DEV_t *i2c_dev = alt_avalon_i2c_open(I2C_DEVICE_NAME);
    if (!i2c_dev) while(1); // Error fatal

    oled_t disp;
    if (!oled_begin_auto(&disp, i2c_dev)) while(1); // Error fatal

    // 2. PANTALLA INICIAL (Fija)
    oled_clear(&disp);
    oled_print_line(&disp, 0, "   Servomotor   "); // Título centrado (línea 0)
    oled_print_line(&disp, 2, "Angulo: ---");      // Valor inicial (línea 2)

    uint8_t angle = 0;
    char text_buffer[20];

    // 3. BUCLE INFINITO
    while (1)
    {
        // A. Recibir dato de MATLAB
        angle = uart_rx();

        // B. Mover el Servo
        IOWR_ALTERA_AVALON_PIO_DATA(SERVO_PIO_BASE, angle);

        // C. Actualizar solo el número en la OLED
        // Los espacios al final son importantes para borrar si el número baja de 3 a 1 dígito
        snprintf(text_buffer, sizeof(text_buffer), "Angulo: %d   ", angle);
        oled_print_line(&disp, 2, text_buffer);
    }

    return 0;
}
