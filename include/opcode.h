#pragma once
#include "intel8080.h"

#define MAKE_FLAG(S, Z, A, P, C)    \
    (uint8_t)((uint8_t)(S << 7) | \
              (uint8_t)(Z << 6) | \
              (uint8_t)(1 << 5) | \
              (uint8_t)(A << 4) | \
              (uint8_t)(0 << 3) | \
              (uint8_t)(P << 2) | \
              (uint8_t)(1 << 1) | \
              (uint8_t)(C << 0) )

#define MAKE_FLAG_NONE  MAKE_FLAG(0,0,0,0,0)
#define MAKE_FLAG_SZAP  MAKE_FLAG(1,1,1,1,0)
#define MAKE_FLAG_CARRY MAKE_FLAG(0,0,0,0,1)
#define MAKE_FLAG_ALL   MAKE_FLAG(1,1,1,1,1)

typedef union {
    void (*f0)(intel8080*);
    void (*f1)(intel8080*, uint8_t);
    void (*f2)(intel8080*, uint16_t);
} opcode_func_t;

typedef struct {
    char instruction[12];
    uint8_t op_bytes;
    uint8_t cycles;
    uint8_t flag_access;

    opcode_func_t handler;
} instr_info_t;

// ===== Data Transfer Group =====
void mov(intel8080 *cpu);
void mvi(intel8080 *cpu, uint8_t data);

// Load/store data from accumulator
void sta(intel8080 *cpu, uint16_t addr);
void lda(intel8080 *cpu, uint16_t addr);

// Load/store data from H and L register
void shld(intel8080 *cpu, uint16_t addr);
void lhld(intel8080 *cpu, uint16_t addr);

// Note: X denotes a register
void stax(intel8080 *cpu);
void ldax(intel8080 *cpu);
void lxi(intel8080 *cpu, uint16_t data);

void xchg(intel8080 *cpu);
void xthl(intel8080 *cpu);
// XCHG // Swaps H and L with D and E
// XTHL // Swaps L with SP and H with SP + 1

void pop_register(intel8080 *cpu);
void push_register(intel8080 *cpu);

// ===== Arithmetic Instructions Group ======
// Add/sub to accumulator
void add(intel8080 *cpu);
void sub(intel8080 *cpu);

// Add/sub from register to accumulator with carry
void adc(intel8080 *cpu);
void sbb(intel8080 *cpu);

// Add/sub immediate data to accumulator
void adi(intel8080 *cpu, uint8_t data);
void sui(intel8080 *cpu, uint8_t data);

// Add/sub immediate data to accumulator and use carry
void aci(intel8080 *cpu, uint8_t data);
void sbi(intel8080 *cpu, uint8_t data);

// Increment/Decrement Register Pair
void inx(intel8080 *cpu);
void dcx(intel8080 *cpu);

// Increment/Decerement the value at the register
void inr(intel8080 *cpu);
void dcr(intel8080 *cpu);

// Double Add
void dad(intel8080 *cpu);

void jmp(intel8080 *cpu, uint16_t addr);
void jz(intel8080 *cpu, uint16_t addr);
void jc(intel8080 *cpu, uint16_t addr);
void jpe(intel8080 *cpu, uint16_t addr);
void jm(intel8080 *cpu, uint16_t addr);

void jnz(intel8080 *cpu, uint16_t addr);
void jnc(intel8080 *cpu, uint16_t addr);
void jpo(intel8080 *cpu, uint16_t addr);
void jp(intel8080 *cpu, uint16_t addr);

void call(intel8080 *cpu, uint16_t data);
void ret(intel8080 *cpu);

extern const instr_info_t opcode_map[0xFF];
