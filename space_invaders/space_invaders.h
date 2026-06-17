#include "raylib.h"
#include "intel8080.h"

#define FPS (60)
#define FRAME_TIME (1/FPS)
#define INSTR_PER_FRAME (CPU_MHZ / FPS)

typedef struct {
    struct {
        Color       display[SCREEN_WIDTH*SCREEN_HEIGHT];
        uint8_t     scale_factor;
    } io;

    uint8_t shift0;         // LSB of the machine's shift hardware
    uint8_t shift1;         // MSB
    uint8_t shift_offset;   // Offset for machines shift hardware

    uint8_t port1;
    uint8_t port2;

    intel8080 i8080;
} SpaceInvaders;

/*
 *
 * Read
 * ============
 * 00 INPUTS (Mapped in hardware but never used by the code)
 * 01 INPUTS
 * 02 INPUTS
 * 03 bit shift register read
 * 
 * Write
 * ============
 * 02 shift amount (3 bits)
 * 03 sound bits
 * 04 shift data
 * 05 sound bits
 * 06 watch-dog 
 */
typedef enum {
    // IN PORT 1
    CREDIT      = 1,
    START_2P 	= (1 << 1),
    START_1P 	= (1 << 2),
    UNUSED   	= (1 << 3), // Always 1
    SHOOT_1P  	= (1 << 4),
    LEFT_1P  	= (1 << 5),
    RIGHT_1P 	= (1 << 6),

    // IN PORT 2
    DIP3     	= (1 << 0),
    DIP5     	= (1 << 1),
    TILT     	= (1 << 2),
    DIP6     	= (1 << 3),
    SHOOT_2P  	= (1 << 4),
    LEFT_2P  	= (1 << 5),
    RIGHT_2P 	= (1 << 6),
    DIP7     	= (1 << 7),

    // OUT PORT 3
    UFO_SFX     = (1 << 0),
    SHOOT_SFX   = (1 << 1),
    PLAYER_DIE  = (1 << 2),
    INVADER_DIE = (1 << 3),
    EXT_PLAY    = (1 << 4),
    AMP_ENABLE  = (1 << 5),

    // OUT PORT 5
    FLEET_1     = (1 << 0),
    FLEET_2     = (1 << 1),
    FLEET_3     = (1 << 2),
    FLEET_4     = (1 << 3),
    UFO_HIT     = (1 << 4),

} PORT_BITS;

void space_invaders_in(intel8080 *i8080, uint8_t port);
void space_invaders_out(intel8080 *i8080, uint8_t port);
