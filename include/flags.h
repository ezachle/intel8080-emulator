#pragma once

#include "common.h"
#include "intel8080.h"
#include "registers.h"

typedef struct {
    union { 
        bool carry: 1;
        bool unused1: 1; // always 1
        bool parity: 1;
        bool unused2: 1; // always 0
        bool aux_carry: 1;
        bool unused3: 1; // always 1
        bool zero: 1;
        bool sign: 1;
        uint8_t flags;
    };
} flags_t;

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
    uint8_t flags;

    opcode_func_t handler;
} instr_info_t;

void mov_8bit(intel8080 *cpu);
void mvi_8bit(intel8080 *cpu, uint8_t data);

void pop(intel8080 *cpu);
void push(intel8080 *cpu);
void jmp_a16(intel8080 *cpu, uint16_t data);
void lxi_16bit(intel8080 *cpu, uint16_t data);

void ldax_8bit(intel8080 *cpu, uint8_t data);
void lda_16bit(intel8080 *cpu, uint16_t addr);

//void inr_8bit(intel8080 *cpu, uint8_t mem_x);
//void dcr_8bit(intel8080 *cpu, uint8_t mem_x);
//
//void inx_16bit(intel8080 *cpu, uint8_t mem_x);
void call_a16(intel8080 *cpu, uint16_t data);
//void ret(intel8080 *cpu);

extern instr_info_t opcode_map[0xFF];