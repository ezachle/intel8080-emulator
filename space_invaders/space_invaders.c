#include <raylib.h>
#include "intel8080.h"

int main(int argc, char *argv) {
    intel8080 *cpu = NULL;
    if(!init_8080(cpu, "./invaders.rom", 0x0000)) {
        return false;
    }

    InitWindow(SCREEN_WIDTH * cpu->io.scale_factor, SCREEN_HEIGHT * cpu->io.scale_factor, "Space Invaders");
    SetTargetFPS(60);

    while(!WindowShouldClose() && !cpu->quit) {
        BeginDrawing();
        ClearBackground(YELLOW);
        EndDrawing();
    }

    destroy_8080(cpu);
    return 1;
}
