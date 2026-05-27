#pragma once 
#include <stdint.h>

typedef union { 
    struct {
        uint8_t carry: 1;
        uint8_t unused1: 1; // always 1
        uint8_t parity: 1;
        uint8_t unused2: 1; // always 0
        uint8_t aux_carry: 1;
        uint8_t unused3: 1; // always 0
        uint8_t zero: 1;
        uint8_t sign: 1;
    };
} flags_t;

typedef struct {
    union {
        uint16_t hl;
        struct {
            uint8_t l;
            uint8_t h;
        };
    };

    union {
        uint16_t de;
        struct {
            uint8_t e;
            uint8_t d;
        };
    };

    union {
        uint16_t bc;
        struct {
            uint8_t c;
            uint8_t b;
        };
    };

    union {
        uint16_t psw;
        struct {
            flags_t     f;
            uint8_t     a;      // accumulator
        };
    };
    uint16_t    sp;     // stack pointer
    uint16_t    pc;     // program counter
} registers_t;
