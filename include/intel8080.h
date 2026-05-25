#pragma once 

#include "common.h"
#include "registers.h"

typedef struct {
    uint8_t data[MAX_MEM];
} memory_t;

void init_memory(memory_t *mem);
void reset_memory(registers_t *regs, memory_t *mem, const uint16_t start_pc);

typedef struct {
    /*
     *  $0000-$1FFF 8K ROM
     *  $2000-$23FF 1K Work RAM
     *  $2400-$3FFF Video RAM (7167 bits)
     *  $4000-      RAM Mirror
     */

    uint8_t     *rom;
    memory_t    mem;
    registers_t regs;
    char        rom_name[1024];
    uint16_t    rom_size;
    uint64_t    cycles;

    bool        is_halted;
    bool        ei;         // Enable Interrupt
    bool        interrupt_pending;
    uint8_t     interrupt_vector;

    bool        quit;
    struct {
        bool        display[SCREEN_WIDTH*SCREEN_HEIGHT];
        uint8_t     scale_factor;
    } io;
} intel8080;

bool init_8080(intel8080 *cpu, char *rom_name, const uint16_t start_pc);
void destroy_8080(intel8080 *cpu);
void emulate_8080(intel8080 *cpu);
