// TODO: Include getopt
#include <raylib.h>
#include "opcode.h"

void emulate_8080(intel8080 *cpu) {
    memory_t *memory = &cpu->mem;
    uint16_t *pc = &cpu->regs.pc;

    uint8_t *instr = &memory->data[*pc];
    const instr_info_t ii = opcode_map[instr[0]];
    if(ii.op_bytes <= 0) {
        printf("Unimplemented opcode: %02X, PC: %04X\n", instr[0], *pc);
        *pc += 1;
    } else {
        if(ii.handler.f0 != NULL) {
            if(ii.op_bytes == 1) {
                ii.handler.f0(cpu);
            } else if(ii.op_bytes == 2) {
                ii.handler.f1(cpu, *(instr+1));
            } else if(ii.op_bytes == 3) {
                ii.handler.f2(cpu, (*(instr+2) << 8) | *(instr+1));
            }
        } else {
            printf("Unimplemented opcode: %02X, PC: %04X\n", instr[0], *pc);
            cpu->regs.pc += ii.op_bytes;
        }

        cpu->cycles += ii.cycles;
#ifdef DEBUG
        printf("Instruction: %-12s(0x%02X)\tBytes: %" PRIu8"\tCycles: %" PRIu8"\tPC: %04X\n",
               ii.instruction, *instr, ii.op_bytes, ii.cycles, *pc);
        printf("  Registers:\n");
        printf("   sp: 0x%04X\n", cpu->regs.sp);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.sp, cpu->mem.data[cpu->regs.sp]);
        printf("   pc: 0x%04X\n", cpu->regs.pc);
        printf("   af: 0x%04X\n", cpu->regs.psw);
        printf("    Flags:\n");
        printf("     carry: %" PRIu8"\n", cpu->regs.f.carry);
        printf("     parity: %" PRIu8"\n", cpu->regs.f.parity);
        printf("     aux_carry: %" PRIu8"\n", cpu->regs.f.aux_carry);
        printf("     zero: %" PRIu8"\n", cpu->regs.f.zero);
        printf("     sign: %" PRIu8"\n", cpu->regs.f.sign);
        printf("   bc: 0x%04X\n", cpu->regs.bc);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.bc, cpu->mem.data[cpu->regs.bc]);
        printf("   de: 0x%04X\n", cpu->regs.de);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.de, cpu->mem.data[cpu->regs.de]);
        printf("   hl: 0x%04X\n", cpu->regs.hl);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.hl, cpu->mem.data[cpu->regs.hl]);
        printf("  Data:");
        for(uint8_t i = 0; i < ii.op_bytes; i++) {
            printf(" %02X", *(instr+i));
        }
        printf("\nTotal Cycles: %" PRIu64, cpu->cycles);
        printf("\n");
#endif
    }
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
    uint64_t instr_count = 0;
#endif
    intel8080 cpu;

    init_8080(&cpu, argv[1]);

    InitWindow(SCREEN_WIDTH * cpu.io.scale_factor, SCREEN_HEIGHT * cpu.io.scale_factor, "Intel8080 Emulator");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        if(cpu.regs.pc < 0xFFFF) {
#ifdef DEBUG
            printf("%" PRIu64") ", instr_count);
#endif
            emulate_8080(&cpu);
            instr_count += 1;
        }

        BeginDrawing();
        ClearBackground(YELLOW);
        EndDrawing();
    }

    destroy_8080(&cpu);

    return 1;
}
