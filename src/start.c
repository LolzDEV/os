#include "types.h"
#include "uart.h"
#include "riscv.h"
#include "utils.h"

void main();

void start() {
    uart_puts("Starting kernel\n\rCurrent Hart ID: ");
    char buf[2];
    uart_puts(itoa(r_mhartid(), buf, 10));
    uart_puts("\n\r");

    u64 x = r_mstatus();
    x &= ~MSTATUS_MPP_MASK;
    x |= MSTATUS_MPP_S;
    w_mstatus(x);
    w_mepc((u64)main);
    w_satp(0);

    uart_puts("Entering Supervisor Mode\n\r");
    w_pmpaddr0(0x3fffffffffffffull);
    w_pmpcfg0(0xf);

    __asm__ volatile("mret");
}
