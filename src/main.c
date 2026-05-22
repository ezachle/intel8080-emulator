// TODO: Include getopt
#include <raylib.h>
#include "log.h"
#include "intel8080.h"

int main(int argc, char *argv[]) {
#ifdef DEBUG
    uint64_t instr_count = 0;
#endif
    intel8080 cpu;

    // CPM tests has the PC starts at 0x0100
    init_8080(&cpu, argv[1], 0x0100);

    InitWindow(SCREEN_WIDTH * cpu.io.scale_factor, SCREEN_HEIGHT * cpu.io.scale_factor, "Intel8080 Emulator");
    SetTargetFPS(60);

    LOG(cpu.regs.pc, "Starting ROM %s", cpu.rom_name);
    while(!WindowShouldClose()) {
        if(cpu.regs.pc < 0xFFFF) {
#ifdef DEBUG
            LOG_DEBUG(cpu.regs.pc, "---------------------`------\n");
            LOG_DEBUG(cpu.regs.pc, "Instruction %" PRIu64": ", instr_count);
            instr_count += 1;
#endif
            emulate_8080(&cpu);
        }

        BeginDrawing();
        ClearBackground(YELLOW);
        EndDrawing();
    }

    destroy_8080(&cpu);

    return 1;
}
