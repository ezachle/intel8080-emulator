#pragma once 

#include "common.h"
#include "registers.h"

#define CPU_MHZ    (2000000)
#define IO_SIZE    (257)
#define VRAM_START (0x2400)
#define VRAM_SIZE  (7168)

#define PRINT_STATE(cpu) \
    fprintf(stderr, "PC: %04X AF: %04X BC: %04X DE: %04X HL: %04X SP: %04X, CYC: %" PRIu64"\t (%02X %02X %02X %02X)\n", \
    cpu->regs.pc, \
    cpu->regs.psw, \
    cpu->regs.bc, \
    cpu->regs.de, \
    cpu->regs.hl, \
    cpu->regs.sp, \
    cpu->cycles, \
    cpu->mem.data[cpu->regs.pc], \
    cpu->mem.data[cpu->regs.pc+1], \
    cpu->mem.data[cpu->regs.pc+2], \
    cpu->mem.data[cpu->regs.pc+3]);

#define PRINT_FLAGS(cpu) \
    fprintf(stderr, "S=%d Z=%d P=%d AC=%d CY=%d\n", \
    cpu->regs.f.sign, \
    cpu->regs.f.zero, \
    cpu->regs.f.parity, \
    cpu->regs.f.aux_carry, \
    cpu->regs.f.carry);

typedef struct {
    uint8_t data[MAX_MEM];
} memory_t;

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
    uint64_t    rom_size;
    uint64_t    cycles;

    /*
     * The 256 input/output ports provide communication with the outside world of peripheral devices. The IN and
     * OUT instructions initiate data transfers.
     */
    uint8_t     in_reg[IO_SIZE];
    uint8_t     out_reg[IO_SIZE];

    bool        is_halted;
    bool        ei;         // Enable Interrupt
    bool        interrupt_pending;
    uint8_t     interrupt_vector;

    void       *userdata;

    bool        quit;
} intel8080;

bool init_8080(intel8080 *cpu, char *rom_name, const uint16_t start_pc, void *userdata);
void destroy_8080(intel8080 *cpu);
void emulate_8080(intel8080 *cpu);

void reset_memory(registers_t *regs, memory_t *mem, const uint16_t start_pc);
bool run_cpm_tests(intel8080 *cpu);
