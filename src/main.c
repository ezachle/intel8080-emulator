#include <raylib.h>
#include "flags.h"

void emulate_8080(intel8080 *cpu) {
    memory_t *memory = &cpu->mem;
    uint16_t *pc = &cpu->regs.pc;

    uint8_t *instr = &memory->data[*pc];
    const instr_info_t ii = opcode_map[instr[0]];
    if(ii.op_bytes <= 0) {
        printf("Unimplemented opcode: %02X, PC: %04X\n", instr[0], *pc);
        *pc += 1;
    } else {
#ifdef DEBUG
        printf("Instruction: %-12s(0x%02X)\tBytes: %" PRIu8"\tCycles: %" PRIu8"\tPC: %04X\n",
               ii.instruction, *instr, ii.op_bytes, ii.cycles, *pc);
        printf("    Data:");
        for(uint8_t i = 0; i < ii.op_bytes; i++) {
            printf(" %02X", *(instr+i));
        }
        printf("\n");
#endif
        if(ii.handler.f0 != NULL) {
            if(ii.op_bytes == 1) {
                ii.handler.f0(cpu);
            } else if(ii.op_bytes == 2) {
                ii.handler.f1(cpu, *(instr+1));
            } else if(ii.op_bytes == 3) {
                ii.handler.f2(cpu, (*(instr+2) << 8) | *(instr+1));
            }
        } else {
            cpu->regs.pc += ii.op_bytes;
        }
    }
}

int main(int argc, char *argv[]) {
    intel8080 cpu;

    init_8080(&cpu, argv[1]);

    InitWindow(SCREEN_WIDTH * cpu.io.scale_factor, SCREEN_HEIGHT * cpu.io.scale_factor, "Intel8080 Emulator");

    while(!WindowShouldClose()) {
        if(cpu.regs.pc < 0xFFFF)
            emulate_8080(&cpu);

        BeginDrawing();
        ClearBackground(YELLOW);
        EndDrawing();
    }

    destroy_8080(&cpu);

    return 1;
}
