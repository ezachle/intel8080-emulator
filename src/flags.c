#include "flags.h"

instr_info_t opcode_map[0xFF] = {
    [0x00] = {"NOP", 1, 4, MAKE_FLAG_NONE},
    [0x10] = {"NOP", 1, 4, MAKE_FLAG_NONE},
    [0x20] = {"NOP", 1, 4, MAKE_FLAG_NONE},
    [0x30] = {"NOP", 1, 4, MAKE_FLAG_NONE},

    [0xCB] = {"JMP a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jmp_a16}},
    [0xC3] = {"JMP a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jmp_a16}},

    //[0xC9] = {"RET", 1, 10, MAKE_FLAG_NONE, {.f0 = ret}},
    [0xCD] = {"CALL a16", 3, 17, MAKE_FLAG_NONE, {.f2 = call_a16}},

    //[0x02] = {"STAX B", 1, 7, MAKE_FLAG_NONE},
    //[0x03] = {"INX B", 1, 5, MAKE_FLAG_NONE, {.f1 = inx_16bit}},
    //[0x04] = {"INR B", 1, 5, MAKE_FLAG_SZAP, {.f1 = inr_8bit}},
    //[0x05] = {"DCR B", 1, 5, MAKE_FLAG_SZAP, {.f1 = dcr_8bit}},

    // Move the 8-bit raw value into the register
    [0x06] = {"MVI B, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi_8bit}},
    [0x16] = {"MVI D, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi_8bit}},
    [0x26] = {"MVI H, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi_8bit}},
    [0x36] = {"MVI M, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi_8bit}},
    [0x0E] = {"MVI C, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi_8bit}},
    [0x1E] = {"MVI E, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi_8bit}},
    [0x2E] = {"MVI L, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi_8bit}},
    [0x3E] = {"MVI A, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi_8bit}},

    [0xC1] = {"POP B", 1, 10, MAKE_FLAG_NONE, {.f0 = pop}},
    [0xD1] = {"POP D", 1, 10, MAKE_FLAG_NONE, {.f0 = pop}},
    [0xE1] = {"POP H", 1, 10, MAKE_FLAG_NONE, {.f0 = pop}},
    [0xF1] = {"POP PSW", 1, 10, MAKE_FLAG_NONE, {.f0 = pop}},

    [0xC5] = {"PUSH B", 1, 10, MAKE_FLAG_NONE, {.f0 = push}},
    [0xD5] = {"PUSH D", 1, 10, MAKE_FLAG_NONE, {.f0 = push}},
    [0xE5] = {"PUSH H", 1, 10, MAKE_FLAG_NONE, {.f0 = push}},
    [0xF5] = {"PUSH PSW", 1, 10, MAKE_FLAG_NONE, {.f0 = push}},

    // Load the 16-bit raw value into the register (BDH) or SP
    [0x01] = {"LXI B, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi_16bit}},
    [0x11] = {"LXI D, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi_16bit}},
    [0x21] = {"LXI H, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi_16bit}},
    [0x31] = {"LXI SP, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi_16bit}},

    // Loads register (BD) into the accumulator
    [0x0A] = {"LDAX B", 1, 7, MAKE_FLAG_NONE, {.f1 = ldax_8bit}},
    [0x1A] = {"LDAX D", 1, 7, MAKE_FLAG_NONE, {.f1 = ldax_8bit}},
    [0x3A] = {"LDA a16", 3, 13, MAKE_FLAG_NONE, {.f2 = lda_16bit}},

    [0x40] = {"MOV B, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x41] = {"MOV B, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x42] = {"MOV B, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x43] = {"MOV B, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x44] = {"MOV B, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x45] = {"MOV B, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x46] = {"MOV B, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x47] = {"MOV B, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},

    [0x48] = {"MOV C, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x49] = {"MOV C, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x4A] = {"MOV C, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x4B] = {"MOV C, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x4C] = {"MOV C, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x4D] = {"MOV C, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x4E] = {"MOV C, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x4F] = {"MOV C, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},

    [0x50] = {"MOV D, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x51] = {"MOV D, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x52] = {"MOV D, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x53] = {"MOV D, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x54] = {"MOV D, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x55] = {"MOV D, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x56] = {"MOV D, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x57] = {"MOV D, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},

    [0x58] = {"MOV E, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x59] = {"MOV E, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x5A] = {"MOV E, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x5B] = {"MOV E, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x5C] = {"MOV E, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x5D] = {"MOV E, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x5E] = {"MOV E, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x5F] = {"MOV E, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},

    [0x60] = {"MOV H, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x61] = {"MOV H, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x62] = {"MOV H, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x63] = {"MOV H, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x64] = {"MOV H, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x65] = {"MOV H, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x66] = {"MOV H, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x67] = {"MOV H, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},

    [0x68] = {"MOV L, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x69] = {"MOV L, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x6A] = {"MOV L, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x6B] = {"MOV L, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x6C] = {"MOV L, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x6D] = {"MOV L, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x6E] = {"MOV L, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x6F] = {"MOV L, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},

    [0x70] = {"MOV M, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x71] = {"MOV M, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x72] = {"MOV M, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x73] = {"MOV M, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x74] = {"MOV M, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x75] = {"MOV M, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x76] = {"HLT", 1, 7, MAKE_FLAG_NONE},
    [0x77] = {"MOV M, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},

    [0x78] = {"MOV E, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x79] = {"MOV E, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x7A] = {"MOV E, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x7B] = {"MOV E, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x7C] = {"MOV E, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x7D] = {"MOV E, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x7E] = {"MOV E, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
    [0x7F] = {"MOV E, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov_8bit}},
};

typedef enum {
    REG_B = 0,
    REG_C = 1,
    REG_D = 2,
    REG_E = 3,
    REG_H = 4,
    REG_L = 5,
    REG_A = 6,
    REG_M = 7,
} registers;

uint16_t get_dst_reg_val(const intel8080 *cpu, uint8_t opcode) {
    registers_t regs = cpu->regs;
    uint8_t byte = (opcode & 0xF) % 8;
    switch(byte) {
        case 0:
            return regs.b;
        case 1:
            return regs.c;
        case 2:
            return regs.d;
        case 3:
            return regs.e;
        case 4:
            return regs.h;
        case 5:
            return regs.l;
        case 6:
            return regs.a;
        case 7:
            return regs.hl;
        default:
            printf("ERROR: Unknown Register: %02X\n", byte);
            return 255;
    };
}

uint16_t* get_src_reg(const intel8080 *cpu, uint8_t opcode) {
    registers_t regs = cpu->regs;
    uint8_t byte1 = (opcode >> 4) & 0xF;
    uint8_t byte2 = opcode & 0xF;
    
    switch(byte1) {
        case 4:
            return (byte2 <= 0x7) ? (uint16_t*)&regs.b : (uint16_t*)&regs.c;
        case 5:
            return (byte2 <= 0x7) ? (uint16_t*)&regs.d : (uint16_t*)&regs.e;
        case 6:
            return (byte2 <= 0x7) ? (uint16_t*)&regs.h : (uint16_t*)&regs.l;
        case 7:
            return (byte2 <= 0x7) ? &regs.hl: (uint16_t*)&regs.a;
        default:
            printf("ERROR: Unknown Registers: %02X %02X\n", byte1, byte2);
            return NULL;
    };
}

#define GET_OPCODE (cpu->mem.data[cpu->regs.pc])
#define GET_INSTR(x) (opcode_map[x])
#define GET_INSTR_SIZE (GET_INSTR.op_bytes)

void mov_8bit(intel8080 *cpu) {
    uint8_t opcode = GET_OPCODE;
    uint16_t dst = get_dst_reg_val(cpu, opcode);
    uint16_t *reg_val = get_src_reg(cpu, opcode);
    *reg_val = dst;

    cpu->regs.pc += 1;
}

void jmp_a16(intel8080 *cpu, uint16_t data) {
    cpu->regs.pc = data;
}

void lxi_16bit(intel8080 *cpu, uint16_t data) {
    uint8_t opcode = GET_OPCODE;
    instr_info_t ii = GET_INSTR(opcode);
    switch(opcode >> 4) {
        case 0x0:
            cpu->regs.bc = data;
            break;
        case 0x1:
            cpu->regs.de = data;
            break;
        case 0x2:
            cpu->regs.hl = data;
            break;
        case 0x3:
            cpu->regs.sp = data;
            break;
        default:
            fprintf(stderr, "ERROR Unknown LXI Code: %2X\n", opcode);
            break;
    }

    cpu->regs.pc += ii.op_bytes;
}

void mvi_8bit(intel8080 *cpu, uint8_t data) {
    uint8_t opcode = GET_OPCODE;
    uint8_t first_nibble = (opcode >> 4) & 0xF;
    uint8_t second_nibble = opcode & 0xF;
    switch(first_nibble) {
        case 0x0:
            if(second_nibble == 0x6) cpu->regs.b = data;
            else cpu->regs.c = data;
            break;
        case 0x1:
            if(second_nibble == 0x6) cpu->regs.d = data;
            else cpu->regs.e = data;
            break;
        case 0x2:
            if(second_nibble == 0x6) cpu->regs.h = data;
            else cpu->regs.l = data;
            break;
        case 0x3:
            if(second_nibble == 0x6) cpu->regs.hl = data;
            else cpu->regs.a = data;
            break;
        default:
            fprintf(stderr, "ERROR Unknown MVI instruction %2X\n", opcode);
            break;
    }

    cpu->regs.pc += GET_INSTR(opcode).op_bytes;
}

void push(intel8080 *cpu) {
    cpu->regs.sp -= 2;
    uint8_t reg = (GET_OPCODE >> 4) & 0xF;
    uint16_t data = 0;
    switch(reg) {
        case 0xC:
            data = cpu->regs.bc;
            break;
        case 0xD:
            data = cpu->regs.de;
            break;
        case 0xE:
            data = cpu->regs.hl;
            break;
        case 0xF:
            data = cpu->regs.psw;
            break;
        default:
            fprintf(stderr, "ERROR Unknown PUSH instruction: %2X\n", GET_OPCODE);
            break;
    }
    cpu->mem.data[cpu->regs.sp] = data;
}

void pop(intel8080 *cpu) {
    uint8_t reg = (GET_OPCODE >> 4) & 0xF;
    uint16_t *reg_ptr = NULL;
    switch(reg) {
        case 0xC:
            reg_ptr = &cpu->regs.bc;
            break;
        case 0xD:
            reg_ptr = &cpu->regs.de;
            break;
        case 0xE:
            reg_ptr = &cpu->regs.hl;
            break;
        case 0xF:
            // TODO FIX PSW
            reg_ptr = &cpu->regs.psw;
            break;
        default:
            fprintf(stderr, "ERROR Unknown PUSH instruction: %2X\n", GET_OPCODE);
            break;
    }

    if(reg_ptr != NULL)
        *reg_ptr = cpu->mem.data[cpu->regs.sp];

    cpu->regs.sp += 2;
}

void call_a16(intel8080 *cpu, uint16_t data) {
    push(cpu);
    cpu->regs.pc = data;
}

void ldax_8bit(intel8080 *cpu, uint8_t data) {
    uint8_t opcode = GET_OPCODE;
    uint8_t first_nibble = (opcode >> 4) & 0xF;

    if(first_nibble == 0x0) {
        cpu->regs.b = data;
    } else if(first_nibble == 0x1) {
        cpu->regs.d = data;
    } else {
        fprintf(stderr, "ERROR Unknown LDAX Instruction: %02X\n", opcode);
    }

    cpu->regs.pc += GET_INSTR(opcode).op_bytes;
}

void lda_16bit(intel8080 *cpu, uint16_t addr) {
    cpu->regs.a = cpu->mem.data[addr];
    cpu->regs.pc += GET_INSTR(GET_OPCODE).op_bytes;
}
