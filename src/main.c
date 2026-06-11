// TODO: Include getopt
#include <raylib.h>
#include "log.h"
#include "intel8080.h"

int main(int argc, char *argv[]) {
    intel8080 cpu;

    bool rc = true;
#ifdef CPM
    // CPM tests has the PC starts at 0x0100
    rc = run_cpm_tests(&cpu);
    return rc;
#else
    rc = init_8080(&cpu, argv[1], 0x0000);
#endif

    if(!rc) return rc;

    InitWindow(SCREEN_WIDTH * cpu.io.scale_factor, SCREEN_HEIGHT * cpu.io.scale_factor, "Intel8080 Emulator");
    SetTargetFPS(60);

    LOG(cpu.regs.pc, "Starting ROM %s", cpu.rom_name);
    while(!WindowShouldClose() && !cpu.quit) {
        if(cpu.regs.pc < 0xFFFF) {
            emulate_8080(&cpu);
        }

        BeginDrawing();
        ClearBackground(YELLOW);
        EndDrawing();
    }

    destroy_8080(&cpu);

    return 1;
}
