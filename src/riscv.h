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

static inline void
w_satp(u64 value) {
  __asm__ volatile ("csrrw x0, satp, %0" : "=r"(value));
}

// Flush the TLB.
static inline void
sfence_vma()
{
  // the zero, zero means flush all TLB entries.
  __asm__ volatile("sfence.vma zero, zero");
}

// Machine Status Register, mstatus

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)    // machine-mode interrupt enable.

/* Read mstatus csr */
static inline u64
r_mstatus()
{
  u64 x;
  __asm__ volatile("csrr %0, mstatus" : "=r" (x) );
  return x;
}

/* Write to mstatus csr */
static inline void
w_mstatus(u64 x)
{
  __asm__ volatile("csrw mstatus, %0" : : "r" (x));
}
