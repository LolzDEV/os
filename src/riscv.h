#pragma once


/* Write to pmpaddr0 */
#include "types.h"
static inline void
w_pmpaddr0(u64 x) {
  __asm__ volatile("csrw pmpaddr0, %0" : : "r" (x));
}

/* Write to pmpcfg0 */
static inline void
w_pmpcfg0(u64 x) {
  __asm__ volatile("csrw pmpcfg0, %0" : : "r" (x));
}

/* Get the ID of the current hart */
static inline int 
r_mhartid() {
    i32 id;
    __asm__ volatile ("csrr %0, mhartid"
        : "=r" (id));   
    return id;
}

/* Write to mepc */
static inline void
w_mepc(u64 addr) {
    __asm__ volatile ("csrw mepc, %0" : : "r" (addr));
}