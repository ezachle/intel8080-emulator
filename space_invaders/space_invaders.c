#include <raylib.h>
#include "space_invaders.h"
#include "opcode.h"

static void handle_input(SpaceInvaders *machine) {
    // test setting to 0?
    //  prediction is there might be a stutter....
    uint8_t port1 = 0x03;
    uint8_t port2 = 0;

    uint16_t keycode = GetKeyPressed();
    switch(keycode) {
        case KEY_C:
            port1 |= CREDIT;
            break;
        case KEY_ESCAPE:
            machine->i8080.quit = true;
            break;
        case KEY_ONE:
            port1 |= START_1P;
            break;
        case KEY_TWO:
            port2 |= START_2P;
            break;
        case KEY_LEFT:
            port1 |= LEFT_1P;
            port2 |= LEFT_2P;
            break;
        case KEY_RIGHT:
            port1 |= RIGHT_1P;
            port2 |= RIGHT_2P;
            break;
        case KEY_SPACE:
            port1 |= SHOOT_1P;
            port2 |= SHOOT_2P;
            break;
        default:
            break;
    };

    machine->port1 = port1;
    machine->port2 = port2;
}

static void update_display(SpaceInvaders *machine) {
    /*
     * Screen was physically rotated counter-CW. (0,0) instead started
     * on the bottom left.
     */
    Color *fb      = &machine->io.frame_buffer[0];
    uint8_t *vram    = &machine->i8080.mem.data[VRAM_START]; // VRAM start 0x2400 - 0x3FFF
    uint8_t  scale   = machine->io.scale_factor;

    memset(fb, 0, SCREEN_WIDTH * SCREEN_HEIGHT);

    for(uint16_t i = 0; i < VRAM_SIZE; i++) {
        // Program sees it as (x,y) = (256,224)
        // while the rotated CRT    = (224,256)
        // x runs horizontally from left
        // y runs vertically from top
        // rows are in 8-bit chunks
        uint8_t byte = vram[i];

        // iterate through each bit in the byte
        for(uint8_t bit = 0; bit < 8; bit++) {
            int x = (i % 32) * 8 + bit;
            int y = i / 32;

            Color pixel = ((byte >> bit) & 1) ? WHITE : BLACK;

            int screen_x = y;
            int screen_y = 255 - x;
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
            i8080->regs.a = machine->port1;
            break;
        case 0x02:
            i8080->regs.a = machine->port2;
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
    if(!init_8080(&machine->i8080, "./space_invaders/rom/invaders.rom", 0x0000, machine)) {
        return false;
    }

    memset(machine->io.frame_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
    machine->io.scale_factor = 3;

    set_in(space_invaders_in);
    set_out(space_invaders_out);

    return true;
}

static void destroy_space_invaders(SpaceInvaders *machine) {
    destroy_8080(&machine->i8080);
    UnloadTexture(machine->texture);
    memset(machine->io.frame_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
}

int main() {
    SpaceInvaders machine;
    intel8080 *i8080 = &machine.i8080;

    if(!init_space_invaders(&machine)) {
        return EXIT_FAILURE;
    }

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
