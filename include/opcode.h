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

void unimplemented_instr(intel8080 *cpu);

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

void xchg(intel8080 *cpu); // Swaps H and L with D and E
void xthl(intel8080 *cpu); // Swaps L with SP and H with SP + 1

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

// ===== Branch Group =====
void jmp(intel8080 *cpu, uint16_t addr);

void rnz(intel8080 *cpu);
void rnc(intel8080 *cpu);
void rpo(intel8080 *cpu);
void rp(intel8080 *cpu);

void jnz(intel8080 *cpu, uint16_t addr);
void jnc(intel8080 *cpu, uint16_t addr);
void jpo(intel8080 *cpu, uint16_t addr);
void jp(intel8080 *cpu, uint16_t addr);

void cnz(intel8080 *cpu, uint16_t addr);
void cnc(intel8080 *cpu, uint16_t addr);
void cpo(intel8080 *cpu, uint16_t addr);
void cp(intel8080 *cpu, uint16_t addr);

void rz(intel8080 *cpu);
void rc(intel8080 *cpu);
void rpe(intel8080 *cpu);
void rm(intel8080 *cpu);

void jz(intel8080 *cpu, uint16_t addr);
void jc(intel8080 *cpu, uint16_t addr);
void jpe(intel8080 *cpu, uint16_t addr);
void jm(intel8080 *cpu, uint16_t addr);

void cz(intel8080 *cpu, uint16_t addr);
void cc(intel8080 *cpu, uint16_t addr);
void cpe(intel8080 *cpu, uint16_t addr);
void cm(intel8080 *cpu, uint16_t addr);

void call(intel8080 *cpu, uint16_t data);
void ret(intel8080 *cpu);
// RST  Restart instr used woth interrupts
void rst(intel8080 *cpu);

void pchl(intel8080 *cpu);
void sphl(intel8080 *cpu);

// ===== Logical Group =====
//ANA Logical AND with Accumulator
void ana(intel8080 *cpu);
//ANI Logical AND with Accumulator Using Immediate Data
void ani(intel8080 *cpu, uint8_t data);
//ORA Logical OR with Accumulator
void ora(intel8080 *cpu);
//ORI Logical OR with Accumulator Using Immediate Data
void ori(intel8080 *cpu, uint8_t data);
//XRA Exclusive Logical OR with Accumulator
void xra(intel8080 *cpu);
//XRI Exclusive OR Using Immediate Data
void xri(intel8080 *cpu, uint8_t data);
//CMP Compare
void cmp(intel8080 *cpu);
void cpi(intel8080 *cpu, uint8_t data);

// Means to roate accumulator one bit position to left or right
void rlc(intel8080* cpu);
void rrc(intel8080* cpu);
void ral(intel8080* cpu);
void rar(intel8080* cpu);

void daa(intel8080 *cpu);
//CMA Complement Accumulator
void cma(intel8080 *cpu);
//CMC Complement Carry Flag
void cmc(intel8080 *cpu);
//STC Set Carry Flag
void stc(intel8080 *cpu);

void hlt(intel8080 *cpu);
void ei(intel8080 *cpu);
void di(intel8080 *cpu);

extern const instr_info_t opcode_map[0x100];
