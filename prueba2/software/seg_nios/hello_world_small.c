#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"

//Direcciones en system.h
#define PIO_SEGMENTS_BASE    0x3020
#define PIO_DIGITS_BASE      0x3030

const unsigned char tabla_7seg[10] = {0x03, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1, 0x19};

void delay(int a) {
    volatile int contador = 0;
    while (contador < a * 5000) {
        contador++;
    }
}

int main() {
    printf("Hola mundo\n");

    unsigned char digito_1 = 1;
    unsigned char digito_2 = 2;
    unsigned char digito_3 = 3;
    unsigned char digito_4 = 4;

    while (1) {
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_DIGITS_BASE, 0x0F); // Apaga todos (1111)
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_SEGMENTS_BASE, tabla_7seg[digito_1]); // Prepara segmentos
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_DIGITS_BASE, 0x0E); // Enciende Dígito 1 (1110)
        delay(5);

        IOWR_ALTERA_AVALON_PIO_DATA(PIO_DIGITS_BASE, 0x0F); // Apaga todos
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_SEGMENTS_BASE, tabla_7seg[digito_2]); // Prepara segmentos
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_DIGITS_BASE, 0x0D); // Enciende Dígito 2 (1101)
        delay(5);

        IOWR_ALTERA_AVALON_PIO_DATA(PIO_DIGITS_BASE, 0x0F); // Apaga todos
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_SEGMENTS_BASE, tabla_7seg[digito_3]); // Prepara segmentos
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_DIGITS_BASE, 0x0B); // Enciende Dígito 3 (1011)
        delay(5);

        IOWR_ALTERA_AVALON_PIO_DATA(PIO_DIGITS_BASE, 0x0F); // Apaga todos
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_SEGMENTS_BASE, tabla_7seg[digito_4]); // Prepara segmentos
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_DIGITS_BASE, 0x07); // Enciende Dígito 4 (0111)
        delay(5);

    }
    return 0;
}
