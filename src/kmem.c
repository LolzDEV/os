#include "kmem.h"
#include "memset.h"
#include "riscv.h"
#include "types.h"
#include "uart.h"
#include "utils.h"

u8 pages[TOTAL_PAGES];
u64* kernel_page_table;

void k_init() {
    memset(pages, K_FREE, TOTAL_PAGES);

    kernel_page_table = (u64*) k_zalloc(1);

    k_map_mem(kernel_page_table, 0x10000000, 0x10000000, 1, 1, 0);
    k_map_mem(kernel_page_table, 0x40000000, 0x10000000, 1, 1, 0);

    uart_puts("Hello there1\n\r");
    w_satp((u64)(0x8L << 60 | ((u64) kernel_page_table) >> 12));

    uart_puts("hi");
}

void *k_alloc(size_t size) {
    for (int i=0; i < TOTAL_PAGES; i++) {
        u8 found = 0;

        if (pages[i] == K_FREE) {
            found = 1;

            for (int k=i; k < size; k++) {
                if (pages[k] != K_FREE) {
                    found = 0;
                    continue;
                }
            }
        }

        if (found) {
            for (int j=i; j < size; j++) {
                pages[j] = K_TAKEN;
            }

            pages[i + (size-1)] = K_LAST;

            return (void *) (u64) (HEAP_START + (i * K_PAGE_SIZE));
        }
    }

    return NULL;
}

int k_free(void *mem) {
    int freed = 0;

    int index = ((u64) mem-HEAP_START)/K_PAGE_SIZE;

    while (index < TOTAL_PAGES) {
        freed++;
        if (pages[index] == K_LAST) {
            pages[index] = K_FREE;
            break;
        }

        pages[index] = K_FREE;

        index++;
    }

    return freed;
}

void *k_zalloc(size_t size) {
    void *ptr = k_alloc(size);
    memset((u8*)ptr, 0, (u64)size*K_PAGE_SIZE);

    return ptr;
}

u64 k_map_mem(u64 *page_table, u64 virt, u64 phys, int write, int exec, int user) {
    u64 vpn[3], ppn[3];
    u64 *pte;
    u64 *alloced_page;

    vpn[2] = VPN2(virt);
    vpn[1] = VPN1(virt);
    vpn[0] = VPN0(virt);

    pte = page_table;

    if (!PTE_IS_VALID(pte[vpn[2]])) {
        alloced_page = k_zalloc(1);
        pte[vpn[2]] = (((u64) alloced_page) >> 2) | K_PTE_VALID;
    }

    pte = alloced_page;

    if (!PTE_IS_VALID(pte[vpn[1]])) {
        alloced_page = k_zalloc(1);
        pte[vpn[1]] = (((u64) alloced_page) >> 2) | K_PTE_VALID;
    }

    pte = alloced_page;

    if (!PTE_IS_VALID(pte[vpn[0]])) {
        pte[vpn[0]] = (phys >> 2) | K_PTE_READ | K_PTE_VALID;

        if (write) pte[vpn[0]] |= K_PTE_WRITE;
        if (exec)  pte[vpn[0]] |= K_PTE_EXEC;
        if (user)  pte[vpn[0]] |= K_PTE_USER;

        return pte[vpn[0]];
    }

    return 0;
}
