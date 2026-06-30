#include <raylib.h>
#include "space_invaders.h"
#include "opcode.h"

static void handle_input(SpaceInvaders *machine) {
    uint8_t port1 = 0x03;
    uint8_t port2 = 0;

    if(IsKeyDown(KEY_ESCAPE)) machine->i8080->quit = true;
    if(IsKeyDown(KEY_C)) port1 |= CREDIT;
    if(IsKeyDown(KEY_ONE)) port1 = START_1P;
    if(IsKeyDown(KEY_TWO)) port2 |= START_2P;
    if(IsKeyDown(KEY_LEFT)) { port1 |= LEFT_1P; port2 |= LEFT_2P; }
    if(IsKeyDown(KEY_RIGHT)) { port1 |= RIGHT_1P; port2 |= RIGHT_2P; }
    if(IsKeyDown(KEY_SPACE)) { port1 |= SHOOT_1P; port2 |= SHOOT_2P; }

    machine->io.port1 = port1;
    machine->io.port2 = port2;
}

static void clear_buffer(SpaceInvaders *machine) {
    memset(machine->io.frame_buffer, 0, sizeof(Color) * SCREEN_WIDTH * SCREEN_HEIGHT);
}

static void update_display(SpaceInvaders *machine) {
    /*
     * Original CRT monitor was using a 256x224 monitor but is rotated
     * counter-clockwise 90 deg and is instead 224x256.
     *  - frame buffer is described as 224 rows and 256 columns.
     *  - each byte represents 8 vertical pixels in a column
     */
    Color *fb      = &machine->io.frame_buffer[0];
    uint8_t *vram    = &machine->i8080->mem.data[VRAM_START]; // VRAM start 0x2400 - 0x3FFF

    clear_buffer(machine);

    for(uint16_t i = 0; i < VRAM_SIZE; i++) {
        uint8_t byte = vram[i];

        int x = (i % 32); // vertical pixel offset
        int y = i / 32;   // track rows

        for(uint8_t bit = 0; bit < 8; bit++) {
            Color pixel = ((byte >> bit) & 1) ? WHITE : BLACK;

            // rotate the screen here
            int screen_x = y;
            int screen_y = 255 - (x * 8 + bit);
            fb[screen_x + screen_y * SCREEN_WIDTH] = pixel;
        }
    }

    UpdateTexture(machine->texture, fb);
}

void space_invaders_in(intel8080 *i8080, uint8_t port) {
/*
 * Read
 *  00 INPUTS (Mapped in hardware but never used by the code)
 *  01 INPUTS
 *  02 INPUTS
 *  03 bit shift register read
 *
 */
    SpaceInvaders *machine = (SpaceInvaders*)i8080->userdata;
    switch(port) {
        case 0x01:
            i8080->regs.a = machine->io.port1;
            break;
        case 0x02:
            i8080->regs.a = machine->io.port2;
            break;
        case 0x03:
            // dedicated shift HW to position a 8-bit pixel image into a 16-bit word
            // for the desired pixel position on the screen
            uint16_t value = ((machine->shift1 << 8) | machine->shift0);
            i8080->regs.a = ((value >> (8 - machine->shift_offset)) & 0xFF);
            break;
        case 0x00: // unused
        default:
            break;
    }
}

void space_invaders_out(intel8080 *i8080, uint8_t port) {
    /*
     * Write
     * 02 shift amount (3 bits)
     * 03 sound bits
     * 04 shift data
     * 05 sound bits
     * 06 watch-dog
     */
    SpaceInvaders *machine = (SpaceInvaders*)i8080->userdata;
    switch(port) {
        case 0x02:
            machine->shift_offset = i8080->regs.a & 0x7;
            break;
        case 0x04:
            machine->shift0 = machine->shift1;
            machine->shift1 = i8080->regs.a;
            break;
        case 0x03:
        case 0x05:
        case 0x06:
        default:
            break;
    }
}

static bool init_space_invaders(SpaceInvaders *machine) {
    machine->i8080 = (intel8080*)malloc(sizeof(intel8080));
    if(!init_8080(machine->i8080, "./space_invaders/rom/invaders.rom", 0x0000, machine)) {
        return false;
    }

    clear_buffer(machine);
    machine->io.scale_factor = 3;

    set_in(space_invaders_in);
    set_out(space_invaders_out);

    return true;
}

static void destroy_space_invaders(SpaceInvaders *machine) {
    destroy_8080(machine->i8080);
    UnloadTexture(machine->texture);
    free(machine->i8080);
    clear_buffer(machine);
}

int main() {
    SpaceInvaders machine;
    if(!init_space_invaders(&machine)) {
        return EXIT_FAILURE;
    }

    intel8080 *i8080 = machine.i8080;

    InitWindow(SCREEN_WIDTH * machine.io.scale_factor, SCREEN_HEIGHT * machine.io.scale_factor, "Space Invaders");
    SetTargetFPS(FPS);

    Image blank = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    machine.texture = LoadTextureFromImage(blank);
    UnloadImage(blank);

    double last_frame = GetTime();

    /*
     * 2MHz == 2,000,000 hz / 60 FPS = 33,3333 instructions per frame
     * Frame time = 1 second / 60 FPS = 16.6667 ms
     *
     * CRT displays images line by line, from top to bottom, then returns to
     * the top through a vertical blank interrupt. 
     *
     *  - RST1 - The VBL roughly reached the middle of the screen
     *  - RST2 - The VBL reached the bottom of the screen
     *
     * Between interrupts, the CPU will run roughly 16,667 cycles, or
     * roughly 33,333 cycles for the entire screen per frame.
     *
     */
    while(!WindowShouldClose() && !i8080->quit) {
        last_frame = GetTime();
        handle_input(&machine);

        while(i8080->cycles < INSTR_PER_FRAME / 2) {
            emulate_8080(i8080);
        }
        generate_interrupt(i8080, 0xCF); // RST 1

        while(i8080->cycles < INSTR_PER_FRAME) {
            emulate_8080(i8080);
        }
        generate_interrupt(i8080, 0xD7); // RST 2

        update_display(&machine);

BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureEx(machine.texture, (Vector2){0,0}, 0, machine.io.scale_factor, WHITE);
EndDrawing();

        double elapsed = GetTime() - last_frame;
        if(elapsed < FRAME_TIME) {
            WaitTime(FRAME_TIME - elapsed);
        }
        i8080->cycles = 0;
    }

    destroy_space_invaders(&machine);
    CloseWindow();

    return EXIT_SUCCESS;
}
