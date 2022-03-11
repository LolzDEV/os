#include "uart.h"

volatile unsigned char* UART = (unsigned char*)0x10000000;

void uart_putc(char c) {
    *UART = c;
}

void uart_puts(char *s) {
    while (*s != '\0') {
        uart_putc(*s);
        s++;
    }
}