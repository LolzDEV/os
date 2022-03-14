#include "kmem.h"
#include "uart.h"
#include "utils.h"

void main() {
    uart_puts("Supervisor Mode Activated\n\r");

    k_init();

    int* x = k_alloc(3);
    k_free(x);

    while(1);
}
