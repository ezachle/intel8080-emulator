#pragma once 
#include <stdint.h>

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
