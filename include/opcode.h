#pragma once

#include "common.h"
#include "intel8080.h"
#include "registers.h"

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

void mov(intel8080 *cpu);
void mvi(intel8080 *cpu, uint8_t data);

void pop_register(intel8080 *cpu);
void push_register(intel8080 *cpu);
void lxi(intel8080 *cpu, uint16_t data);

void ldax(intel8080 *cpu, uint8_t data);
void lda(intel8080 *cpu, uint16_t addr);

void shld(intel8080 *cpu, uint16_t addr);
void lhld(intel8080 *cpu, uint16_t addr);
void dad(intel8080 *cpu);

void add(intel8080 *cpu);
void inx(intel8080 *cpu);
void inr(intel8080 *cpu);
void dcr(intel8080 *cpu);

void stax(intel8080 *cpu);
void sta(intel8080 *cpu, uint16_t addr);

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
