#pragma once 

#include <stdint.h>

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
            uint8_t     f;       // cast to flags_t
            uint8_t     a;      // accumulator
        };
    };
    uint16_t    sp;     // stack pointer
    uint16_t    pc;     // program counter
} registers_t;