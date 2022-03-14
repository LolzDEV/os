#pragma once

#include "types.h"
#include <stddef.h>

// Heap data
#define K_PAGE_SIZE 4096
const extern u64 HEAP_START;
const extern u64 HEAP_SIZE;
#define TOTAL_PAGES 0x7F7E

// Page flags
#define K_FREE 1 << 0
#define K_TAKEN 1 << 1
#define K_LAST 1 << 2

#define K_PTE_SIZE    8
#define K_PTE_ENTRIES K_PAGE_SIZE / K_PTE_SIZE
#define K_PTE_VALID   1
#define K_PTE_READ    (1 << 1)
#define K_PTE_WRITE   (1 << 2)
#define K_PTE_EXEC    (1 << 3)
#define K_PTE_USER    (1 << 4)

// Helper functions
#define PTE_IS_VALID(x) (x & 0x1)
#define PPN(x)          (((x >> 28) & 0x3ffffff) | ((x >> 19) & 0x1ff) | ((x >> 10) & 0x1ff)) >> 12
#define VPN0(x)         (x >> 12) & 0x1ff
#define VPN1(x)         (x >> 21) & 0x1ff
#define VPN2(x)         (x >> 30) & 0x1ff

void k_init();
void *k_alloc(size_t size);
void *k_zalloc(size_t size);
int k_free(void* mem);
u64 k_map_mem(u64 *page_table, u64 virt, u64 phys, int write, int exec, int user);
