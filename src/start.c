#include "types.h"
#include "uart.h"
#include "riscv.h"
#include "utils.h"

void main();

void start() {
    uart_puts("Starting kernel\nCurrent Hart ID: ");
    char buf[2];
    uart_puts(itoa(r_mhartid(), buf, 10));
    uart_putc('\n');

    w_mepc((u64)main);

    uart_puts("Entering Supervisor Mode\n");
    w_pmpaddr0(0x3fffffffffffffull);
    w_pmpcfg0(0xf);

    __asm__ ("mret");
}