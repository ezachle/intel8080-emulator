#include "log.h"
#include "opcode.h"

const instr_info_t opcode_map[0x100] = {
    [0x00] = {"NOP", 1, 4, MAKE_FLAG_NONE, {.f0 = NULL}},
    [0x10] = {"NOP", 1, 4, MAKE_FLAG_NONE, {.f0 = NULL}},
    [0x20] = {"NOP", 1, 4, MAKE_FLAG_NONE, {.f0 = NULL}},
    [0x30] = {"NOP", 1, 4, MAKE_FLAG_NONE, {.f0 = NULL}},

    [0xCB] = {"JMP a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jmp}},
    [0xC3] = {"JMP a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jmp}},
    [0xC9] = {"RET", 1, 10, MAKE_FLAG_NONE, {.f0 = ret}},
    [0xD9] = {"RET", 1, 10, MAKE_FLAG_NONE, {.f0 = ret}},
    [0xCD] = {"CALL a16", 3, 17, MAKE_FLAG_NONE, {.f2 = call}},

    [0xE9] = {"PCHL", 1, 5, MAKE_FLAG_NONE, {.f0 = pchl}},
    [0xF9] = {"SPHL", 1, 5, MAKE_FLAG_NONE, {.f0 = sphl}},

    [0xC7] = {"RST 0", 1, 11, MAKE_FLAG_NONE, {.f0 = rst}},
    [0xD7] = {"RST 2", 1, 11, MAKE_FLAG_NONE, {.f0 = rst}},
    [0xE7] = {"RST 4", 1, 11, MAKE_FLAG_NONE, {.f0 = rst}},
    [0xF7] = {"RST 6", 1, 11, MAKE_FLAG_NONE, {.f0 = rst}},

    [0xCF] = {"RST 1", 1, 11, MAKE_FLAG_NONE, {.f0 = rst}},
    [0xDF] = {"RST 3", 1, 11, MAKE_FLAG_NONE, {.f0 = rst}},
    [0xEF] = {"RST 5", 1, 11, MAKE_FLAG_NONE, {.f0 = rst}},
    [0xFF] = {"RST 7", 1, 11, MAKE_FLAG_NONE, {.f0 = rst}},

    [0xC0] = {"RNZ", 1, 5, MAKE_FLAG_NONE, {.f0 = rnz}},
    [0xD0] = {"RNC", 1, 5, MAKE_FLAG_NONE, {.f0 = rnz}},
    [0xE0] = {"RPO", 1, 5, MAKE_FLAG_NONE, {.f0 = rnz}},
    [0xF0] = {"RP", 1, 5, MAKE_FLAG_NONE, {.f0 = rnz}},

    [0xC2] = {"JNZ a16", 3, 10, MAKE_FLAG_NONE, { .f2 = jnz}},
    [0xD2] = {"JNC a16", 3, 10, MAKE_FLAG_NONE, { .f2 = jnc}},
    [0xE2] = {"JPO a16", 3, 10, MAKE_FLAG_NONE, { .f2 = jpo}},
    [0xF2] = {"JP a16", 3, 10, MAKE_FLAG_NONE, { .f2 = jp}},

    [0xC4] = {"CNZ a16", 3, 11, MAKE_FLAG_NONE, {.f2 = cnz}},
    [0xD4] = {"CNC a16", 3, 11, MAKE_FLAG_NONE, {.f2 = cnc}},
    [0xE4] = {"CPO a16", 3, 11, MAKE_FLAG_NONE, {.f2 = cpo}},
    [0xF4] = {"CP a16", 3, 11, MAKE_FLAG_NONE, {.f2 = cp}},

    [0xC8] = {"RZ", 1, 5, MAKE_FLAG_NONE, {.f0  = rz}},
    [0xD8] = {"RC", 1, 5, MAKE_FLAG_NONE, {.f0  = rc}},
    [0xE8] = {"RPE", 1, 5, MAKE_FLAG_NONE, {.f0 = rpe}},
    [0xF8] = {"RM", 1, 5, MAKE_FLAG_NONE, {.f0  = rm}},

    [0xCA] = {"JZ a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jz}},
    [0xDA] = {"JC a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jc}},
    [0xEA] = {"JPE a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jpe}},
    [0xFA] = {"JM a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jm}},

    [0xCC] = {"CZ a16", 3, 11, MAKE_FLAG_NONE, {.f2 = cz}},
    [0xDC] = {"CC a16", 3, 11, MAKE_FLAG_NONE, {.f2 = cc}},
    [0xEC] = {"CPE a16",  3, 11, MAKE_FLAG_NONE, {.f2 = cpe}},
    [0xFC] = {"CM a16", 3, 11, MAKE_FLAG_NONE, {.f2 = cm}},

    [0xC1] = {"POP B", 1, 10, MAKE_FLAG_NONE, {.f0 = pop_register}},
    [0xD1] = {"POP D", 1, 10, MAKE_FLAG_NONE, {.f0 = pop_register}},
    [0xE1] = {"POP H", 1, 10, MAKE_FLAG_NONE, {.f0 = pop_register}},
    [0xF1] = {"POP PSW", 1, 10, MAKE_FLAG_ALL, {.f0 = pop_register}},

    [0xC5] = {"PUSH B", 1, 11, MAKE_FLAG_NONE, {.f0 = push_register}},
    [0xD5] = {"PUSH D", 1, 11, MAKE_FLAG_NONE, {.f0 = push_register}},
    [0xE5] = {"PUSH H", 1, 11, MAKE_FLAG_NONE, {.f0 = push_register}},
    [0xF5] = {"PUSH PSW", 1, 11, MAKE_FLAG_ALL, {.f0 = push_register}},

    // ==== Arithmetic Group ====
    [0x80] = {"ADD B", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x81] = {"ADD C", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x82] = {"ADD D", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x83] = {"ADD E", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x84] = {"ADD H", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x85] = {"ADD L", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x86] = {"ADD M", 1, 7, MAKE_FLAG_ALL, {.f0 = add}},
    [0x87] = {"ADD A", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},

    [0x90] = {"SUB B", 1, 4, MAKE_FLAG_ALL, {.f0 = sub}},
    [0x91] = {"SUB C", 1, 4, MAKE_FLAG_ALL, {.f0 = sub}},
    [0x92] = {"SUB D", 1, 4, MAKE_FLAG_ALL, {.f0 = sub}},
    [0x93] = {"SUB E", 1, 4, MAKE_FLAG_ALL, {.f0 = sub}},
    [0x94] = {"SUB H", 1, 4, MAKE_FLAG_ALL, {.f0 = sub}},
    [0x95] = {"SUB L", 1, 4, MAKE_FLAG_ALL, {.f0 = sub}},
    [0x96] = {"SUB M", 1, 7, MAKE_FLAG_ALL, {.f0 = sub}},
    [0x97] = {"SUB A", 1, 4, MAKE_FLAG_ALL, {.f0 = sub}},

    [0xC6] = {"ADI d8", 2, 7, MAKE_FLAG_ALL, {.f1 = adi}},
    [0xD6] = {"SUI d8", 2, 7, MAKE_FLAG_ALL, {.f1 = sui}},

    [0xCE] = {"ACI d8", 2, 7, MAKE_FLAG_ALL, {.f1 = aci}},
    [0xDE] = {"SBI d8", 2, 7, MAKE_FLAG_ALL, {.f1 = sbi}},

    [0x88] = {"ADC B", 1, 5, MAKE_FLAG_NONE, {.f0 = adc}},
    [0x89] = {"ADC C", 1, 5, MAKE_FLAG_NONE, {.f0 = adc}},
    [0x8A] = {"ADC D", 1, 5, MAKE_FLAG_NONE, {.f0 = adc}},
    [0x8B] = {"ADC E", 1, 5, MAKE_FLAG_NONE, {.f0 = adc}},
    [0x8C] = {"ADC H", 1, 5, MAKE_FLAG_NONE, {.f0 = adc}},
    [0x8D] = {"ADC L", 1, 5, MAKE_FLAG_NONE, {.f0 = adc}},
    [0x8E] = {"ADC M", 1, 7, MAKE_FLAG_NONE, {.f0 = adc}},
    [0x8F] = {"ADC A", 1, 5, MAKE_FLAG_NONE, {.f0 = adc}},

    [0x98] = {"SBB B", 1, 5, MAKE_FLAG_NONE, {.f0 = sbb}},
    [0x99] = {"SBB C", 1, 5, MAKE_FLAG_NONE, {.f0 = sbb}},
    [0x9A] = {"SBB D", 1, 5, MAKE_FLAG_NONE, {.f0 = sbb}},
    [0x9B] = {"SBB E", 1, 5, MAKE_FLAG_NONE, {.f0 = sbb}},
    [0x9C] = {"SBB H", 1, 5, MAKE_FLAG_NONE, {.f0 = sbb}},
    [0x9D] = {"SBB L", 1, 5, MAKE_FLAG_NONE, {.f0 = sbb}},
    [0x9E] = {"SBB M", 1, 7, MAKE_FLAG_NONE, {.f0 = sbb}},
    [0x9F] = {"SBB A", 1, 5, MAKE_FLAG_NONE, {.f0 = sbb}},

    [0x05] = {"DCR B", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x15] = {"DCR D", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x25] = {"DCR H", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x35] = {"DCR M", 1, 10, MAKE_FLAG_SZAP, {.f0 = dcr}},

    [0x0D] = {"DCR C", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x1D] = {"DCR E", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x2D] = {"DCR L", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x3D] = {"DCR A", 1, 10, MAKE_FLAG_SZAP, {.f0 = dcr}},

    [0x0B] = {"DCX B", 1, 5, MAKE_FLAG_NONE, {.f0 = dcx}},
    [0x1B] = {"DCX D", 1, 5, MAKE_FLAG_NONE, {.f0 = dcx}},
    [0x2B] = {"DCX H", 1, 5, MAKE_FLAG_NONE, {.f0 = dcx}},
    [0x3B] = {"DCX SP", 1, 5, MAKE_FLAG_NONE, {.f0 = dcx}},

    [0x03] = {"INX B", 1, 5, MAKE_FLAG_NONE, {.f0 = inx}},
    [0x13] = {"INX D", 1, 5, MAKE_FLAG_NONE, {.f0 = inx}},
    [0x23] = {"INX H", 1, 5, MAKE_FLAG_NONE, {.f0 = inx}},
    [0x33] = {"INX SP", 1, 5, MAKE_FLAG_NONE, {.f0 = inx}},

    [0x04] = {"INR B", 1, 5, MAKE_FLAG_SZAP, {.f0 = inr}},
    [0x14] = {"INR D", 1, 5, MAKE_FLAG_SZAP, {.f0 = inr}},
    [0x24] = {"INR H", 1, 5, MAKE_FLAG_SZAP, {.f0 = inr}},
    [0x34] = {"INR M", 1, 10, MAKE_FLAG_SZAP, {.f0 = inr}},

    [0x0C] = {"INR B", 1, 5, MAKE_FLAG_SZAP, {.f0 = inr}},
    [0x1C] = {"INR D", 1, 5, MAKE_FLAG_SZAP, {.f0 = inr}},
    [0x2C] = {"INR H", 1, 5, MAKE_FLAG_SZAP, {.f0 = inr}},
    [0x3C] = {"INR A", 1, 5, MAKE_FLAG_SZAP, {.f0 = inr}},

    [0x09] = {"DAD B", 1, 10, MAKE_FLAG_CARRY, {.f0 = dad}},
    [0x19] = {"DAD C", 1, 10, MAKE_FLAG_CARRY, {.f0 = dad}},
    [0x29] = {"DAD H", 1, 10, MAKE_FLAG_CARRY, {.f0 = dad}},
    [0x39] = {"DAD SP", 1, 10, MAKE_FLAG_CARRY, {.f0 = dad}},

    // ==== Data Transfer Group ====

    [0x40] = {"MOV B, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x41] = {"MOV B, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x42] = {"MOV B, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x43] = {"MOV B, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x44] = {"MOV B, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x45] = {"MOV B, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x46] = {"MOV B, M", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x47] = {"MOV B, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x48] = {"MOV C, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x49] = {"MOV C, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4A] = {"MOV C, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4B] = {"MOV C, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4C] = {"MOV C, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4D] = {"MOV C, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4E] = {"MOV C, M", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4F] = {"MOV C, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x50] = {"MOV D, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x51] = {"MOV D, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x52] = {"MOV D, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x53] = {"MOV D, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x54] = {"MOV D, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x55] = {"MOV D, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x56] = {"MOV D, M", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x57] = {"MOV D, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x58] = {"MOV E, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x59] = {"MOV E, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5A] = {"MOV E, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5B] = {"MOV E, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5C] = {"MOV E, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5D] = {"MOV E, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5E] = {"MOV E, M", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5F] = {"MOV E, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x60] = {"MOV H, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x61] = {"MOV H, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x62] = {"MOV H, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x63] = {"MOV H, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x64] = {"MOV H, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x65] = {"MOV H, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x66] = {"MOV H, M", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x67] = {"MOV H, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x68] = {"MOV L, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x69] = {"MOV L, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6A] = {"MOV L, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6B] = {"MOV L, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6C] = {"MOV L, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6D] = {"MOV L, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6E] = {"MOV L, M", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6F] = {"MOV L, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x70] = {"MOV M, B", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x71] = {"MOV M, C", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x72] = {"MOV M, D", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x73] = {"MOV M, E", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x74] = {"MOV M, H", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x75] = {"MOV M, L", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x77] = {"MOV M, A", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x78] = {"MOV A, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x79] = {"MOV A, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7A] = {"MOV A, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7B] = {"MOV A, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7C] = {"MOV A, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7D] = {"MOV A, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7E] = {"MOV A, M", 1, 7, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7F] = {"MOV A, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    // Move the 8-bit raw value into the register
    [0x06] = {"MVI B, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x0E] = {"MVI C, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x16] = {"MVI D, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x1E] = {"MVI E, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x26] = {"MVI H, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x2E] = {"MVI L, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x36] = {"MVI M, d8", 2, 10, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x3E] = {"MVI A, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},

    [0x32] = {"STA a16", 3, 13, MAKE_FLAG_NONE, {.f2 = sta}},
    [0x3A] = {"LDA a16", 3, 13, MAKE_FLAG_NONE, {.f2 = lda}},

    [0x22] = {"SHLD a16", 3, 16, MAKE_FLAG_NONE, {.f2 = shld}},
    [0x2A] = {"LHLD a16", 3, 16, MAKE_FLAG_NONE, {.f2 = lhld}},

    // Load the 16-bit raw value into the register (BDH) or SP
    [0x01] = {"LXI B, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi}},
    [0x11] = {"LXI D, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi}},
    [0x21] = {"LXI H, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi}},
    [0x31] = {"LXI SP, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi}},

    [0x0A] = {"LDAX B", 1, 7, MAKE_FLAG_NONE, {.f0 = ldax}},
    [0x1A] = {"LDAX D", 1, 7, MAKE_FLAG_NONE, {.f0 = ldax}},
    [0x02] = {"STAX B", 1, 7, MAKE_FLAG_NONE, {.f0 = stax}},
    [0X12] = {"STAX D", 1, 7, MAKE_FLAG_NONE, {.f0 = stax}},
    [0xE3] = {"XTHL", 1, 18, MAKE_FLAG_NONE, {.f0 = xthl}},
    [0xEB] = {"XCHG", 1, 5, MAKE_FLAG_NONE, {.f0 = xchg}},

    // ==== Logical Group ====
    [0xA0] = {"ANA B", 1, 4, MAKE_FLAG_ALL, {.f0 = ana}},
    [0xA1] = {"ANA C", 1, 4, MAKE_FLAG_ALL, {.f0 = ana}},
    [0xA2] = {"ANA D", 1, 4, MAKE_FLAG_ALL, {.f0 = ana}},
    [0xA3] = {"ANA E", 1, 4, MAKE_FLAG_ALL, {.f0 = ana}},
    [0xA4] = {"ANA H", 1, 4, MAKE_FLAG_ALL, {.f0 = ana}},
    [0xA5] = {"ANA L", 1, 4, MAKE_FLAG_ALL, {.f0 = ana}},
    [0xA6] = {"ANA M", 1, 7, MAKE_FLAG_ALL, {.f0 = ana}},
    [0xA7] = {"ANA A", 1, 4, MAKE_FLAG_ALL, {.f0 = ana}},

    [0xB0] = {"ORA B", 1, 4, MAKE_FLAG_ALL, {.f0 = ora}},
    [0xB1] = {"ORA C", 1, 4, MAKE_FLAG_ALL, {.f0 = ora}},
    [0xB2] = {"ORA D", 1, 4, MAKE_FLAG_ALL, {.f0 = ora}},
    [0xB3] = {"ORA E", 1, 4, MAKE_FLAG_ALL, {.f0 = ora}},
    [0xB4] = {"ORA H", 1, 4, MAKE_FLAG_ALL, {.f0 = ora}},
    [0xB5] = {"ORA L", 1, 4, MAKE_FLAG_ALL, {.f0 = ora}},
    [0xB6] = {"ORA M", 1, 7, MAKE_FLAG_ALL, {.f0 = ora}},
    [0xB7] = {"ORA A", 1, 4, MAKE_FLAG_ALL, {.f0 = ora}},

    [0xE6] = {"ANI d8", 2, 7, MAKE_FLAG_ALL, {.f1 = ani}},
    [0xF6] = {"ORI d8", 2, 7, MAKE_FLAG_ALL, {.f1 = ori}},

    [0xA8] = {"XRA B", 1, 5, MAKE_FLAG_ALL, {.f0 = xra}},
    [0xA9] = {"XRA C", 1, 5, MAKE_FLAG_ALL, {.f0 = xra}},
    [0xAA] = {"XRA D", 1, 5, MAKE_FLAG_ALL, {.f0 = xra}},
    [0xAB] = {"XRA E", 1, 5, MAKE_FLAG_ALL, {.f0 = xra}},
    [0xAC] = {"XRA H", 1, 5, MAKE_FLAG_ALL, {.f0 = xra}},
    [0xAD] = {"XRA L", 1, 5, MAKE_FLAG_ALL, {.f0 = xra}},
    [0xAE] = {"XRA M", 1, 7, MAKE_FLAG_ALL, {.f0 = xra}},
    [0xAF] = {"XRA A", 1, 5, MAKE_FLAG_ALL, {.f0 = xra}},

    [0xB8] = {"CMP B", 1, 5, MAKE_FLAG_ALL, {.f0 = cmp}},
    [0xB9] = {"CMP C", 1, 5, MAKE_FLAG_ALL, {.f0 = cmp}},
    [0xBA] = {"CMP D", 1, 5, MAKE_FLAG_ALL, {.f0 = cmp}},
    [0xBB] = {"CMP E", 1, 5, MAKE_FLAG_ALL, {.f0 = cmp}},
    [0xBC] = {"CMP H", 1, 5, MAKE_FLAG_ALL, {.f0 = cmp}},
    [0xBD] = {"CMP L", 1, 5, MAKE_FLAG_ALL, {.f0 = cmp}},
    [0xBE] = {"CMP M", 1, 7, MAKE_FLAG_ALL, {.f0 = cmp}},
    [0xBF] = {"CMP A", 1, 5, MAKE_FLAG_ALL, {.f0 = cmp}},

    [0xEE] = {"XRI d8", 2, 7, MAKE_FLAG_ALL, {.f1 = xri}},
    [0xFE] = {"CPI d8", 2, 7, MAKE_FLAG_ALL, {.f1 = cpi}},

    [0x07] = {"RLC", 1, 4, MAKE_FLAG_CARRY, {.f0 = rlc}},
    [0x17] = {"RRC", 1, 4, MAKE_FLAG_CARRY, {.f0 = rrc}},
    [0x0F] = {"RAL", 1, 4, MAKE_FLAG_CARRY, {.f0 = ral}},
    [0x1F] = {"RAR", 1, 4, MAKE_FLAG_CARRY, {.f0 = rar}},

    [0x27] = {"DAA", 1, 4, MAKE_FLAG_ALL,   {.f0 = daa}},
    [0x37] = {"STC", 1, 4, MAKE_FLAG_CARRY, {.f0 = stc}},
    [0x2F] = {"CMA", 1, 4, MAKE_FLAG_NONE,  {.f0 = cma}},
    [0x3F] = {"CMC", 1, 4, MAKE_FLAG_CARRY, {.f0 = cmc}},

    // d8 == port
    [0xD3] = {"OUT d8", 2, 10, MAKE_FLAG_NONE, {.f0 = unimplemented_instr}},
    [0xDB] = {"IN d8", 2, 10, MAKE_FLAG_NONE,  {.f0 = unimplemented_instr}},

    [0x76] = {"HLT", 1, 7, MAKE_FLAG_NONE, {.f0 = hlt}},
    [0xF3] = {"EI", 1, 4, MAKE_FLAG_NONE, {.f0 = ei}},
    [0xFB] = {"DI", 1, 4, MAKE_FLAG_NONE, {.f0 = di}},
};

typedef enum {
    REG_B = 0,
    REG_C = 1,
    REG_D = 2,
    REG_E = 3,
    REG_H = 4,
    REG_L = 5,
    REG_M = 6,
    REG_A = 7,
} registers;

#define CUR_OP(cpu) ((cpu)->mem.data[(cpu)->regs.pc])
#define GET_INSTR(op) (opcode_map[op])
#define GET_INSTR_CPU(cpu) (opcode_map[CUR_OP(cpu)])
#define INSTR_SIZE(cpu) ((GET_INSTR_CPU(cpu)).op_bytes)

#define FLAG_ACCESS(cpu) (GET_INSTR_CPU(cpu).flag_access)
#define HAS_ACCESS(flag_access, x) (flag_access & (1 << x))

#define OP_DST_REG(cpu)  ((CUR_OP(cpu) & 0x38) >> 3)
#define OP_SRC_REG(cpu)  (CUR_OP(cpu) & 0x7)

#define SET_FLAG(flags, x) (flags &= (1 << x))

typedef enum {
    CARRY = 0,
    PARITY = 2,
    AUX_CARRY = 4,
    ZERO = 6,
    SIGN = 7,
    NONE,
} FLAGS;

static void swap_u8(uint8_t *a, uint8_t *b) {
    uint8_t t = *a;
    *a = *b;
    *b = t;
}

static void swap_u16(uint16_t *a, uint16_t *b) {
    uint16_t t = *a;
    *a = *b;
    *b = t;
}


static void modify_flags(uint16_t value, registers_t *regs, const uint8_t flag_access) {
    if(HAS_ACCESS(flag_access, SIGN)) {
        regs->f.sign = (value & (1 << SIGN)) & 0x1;
    }

    if(HAS_ACCESS(flag_access, ZERO)) {
        regs->f.zero = (value == 0);
    }

    // 0 == Even Parity
    // 1 == Odd Parity
    if(HAS_ACCESS(flag_access, PARITY)) {
        regs->f.parity ^= (value >> 8);
        regs->f.parity ^= (regs->f.parity >> 4);
        regs->f.parity ^= (regs->f.parity >> 2);
        regs->f.parity ^= (regs->f.parity>> 1);
    }

    if(HAS_ACCESS(flag_access, AUX_CARRY)) {
        regs->f.aux_carry = (value & 0x10);
    }

    // Check for carry
    if(HAS_ACCESS(flag_access, CARRY)) {
        regs->f.carry = (value & 0xFF00) ? 1 : 0;
    }
}

#ifdef DEBUG
static char get_register_char(registers reg) {
    switch(reg) {
        case REG_B: return 'B';
        case REG_C: return 'C';
        case REG_D: return 'D';
        case REG_E: return 'E';
        case REG_H: return 'H';
        case REG_L: return 'L';
        case REG_M: return 'M';
        case REG_A: return 'A';
    }

    return '\0';
}
#endif

static uint8_t* get_register(intel8080 *cpu, registers reg) {
    registers_t *regs = &cpu->regs;
    switch(reg) {
        case REG_B:
            return &regs->b;
        case REG_C:
            return &regs->c;
        case REG_D:
            return &regs->d;
        case REG_E:
            return &regs->e;
        case REG_H:
            return &regs->h;
        case REG_L:
            return &regs->l;
        case REG_M:
            return &cpu->mem.data[regs->hl];
        case REG_A:
            return &regs->a;
        default:
            LOG_ERROR(cpu->regs.pc, "Unknown register %d", reg);
            return NULL;
    }
}

void unimplemented_instr(intel8080 *cpu) {
    LOG_WARNING(cpu->regs.pc, "%s: Unimplemented instruction", GET_INSTR_CPU(cpu).instruction);
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void mov(intel8080 *cpu) {
    registers reg_src = OP_SRC_REG(cpu);
    registers reg_dst = OP_DST_REG(cpu);
    uint8_t *dst = get_register(cpu, reg_dst);
    uint8_t *src = get_register(cpu, reg_src);

#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Moving data from register %c (0x%02X) to %c (0x%02X)", ii.instruction, 
              get_register_char(reg_src), *src, get_register_char(reg_dst), *dst);
#endif

    *dst = *src;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void mvi(intel8080 *cpu, uint8_t data) {
    registers_t *regs = &cpu->regs;
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));

#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Copying data 0x%02X", ii.instruction, data);
#endif

    *reg_ptr = data;
    regs->pc += INSTR_SIZE(cpu);
}

void sta(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Loading register A(0x%02X) into memory address 0x%04X", ii.instruction, cpu->regs.a, addr);
#endif
    cpu->mem.data[addr] = cpu->regs.a;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void lda(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Copying data from memory address 0x%04X(0x%02X) into the accumulator", ii.instruction, addr, cpu->regs.a);
#endif
    cpu->regs.a = cpu->mem.data[addr];
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void ldax(intel8080 *cpu) {
    uint16_t *reg_ptr = NULL;
    if(CUR_OP(cpu) == 0x02) {
        reg_ptr = &cpu->regs.bc;
    } else {
        reg_ptr = &cpu->regs.de;
    }

#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Loading accumulator with value from the memory address 0x%02X(0x%02X)", ii.instruction, *reg_ptr, cpu->mem.data[*reg_ptr]);
#endif

    cpu->regs.a = cpu->mem.data[*reg_ptr];
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void stax(intel8080 *cpu) {
    uint16_t *reg_ptr = NULL;
    if(CUR_OP(cpu) == 0x02) {
        reg_ptr = &cpu->regs.bc;
    } else {
        reg_ptr = &cpu->regs.de;
    }
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Storing register A(0x%02X) into address 0x%04X", ii.instruction, cpu->regs.a, *reg_ptr);
#endif

    cpu->mem.data[*reg_ptr] = cpu->regs.a;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void lhld(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Loading data at address 0x%04X(0x%02X) in register HL", ii.instruction, addr, cpu->mem.data[cpu->regs.hl]);
#endif
    cpu->regs.hl = cpu->mem.data[addr];
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void shld(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Copying HL(0x%04X) to address 0x%04X", ii.instruction, cpu->regs.hl, addr);
#endif
    cpu->mem.data[addr] = cpu->regs.hl;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void xchg(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Swapping registers HL(0x%04X) and DE(0x%04X), respectively", ii.instruction, cpu->regs.hl, cpu->regs.de);
#endif
    swap_u16(&cpu->regs.hl, &cpu->regs.de);
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void xthl(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Swapping registers HL(0x%04X) with SP+1(0x%02X) and SP(0x%02X)", ii.instruction, cpu->regs.hl, cpu->regs.sp+1, cpu->regs.sp);
#endif
    swap_u8(&cpu->regs.l, &cpu->mem.data[cpu->regs.sp]);
    swap_u8(&cpu->regs.h, &cpu->mem.data[cpu->regs.sp + 1]);
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void jmp(intel8080 *cpu, uint16_t data) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Jumping to address 0x%04X", ii.instruction, data);
#endif
    cpu->regs.pc = data;
}

void rnz(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Return if Not Zero; Result: %d", ii.instruction, !cpu->regs.f.zero);
#endif
    if(cpu->regs.f.zero == 0) ret(cpu);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void rnc(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Return if Not Carry; Result: %d", ii.instruction, !cpu->regs.f.carry);
#endif
    if(cpu->regs.f.carry == 0) ret(cpu);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void rpo(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Return if Parity Odd; Result: %d", ii.instruction, !cpu->regs.f.parity);
#endif
    if(cpu->regs.f.parity == 0) ret(cpu);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void rp(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Return if Sign Positive; Result: %d", ii.instruction, !cpu->regs.f.sign);
#endif
    if(cpu->regs.f.sign == 0) ret(cpu);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void jnz(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: JNZ to address 0x%04X; Result: %d", ii.instruction, addr, !cpu->regs.f.zero);
#endif
    if(!cpu->regs.f.zero) cpu->regs.pc = addr;
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void jnc(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: JNC to address 0x%04X; Result: %d", ii.instruction, addr, !cpu->regs.f.carry);
#endif
    if(!cpu->regs.f.carry) cpu->regs.pc = addr;
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void jpo(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: JPO to address 0x%04X; Result: %d", ii.instruction, addr, !cpu->regs.f.parity);
#endif
    if(!cpu->regs.f.parity) cpu->regs.pc = addr;
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void jp(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: JP to address 0x%04X; Result: %d", ii.instruction, addr, !cpu->regs.f.sign);
#endif
    if(!cpu->regs.f.sign) cpu->regs.pc = addr;
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void rst(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: RST %" PRIu8, ii.instruction, (CUR_OP(cpu) & 0x38) >> 3);
#endif
    call(cpu, CUR_OP(cpu) & 0x38);
}

void cnz(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Call 0x%04X if Not Zero; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.zero == 0);
#endif
    if(cpu->regs.f.zero == 0) call(cpu, addr);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void cnc(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Call 0x%04X if Not Carry; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.carry == 0);
#endif
    if(cpu->regs.f.carry == 0) call(cpu, addr);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void cpo(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Call 0x%04X if Parity Odd; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.parity == 0);
#endif
    if(cpu->regs.f.parity == 0) call(cpu, addr);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void cp(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Call 0x%04X if Sign Positive; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.sign == 0);
#endif
    if(cpu->regs.f.zero == 0) call(cpu, addr);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void rz(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Return if Zero; Result: %" PRIu8, ii.instruction, cpu->regs.f.zero);
#endif
    if(cpu->regs.f.zero == 1) ret(cpu);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void rc(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s Return if Carry; Result: %" PRIu8, ii.instruction, cpu->regs.f.carry);
#endif
    if(cpu->regs.f.carry == 1) ret(cpu);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void rpe(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Return if Parity Even; Result: %" PRIu8, ii.instruction, cpu->regs.f.parity);
#endif
    if(cpu->regs.f.parity == 1) ret(cpu);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void rm(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Return if Sign Minus; Result: %" PRIu8, ii.instruction, cpu->regs.f.sign);
#endif
    if(cpu->regs.f.sign == 1) ret(cpu);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void jz(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: JZ to address 0x%04X; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.zero);
#endif
    if(cpu->regs.f.zero) cpu->regs.pc = addr;
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void jc(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: JC to address 0x%04X; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.carry);
#endif
    if(cpu->regs.f.carry) cpu->regs.pc = addr;
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void jpe(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: JPE to address 0x%04X; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.parity);
#endif
    if(cpu->regs.f.parity) cpu->regs.pc = addr;
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void jm(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: JM to address 0x%04X; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.sign);
#endif
    if(cpu->regs.f.sign) cpu->regs.pc = addr;
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void cz(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Call 0x%04X if Zero; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.zero == 1);
#endif
    if(cpu->regs.f.zero == 1) call(cpu, addr);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void cc(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Call 0x%04X if Carry; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.carry == 1);
#endif
    if(cpu->regs.f.carry == 1) call(cpu, addr);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void cpe(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Call 0x%04X if Parity Even; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.parity == 1);
#endif
    if(cpu->regs.f.parity == 1) call(cpu, addr);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void cm(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Call 0x%04X if Sign Minus; Result: %" PRIu8, ii.instruction, addr, cpu->regs.f.sign == 1);
#endif
    if(cpu->regs.f.zero == 1) call(cpu, addr);
    else cpu->regs.pc += INSTR_SIZE(cpu);
}

void lxi(intel8080 *cpu, uint16_t data) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Copying data 0x%04X into register/SP", ii.instruction, data);
#endif
    uint8_t opcode = CUR_OP(cpu);
    switch(OP_DST_REG(cpu)) {
        case REG_B:
        case REG_C:
            cpu->regs.bc = data;
            break;
        case REG_E:
        case REG_D:
            cpu->regs.de = data;
            break;
        case REG_H:
        case REG_L:
            cpu->regs.hl = data;
            break;
        case REG_M:
        case REG_A:
            cpu->regs.sp = data;
            break;
        default:
            LOG_WARNING(cpu->regs.pc, "Unknown LIX Code: 0x%02X", opcode);
            break;
    }

    cpu->regs.pc += INSTR_SIZE(cpu);
}

void push_register(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    const uint8_t *instr = &cpu->mem.data[cpu->regs.pc];
    LOG_DEBUG(cpu->regs.pc, "%s: Pushing data: 0x%02X%02X at SP 0x%04X", ii.instruction, *(instr+1), *(instr+2), cpu->regs.sp);
#endif
    uint16_t *reg_ptr = NULL;
    switch(OP_DST_REG(cpu)){
        case REG_B:
        case REG_C:
            reg_ptr = &cpu->regs.bc;
            break;
        case REG_E:
        case REG_D:
            reg_ptr = &cpu->regs.de;
            break;
        case REG_L:
        case REG_H:
            reg_ptr = &cpu->regs.hl;
            break;
        case REG_M:
        case REG_A:
            reg_ptr = &cpu->regs.psw;
            break;
        default:
            fprintf(stderr, "ERROR Unknown POP instruction: %2X\n", CUR_OP(cpu));
            break;
    }

    //*reg_ptr = cpu->mem.data[cpu->regs.sp];
    *reg_ptr = ((cpu->mem.data[cpu->regs.sp-1] << 0) & 0xFF) |
               ((cpu->mem.data[cpu->regs.sp-2] << 8) & 0xFF00);
    cpu->regs.sp += 2;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void pop_register(intel8080 *cpu) {
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    uint16_t *reg_ptr = NULL;
    switch(OP_DST_REG(cpu)) {
        case REG_B:
        case REG_C:
            reg_ptr = &cpu->regs.bc;
            break;
        case REG_E:
        case REG_D:
            reg_ptr = &cpu->regs.de;
            break;
        case REG_L:
        case REG_H:
            reg_ptr = &cpu->regs.hl;
            break;
        case REG_M:
        case REG_A:
            reg_ptr = &cpu->regs.psw;
            break;
        default:
            fprintf(stderr, "ERROR Unknown POP instruction: %2X\n", CUR_OP(cpu));
            break;
    }

#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "%s: Popping data(0x%02X) at SP 0x%04X", ii.instruction, *reg_ptr, cpu->regs.sp);
#endif


    *reg_ptr = (cpu->mem.data[cpu->regs.sp-1] & 0x00FF) |
               ((cpu->mem.data[cpu->regs.sp-2] << 8) & 0xFF00);
    modify_flags(*reg_ptr, &cpu->regs, ii.flag_access);

    cpu->regs.sp -= 2;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void ret(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    uint16_t old_pc = cpu->regs.pc;
#endif
    cpu->regs.pc = ((cpu->mem.data[cpu->regs.sp-1] << 0) & 0xFF)|
                   ((cpu->mem.data[cpu->regs.sp-2] << 8) & 0xFF00);
    cpu->regs.sp -= 2;
#ifdef DEBUG
    LOG_DEBUG(old_pc, "%s: Returning to address at 0x%04X", ii.instruction, cpu->regs.pc);
#endif
}

void call(intel8080 *cpu, uint16_t data) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    const uint16_t old_pc = cpu->regs.pc;
    LOG_DEBUG(cpu->regs.pc, "%s: Calling method at address 0x%04X", ii.instruction, data);
#endif
    cpu->regs.pc += INSTR_SIZE(cpu);

    cpu->mem.data[cpu->regs.sp++] = (cpu->regs.pc >> 8) & 0xFF;
    cpu->mem.data[cpu->regs.sp++] = (cpu->regs.pc >> 0) & 0xFF;
#ifdef DEBUG
    LOG_DEBUG(old_pc, "%s: Pushing PC(0x%04X) at SP 0x%04X", ii.instruction, cpu->regs.pc, cpu->regs.sp);
#endif

    cpu->regs.pc = data;
}

void pchl(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Setting PC to contents of HL(0x%02X)", ii.instruction, cpu->regs.hl); 
#endif
    cpu->regs.pc = cpu->regs.hl;
}

void sphl(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Setting SP to contents of HL(0x%02X)", ii.instruction, cpu->regs.hl); 
#endif
    cpu->regs.sp = cpu->regs.hl;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void dad(intel8080 *cpu) {
    uint16_t *reg_ptr = NULL;
    switch(OP_DST_REG(cpu)){
        case REG_B:
        case REG_C:
            reg_ptr = &cpu->regs.bc;
            break;
        case REG_E:
        case REG_D:
            reg_ptr = &cpu->regs.de;
            break;
        case REG_H:
        case REG_L:
            reg_ptr = &cpu->regs.hl;
            break;
        case REG_M:
        case REG_A:
            reg_ptr = &cpu->regs.sp;
            break;
        default:
            fprintf(stderr, "ERROR Unknown DAD instruction: %2X\n", CUR_OP(cpu));
            break;
    };

#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Adding 0x%02X to the HL register; Result: 0x%02X", ii.instruction, *reg_ptr, cpu->regs.hl + *reg_ptr);
#endif

    uint16_t t = cpu->regs.hl + *reg_ptr;
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));

    cpu->regs.hl = t;

    cpu->regs.pc += INSTR_SIZE(cpu);
}

void inr(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Incrementing value 0x%02X", ii.instruction, reg_ptr ? *reg_ptr : 0);
#endif

    if(reg_ptr) {
        (*reg_ptr)++;
        modify_flags(*reg_ptr, &cpu->regs, FLAG_ACCESS(cpu));
    }

    cpu->regs.pc += INSTR_SIZE(cpu);
}

void add(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Adding 0x%02X to accumulator(0x%02X); Result: 0x%02X", ii.instruction, *reg_ptr, cpu->regs.a, cpu->regs.a + *reg_ptr);
#endif

    uint16_t t = cpu->regs.a + *reg_ptr;
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));

    cpu->regs.a = t;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void sub(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Subtracting 0x%02X to accumulator(0x%02X); Result: 0x%02X", ii.instruction, *reg_ptr, cpu->regs.a, cpu->regs.a - *reg_ptr);
#endif

    uint16_t t = cpu->regs.a - *reg_ptr;
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));

    cpu->regs.a = t;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void adc(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
    uint16_t t = cpu->regs.a + *reg_ptr + 1;
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Adding 0x%02X to accumulator(0x%02X) + carry(%" PRIu8"); Result: 0x%02X", ii.instruction, *reg_ptr, cpu->regs.a, cpu->regs.f.carry, t);
#endif

    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.a = t;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void sbb(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
    uint16_t t = cpu->regs.a - *reg_ptr - 1;
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Subtracting 0x%02X to accumulator(0x%02X) - carry(%" PRIu8"); Result: 0x%02X", ii.instruction, *reg_ptr, cpu->regs.a, cpu->regs.f.carry, t);
#endif

    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.a = t;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void adi(intel8080 *cpu, uint8_t data) {
    uint16_t t = cpu->regs.a + data;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Adding accumulator(0x%02X) and 0x%02X; Result: 0x%02X", ii.instruction, cpu->regs.a, data, t);
#endif
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.a = t;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void sui(intel8080 *cpu, uint8_t data) {
    uint16_t t = cpu->regs.a - data;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Subtracting accumulator(0x%02X) and 0x%02X; Result: 0x%02X", ii.instruction, cpu->regs.a, data, t);
#endif
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.a = t;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void aci(intel8080 *cpu, uint8_t data) {
    uint16_t t = cpu->regs.a + data + 1;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Adding carry(%" PRIu8"), accumulator(0x%02X) and 0x%02X; Result: 0x%02X", ii.instruction, cpu->regs.f.carry, cpu->regs.a, data, t);
#endif
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.a = t;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void sbi(intel8080 *cpu, uint8_t data) {
    uint16_t t = cpu->regs.a - data - 1;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Subtracting carry(%" PRIu8"), accumulator(0x%02X) and 0x%02X; Result: 0x%02X", ii.instruction, cpu->regs.f.carry, cpu->regs.a, data, t);
#endif
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.a = t;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void inx(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Incrementing values ", ii.instruction);

    switch(OP_DST_REG(cpu)) {
        case REG_B:
        case REG_C:
            LOG_DEBUG(cpu->regs.pc, "B: 0x%02X C: 0x%02X", cpu->regs.b , cpu->regs.c );
            break;
        case REG_E:
        case REG_D:
            LOG_DEBUG(cpu->regs.pc, "D: 0x%02X E: 0x%02X", cpu->regs.d , cpu->regs.e );
            break;
        case REG_H:
        case REG_L:
            LOG_DEBUG(cpu->regs.pc, "H: 0x%02X L: 0x%02X", cpu->regs.h , cpu->regs.l );
            break;
        case REG_M:
        case REG_A:
            LOG_DEBUG(cpu->regs.pc, "SP: 0x%02X", cpu->regs.sp );
            break;
    };
#endif
    switch(OP_DST_REG(cpu)){
        case REG_B:
        case REG_C:
            cpu->regs.b++;
            cpu->regs.c++;
            break;
        case REG_E:
        case REG_D:
            cpu->regs.d++;
            cpu->regs.e++;
            break;
        case REG_H:
        case REG_L:
            cpu->regs.h++;
            cpu->regs.l++;
            break;
        case REG_M:
        case REG_A:
            cpu->regs.sp++;
            break;
        default:
            fprintf(stderr, "ERROR Unknown INX instruction: %2X\n", CUR_OP(cpu));
            break;
    };

    cpu->regs.pc += INSTR_SIZE(cpu);
}

void dcx(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Decrementing values ", ii.instruction);

    switch(OP_DST_REG(cpu)) {
        case REG_B:
        case REG_C:
            LOG_DEBUG(cpu->regs.pc, "B: 0x%02X C: 0x%02X", cpu->regs.b , cpu->regs.c );
            break;
        case REG_E:
        case REG_D:
            LOG_DEBUG(cpu->regs.pc, "D: 0x%02X E: 0x%02X", cpu->regs.d , cpu->regs.e );
            break;
        case REG_H:
        case REG_L:
            LOG_DEBUG(cpu->regs.pc, "H: 0x%02X L: 0x%02X", cpu->regs.h , cpu->regs.l );
            break;
        case REG_M:
        case REG_A:
            LOG_DEBUG(cpu->regs.pc, "SP: 0x%02X", cpu->regs.sp );
            break;
    };
#endif
    switch(OP_DST_REG(cpu)){
        case REG_B:
        case REG_C:
            cpu->regs.b--;
            cpu->regs.c--;
            break;
        case REG_E:
        case REG_D:
            cpu->regs.d--;
            cpu->regs.e--;
            break;
        case REG_H:
        case REG_L:
            cpu->regs.h--;
            cpu->regs.l--;
            break;
        case REG_M:
        case REG_A:
            cpu->regs.sp--;
            break;
        default:
            fprintf(stderr, "ERROR Unknown DCX instruction: %2X\n", CUR_OP(cpu));
            break;
    };

    cpu->regs.pc += INSTR_SIZE(cpu);
}

void dcr(intel8080 *cpu) {
    registers_t *regs = &cpu->regs;
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));

#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Decrementing value 0x%02X", ii.instruction, reg_ptr ? *reg_ptr : 0);
#endif

    (*reg_ptr)--;
    modify_flags(*reg_ptr, regs, FLAG_ACCESS(cpu));
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void ana(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
    uint8_t x = cpu->regs.a & *reg_ptr;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Logical AND with Accumulator(0x%02X); Result: 0x%02X", ii.instruction, cpu->regs.a, x);
#endif
    cpu->regs.a = x;
    modify_flags(cpu->regs.a, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void ani(intel8080 *cpu, uint8_t data) {
    uint8_t x = cpu->regs.a & data;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Logical AND; Data(0x%02X) & Accumulator(0x%02X); Result: 0x%02X", ii.instruction, data, cpu->regs.a, x);
#endif
    cpu->regs.a = x;
    modify_flags(cpu->regs.a, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void ora(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
    uint8_t x = cpu->regs.a | *reg_ptr;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Logical OR with Accumulator(0x%02X); Result: 0x%02X", ii.instruction, cpu->regs.a, x);
#endif
    cpu->regs.a = x;
    modify_flags(cpu->regs.a, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void ori(intel8080 *cpu, uint8_t data) {
    uint8_t x = cpu->regs.a | data;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Logical OR; Data(0x%02X) | Accumulator(0x%02X); Result: 0x%02X", ii.instruction, data, cpu->regs.a, x);
#endif
    cpu->regs.a = x;
    modify_flags(cpu->regs.a, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void xra(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
    uint8_t x = cpu->regs.a ^ *reg_ptr;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Logical XOR with Accumulator(0x%02X); Result: 0x%02X", ii.instruction, cpu->regs.a, x);
#endif
    cpu->regs.a = x;
    modify_flags(cpu->regs.a, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void xri(intel8080 *cpu, uint8_t data) {
    uint8_t x = cpu->regs.a ^ data;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Logical XOR; Data(0x%02X) ^ Accumulator(0x%02X); Result: 0x%02X", ii.instruction, data, cpu->regs.a, x);
#endif
    cpu->regs.a = x;
    modify_flags(cpu->regs.a, &cpu->regs, FLAG_ACCESS(cpu));
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void cmp(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));

    uint16_t t = cpu->regs.a - *reg_ptr;
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Comparing Register(0x%02X) and Accumulator(0x%02X)", ii.instruction, *reg_ptr, cpu->regs.a);
    LOG_DEBUG(cpu->regs.pc, "%s: Result: 0x%02X", ii.instruction, t);
#endif

    cpu->regs.pc += INSTR_SIZE(cpu);
}

void cpi(intel8080 *cpu, uint8_t data) {
    uint16_t t = cpu->regs.a - data;
    modify_flags(t, &cpu->regs, FLAG_ACCESS(cpu));
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Comparing Data(0x%02X) and Accumulator(0x%02X)", ii.instruction, data, cpu->regs.a);
    LOG_DEBUG(cpu->regs.pc, "%s: Result: 0x%02X", ii.instruction, t);
#endif

    cpu->regs.pc += INSTR_SIZE(cpu);
}

void rlc(intel8080* cpu) {
    cpu->regs.f.carry = (cpu->regs.a >> 7);
    cpu->regs.a = (cpu->regs.a << 1) | cpu->regs.f.carry;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Rotating Accumulator Left", ii.instruction);
    LOG_DEBUG(cpu->regs.pc, "%s: Carry: %" PRIu8" Result: 0x%02X", ii.instruction, cpu->regs.f.carry, cpu->regs.a);
#endif
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void rrc(intel8080* cpu) {
    cpu->regs.f.carry = cpu->regs.a & 0x1;
    cpu->regs.a = (cpu->regs.a >> 1) | (cpu->regs.f.carry << 7);
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Rotating Accumulator Right", ii.instruction);
    LOG_DEBUG(cpu->regs.pc, "%s: Carry: %" PRIu8" Result: 0x%02X", ii.instruction, cpu->regs.f.carry, cpu->regs.a);
#endif
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void ral(intel8080* cpu) {
    uint8_t temp = cpu->regs.f.carry;
    cpu->regs.f.carry = cpu->regs.a >> 7;
    cpu->regs.a = (cpu->regs.a << 1) | temp;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Rotating Left Through Carry", ii.instruction);
    LOG_DEBUG(cpu->regs.pc, "%s: Carry: %" PRIu8" Result: 0x%02X", ii.instruction, cpu->regs.f.carry, cpu->regs.a);
#endif
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void rar(intel8080* cpu) {
    uint8_t temp = cpu->regs.f.carry;
    cpu->regs.f.carry = cpu->regs.a & 0x1;
    cpu->regs.a = (cpu->regs.a >> 1) | (temp << 7);
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Rotating Right Through Carry", ii.instruction);
    LOG_DEBUG(cpu->regs.pc, "%s: Carry: %" PRIu8" Result: 0x%02X", ii.instruction, cpu->regs.f.carry, cpu->regs.a);
#endif
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void daa(intel8080 *cpu) {
    if((cpu->regs.a & 0xF) > 9 || cpu->regs.f.aux_carry) {
        cpu->regs.a += 6;
        modify_flags(cpu->regs.a, &cpu->regs, FLAG_ACCESS(cpu));
    }

    if(((cpu->regs.a >> 4) & 0xF) > 9 || cpu->regs.f.carry) {
        cpu->regs.a += 6;
        modify_flags(cpu->regs.a, &cpu->regs, FLAG_ACCESS(cpu));
    }
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Adjusting accumulator: 0x%02X", ii.instruction, ~cpu->regs.a);
#endif
    cpu->regs.pc += INSTR_SIZE(cpu);
}
void cma(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Complementing accumulator: 0x%02X", ii.instruction, ~cpu->regs.a);
#endif
    cpu->regs.a = ~cpu->regs.a;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void cmc(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Complementing carry: 0x%02X", ii.instruction, ~cpu->regs.f.carry);
#endif
    cpu->regs.f.carry = ~cpu->regs.f.carry;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void stc(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Setting carry to 1", ii.instruction);
#endif
    cpu->regs.f.carry = 1;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void hlt(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Setting HALT to True", ii.instruction);
#endif
    cpu->is_halted = true;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void ei(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Enabling interrupts", ii.instruction);
#endif
    cpu->ei = true;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

void di(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Disabling interrupts", ii.instruction);
#endif
    cpu->ei = false;
    cpu->regs.pc += INSTR_SIZE(cpu);
}

static void generate_interrupt(intel8080 *cpu, uint8_t opcode) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR_CPU(cpu);
    LOG_DEBUG(cpu->regs.pc, "%s: Creating interrupt with opcode %" PRIu8, ii.instruction, opcode);
#endif
    cpu->interrupt_pending = true;
    cpu->interrupt_vector = opcode;
}