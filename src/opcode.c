#include "log.h"
#include "opcode.h"

const instr_info_t opcode_map[0xFF] = {
    [0x00] = {"NOP", 1, 4, MAKE_FLAG_NONE},
    [0x10] = {"NOP", 1, 4, MAKE_FLAG_NONE},
    [0x20] = {"NOP", 1, 4, MAKE_FLAG_NONE},
    [0x30] = {"NOP", 1, 4, MAKE_FLAG_NONE},

    [0xCB] = {"JMP a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jmp}},
    [0xC3] = {"JMP a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jmp}},

    [0xC2] = {"JNZ a16", 3, 10, MAKE_FLAG_NONE, { .f2 = jnz}},
    [0xD2] = {"JNC a16", 3, 10, MAKE_FLAG_NONE, { .f2 = jnc}},
    [0xE2] = {"JPO a16", 3, 10, MAKE_FLAG_NONE, { .f2 = jpo}},
    [0xF2] = {"JP a16", 3, 10, MAKE_FLAG_NONE, { .f2 = jp}},

    [0xCA] = {"JZ a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jz}},
    [0xDA] = {"JC a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jc}},
    [0xEA] = {"JPE a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jpe}},
    [0xFA] = {"JM a16", 3, 10, MAKE_FLAG_NONE, {.f2 = jm}},

    [0xC9] = {"RET", 1, 10, MAKE_FLAG_NONE, {.f0 = ret}},
    [0xD9] = {"RET", 1, 10, MAKE_FLAG_NONE, {.f0 = ret}},
    [0xCD] = {"CALL a16", 3, 17, MAKE_FLAG_NONE, {.f2 = call}},

    [0x02] = {"STAX B", 1, 7, MAKE_FLAG_NONE, {.f0 = stax}},
    [0X12] = {"STAX D", 1, 7, MAKE_FLAG_NONE, {.f0 = stax}},
    [0x32] = {"STA a16", 3, 13, MAKE_FLAG_NONE, {.f2 = sta}},

    [0x05] = {"DCR B", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x15] = {"DCR D", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x25] = {"DCR H", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x35] = {"DCR M", 1, 10, MAKE_FLAG_SZAP, {.f0 = dcr}},

    [0x0D] = {"DCR C", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x1D] = {"DCR E", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x2D] = {"DCR L", 1, 5, MAKE_FLAG_SZAP, {.f0 = dcr}},
    [0x3D] = {"DCR A", 1, 10, MAKE_FLAG_SZAP, {.f0 = dcr}},

    [0x03] = {"INX B", 1, 5, MAKE_FLAG_NONE, {.f0 = inx}},
    [0x13] = {"INX D", 1, 5, MAKE_FLAG_NONE, {.f0 = inx}},
    [0x23] = {"INX H", 1, 5, MAKE_FLAG_NONE, {.f0 = inx}},
    [0x33] = {"INX SP", 1, 5, MAKE_FLAG_NONE, {.f0 = inx}},

    // Move the 8-bit raw value into the register
    [0x06] = {"MVI B, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x16] = {"MVI D, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x26] = {"MVI H, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x36] = {"MVI M, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x0E] = {"MVI C, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x1E] = {"MVI E, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x2E] = {"MVI L, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},
    [0x3E] = {"MVI A, d8", 2, 7, MAKE_FLAG_NONE, {.f1 = mvi}},

    [0x22] = {"SHLD a16", 3, 16, MAKE_FLAG_NONE, {.f2 = shld}},
    [0x2A] = {"LHLD a16", 3, 16, MAKE_FLAG_NONE, {.f2 = lhld}},

    [0x09] = {"DAD B", 1, 10, MAKE_FLAG_CARRY},
    [0x19] = {"DAD C", 1, 10, MAKE_FLAG_CARRY},
    [0x29] = {"DAD H", 1, 10, MAKE_FLAG_CARRY},
    [0x39] = {"DAD SP", 1, 10, MAKE_FLAG_CARRY},

    [0xC1] = {"POP B", 1, 10, MAKE_FLAG_NONE, {.f0 = pop_register}},
    [0xD1] = {"POP D", 1, 10, MAKE_FLAG_NONE, {.f0 = pop_register}},
    [0xE1] = {"POP H", 1, 10, MAKE_FLAG_NONE, {.f0 = pop_register}},
    [0xF1] = {"POP PSW", 1, 10, MAKE_FLAG_ALL, {.f0 = pop_register}},

    [0xC5] = {"PUSH B", 1, 10, MAKE_FLAG_NONE, {.f0 = push_register}},
    [0xD5] = {"PUSH D", 1, 10, MAKE_FLAG_NONE, {.f0 = push_register}},
    [0xE5] = {"PUSH H", 1, 10, MAKE_FLAG_NONE, {.f0 = push_register}},
    [0xF5] = {"PUSH PSW", 1, 10, MAKE_FLAG_ALL, {.f0 = push_register}},

    // Load the 16-bit raw value into the register (BDH) or SP
    [0x01] = {"LXI B, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi}},
    [0x11] = {"LXI D, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi}},
    [0x21] = {"LXI H, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi}},
    [0x31] = {"LXI SP, d16", 3, 10, MAKE_FLAG_NONE, {.f2 = lxi}},

    // Loads register (BD) into the accumulator
    [0x0A] = {"LDAX B", 1, 7, MAKE_FLAG_NONE, {.f1 = ldax}},
    [0x1A] = {"LDAX D", 1, 7, MAKE_FLAG_NONE, {.f1 = ldax}},
    [0x3A] = {"LDA a16", 3, 13, MAKE_FLAG_NONE, {.f2 = lda}},

    [0x80] = {"ADD B", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x81] = {"ADD C", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x82] = {"ADD D", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x83] = {"ADD E", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x84] = {"ADD H", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x85] = {"ADD L", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x86] = {"ADD M", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},
    [0x87] = {"ADD A", 1, 4, MAKE_FLAG_ALL, {.f0 = add}},

    [0x40] = {"MOV B, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x41] = {"MOV B, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x42] = {"MOV B, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x43] = {"MOV B, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x44] = {"MOV B, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x45] = {"MOV B, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x46] = {"MOV B, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x47] = {"MOV B, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x48] = {"MOV C, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x49] = {"MOV C, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4A] = {"MOV C, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4B] = {"MOV C, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4C] = {"MOV C, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4D] = {"MOV C, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4E] = {"MOV C, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x4F] = {"MOV C, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x50] = {"MOV D, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x51] = {"MOV D, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x52] = {"MOV D, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x53] = {"MOV D, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x54] = {"MOV D, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x55] = {"MOV D, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x56] = {"MOV D, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x57] = {"MOV D, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x58] = {"MOV E, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x59] = {"MOV E, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5A] = {"MOV E, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5B] = {"MOV E, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5C] = {"MOV E, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5D] = {"MOV E, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5E] = {"MOV E, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x5F] = {"MOV E, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x60] = {"MOV H, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x61] = {"MOV H, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x62] = {"MOV H, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x63] = {"MOV H, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x64] = {"MOV H, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x65] = {"MOV H, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x66] = {"MOV H, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x67] = {"MOV H, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x68] = {"MOV L, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x69] = {"MOV L, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6A] = {"MOV L, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6B] = {"MOV L, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6C] = {"MOV L, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6D] = {"MOV L, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6E] = {"MOV L, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x6F] = {"MOV L, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x70] = {"MOV M, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x71] = {"MOV M, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x72] = {"MOV M, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x73] = {"MOV M, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x74] = {"MOV M, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x75] = {"MOV M, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x76] = {"HLT", 1, 7, MAKE_FLAG_NONE},
    [0x77] = {"MOV M, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},

    [0x78] = {"MOV A, B", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x79] = {"MOV A, C", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7A] = {"MOV A, D", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7B] = {"MOV A, E", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7C] = {"MOV A, H", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7D] = {"MOV A, L", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7E] = {"MOV A, M", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
    [0x7F] = {"MOV A, A", 1, 5, MAKE_FLAG_NONE, {.f0 = mov}},
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
#define GET_INSTR_SIZE(cpu) (GET_INSTR(CUR_OP(cpu)).op_bytes)

#define GET_INSTR_FLAGS_ACC(x) (GET_INSTR(x).flag_access)

#define OP_DST_REG(cpu)  ((CUR_OP(cpu) & 0x38) >> 3)
#define OP_SRC_REG(cpu)  (CUR_OP(cpu) & 0x7)

#define HAS_ACCESS(flag_access, x) (flag_access & (1 << x))
#define SET_FLAG(flags, x) (flags &= (1 << x))

#define mem_write_16(addr, a, b) \

typedef enum {
    CARRY = 0,
    PARITY = 2,
    AUX_CARRY = 4,
    ZERO = 6,
    SIGN = 7,
    NONE,
} FLAGS;

static void modify_flags_szap(uint16_t value, registers_t *regs, const uint8_t flag_access) {
    if(HAS_ACCESS(flag_access, SIGN)) {
        regs->f.sign = (value & (1 << SIGN));
    }

    if(HAS_ACCESS(flag_access, ZERO)) {
        regs->f.zero = (value == 0);
    }

    // 0 == Even Parity
    // 1 == Odd Parity
    if(HAS_ACCESS(flag_access, PARITY)) {
        regs->f.parity ^= (value >> 4);
        regs->f.parity ^= (regs->f.parity >> 2);
        regs->f.parity ^= (regs->f.parity>> 1);
    }

    if(HAS_ACCESS(flag_access, AUX_CARRY)) {
        regs->f.aux_carry = (value & 0x10);
    }

    // Check for carry
    if(HAS_ACCESS(flag_access, CARRY)) {
        cpu->regs.f.carry = (t & 0xFF00) ? 1 : 0;
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

void mov(intel8080 *cpu) {
    registers reg_src = OP_DST_REG(cpu);
    registers reg_dst = OP_SRC_REG(cpu);
    uint8_t *dst = get_register(cpu, reg_dst);
    uint8_t *src = get_register(cpu, reg_src);

#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.sp, "%s: Moving data from register %c (0x%02X) to %c (0x%02X)", ii.instruction, 
              get_register_char(reg_dst), *dst, get_register_char(reg_src), *src);
#endif

    *src = *dst;
    cpu->regs.pc += 1;
}

void jmp(intel8080 *cpu, uint16_t data) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.sp, "%s: Jumping to address 0x%04X", ii.instruction, data);
#endif
    cpu->regs.pc = data;
}

void jz(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "JZ to address 0x%04X; Result: %d", addr, cpu->regs.f.zero);
#endif
    if(cpu->regs.f.zero) cpu->regs.pc = addr;
    else cpu->regs.pc += 1;
}

void jc(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "JC to address 0x%04X; Result: %d", addr, cpu->regs.f.carry);
#endif
    if(cpu->regs.f.carry) cpu->regs.pc = addr;
    else cpu->regs.pc += 1;
}

void jpe(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "JPE to address 0x%04X; Result: %d", addr, cpu->regs.f.parity);
#endif
    if(cpu->regs.f.parity) cpu->regs.pc = addr;
    else cpu->regs.pc += 1;
}

void jm(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "JM to address 0x%04X; Result: %d", addr, cpu->regs.f.sign);
#endif
    if(cpu->regs.f.sign) cpu->regs.pc = addr;
    else cpu->regs.pc += 1;
}

void jnz(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "JNZ to address 0x%04X; Result: %d", addr, !cpu->regs.f.zero);
#endif
    if(!cpu->regs.f.zero) cpu->regs.pc = addr;
    else cpu->regs.pc += 1;
}

void jnc(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "JNC to address 0x%04X; Result: %d", addr, !cpu->regs.f.carry);
#endif
    if(!cpu->regs.f.carry) cpu->regs.pc = addr;
    else cpu->regs.pc += 1;
}

void jpo(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "JPO to address 0x%04X; Result: %d", addr, !cpu->regs.f.parity);
#endif
    if(!cpu->regs.f.parity) cpu->regs.pc = addr;
    else cpu->regs.pc += 1;
}

void jp(intel8080 *cpu, uint16_t addr) {
#ifdef DEBUG
    LOG_DEBUG(cpu->regs.pc, "JP to address 0x%04X; Result: %d", addr, !cpu->regs.f.sign);
#endif
    if(!cpu->regs.f.sign) cpu->regs.pc = addr;
    else cpu->regs.pc += 1;
}

void lxi(intel8080 *cpu, uint16_t data) {
    uint8_t opcode = CUR_OP(cpu);
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
            LOG_WARNING(cpu->regs.pc, "Unknown LIX Code: 0x%02X", opcode);
            break;
    }

#ifdef DEBUG
    instr_info_t ii = GET_INSTR(opcode);
    LOG_DEBUG(cpu->regs.pc, "%s: Copying data 0x%04X into register/SP", ii.instruction, data);
#endif

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void mvi(intel8080 *cpu, uint8_t data) {
    uint8_t opcode = CUR_OP(cpu);
    registers_t *regs = &cpu->regs;
    uint8_t *reg_ptr = get_register(cpu, (opcode & 0x38) >> 3);

#ifdef DEBUG
    instr_info_t ii = GET_INSTR(opcode);
    LOG_DEBUG(cpu->regs.pc, "%s: Copying data 0x%02X", ii.instruction, data);
#endif

    *reg_ptr = data;
    regs->pc += GET_INSTR_SIZE(cpu);
}

static void push_stack(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Pushing PC(0x%04X) at SP 0x%04X", ii.instruction, cpu->regs.pc, cpu->regs.sp);
#endif
    cpu->regs.sp += 2;

    cpu->mem.data[cpu->regs.sp] = cpu->regs.pc;
}

void push_register(intel8080 *cpu) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    const uint8_t *instr = &cpu->mem.data[cpu->regs.pc];
    LOG_DEBUG(cpu->regs.pc, "%s: Pushing data: 0x%02X%02X at SP 0x%04X", ii.instruction, *(instr+1), *(instr+2), cpu->regs.sp);
#endif

    // Automatically incrememted as per the manual
    cpu->regs.sp += 2;

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

    if(reg_ptr != NULL)
        *reg_ptr = cpu->mem.data[cpu->regs.sp];
}

static void pop_stack(intel8080 *cpu) {
    cpu->regs.pc = cpu->mem.data[cpu->regs.sp];
    cpu->regs.sp -= 2;
}

void pop_register(intel8080 *cpu) {
    const instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    uint16_t *reg_ptr = NULL;
    uint8_t first_nibble = (CUR_OP(cpu) & 0x38) >> 3;
    switch(first_nibble) {
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

    if(reg_ptr != NULL) {
        *reg_ptr = cpu->mem.data[cpu->regs.sp];
        if(first_nibble == REG_M || first_nibble == REG_A)
            modify_flags_szap(*reg_ptr, &cpu->regs, ii.flag_access);
    }

    cpu->regs.sp -= 2;
}

void ret(intel8080 *cpu) {
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Returning to address at 0x%04X", ii.instruction, cpu->mem.data[cpu->regs.sp]);
#endif

    pop_stack(cpu);
}

void call(intel8080 *cpu, uint16_t data) {
#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    //LOG_DEBUG(cpu->regs.pc, "%s: Pushing current PC at SP (0x%04X)", ii.instruction, cpu->regs.sp);
    LOG_DEBUG(cpu->regs.pc, "%s: Calling method at address 0x%04X", ii.instruction, data);
#endif
    push_stack(cpu);
    cpu->regs.pc = data;
}

void stax(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, OP_DST_REG(cpu));
    *reg_ptr = cpu->regs.a;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Loading register A(0x%02X) into register %c", ii.instruction, cpu->regs.a, get_register_char(OP_DST_REG(cpu)));
#endif

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void sta(intel8080 *cpu, uint16_t addr) {
    cpu->mem.data[addr] = cpu->regs.a;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Loading register A(0x%02X) into memory address 0x%04X", ii.instruction, cpu->regs.a, addr);
#endif
    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void ldax(intel8080 *cpu, uint8_t data) {
    uint8_t opcode = CUR_OP(cpu);
    uint8_t *reg_ptr = get_register(cpu, (opcode &0x38) >> 3);
    *reg_ptr = data;

#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Loading from register(0x%02X) to accumulator", ii.instruction, data);
#endif

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void lda(intel8080 *cpu, uint16_t addr) {
    cpu->regs.a = cpu->mem.data[addr];
#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Copying 0x%02X into the accumulator", ii.instruction, cpu->regs.a);
#endif
    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void lhld(intel8080 *cpu, uint16_t addr) {
    cpu->regs.hl = cpu->mem.data[addr];
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Loading data at address 0x%04X(0x%02X) in register HL", ii.instruction, addr, cpu->mem.data[cpu->regs.hl]);
#endif

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void shld(intel8080 *cpu, uint16_t addr) {
    cpu->mem.data[addr] = cpu->regs.hl;
#ifdef DEBUG
    const instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Copying HL(0x%04X) to address 0x%04X", ii.instruction, cpu->regs.hl, addr);
#endif

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
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
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Adding 0x%02X to the HL register; Result: 0x%02X", ii.instruction, *reg_ptr, cpu->regs.hl + *reg_ptr);
#endif

    uint16_t t = cpu->regs.hl + *reg_ptr;
    if(t < cpu->regs.hl || t < *reg_ptr) {
        cpu->regs.f.carry = 1;
    } else {
        cpu->regs.f.carry = 0;
    }

    cpu->regs.hl = t;

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void inr(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, (CUR_OP(cpu) & 0x38) >> 3 );

    if(reg_ptr) {
        (*reg_ptr)++;
        modify_flags_szap(*reg_ptr, &cpu->regs, GET_INSTR_FLAGS_ACC(CUR_OP(cpu)));
    }

#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Incrementing value 0x%02X", ii.instruction, reg_ptr ? *reg_ptr : 0);
#endif

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void add(intel8080 *cpu) {
    uint8_t *reg_ptr = get_register(cpu, CUR_OP(cpu));
#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Adding 0x%02X to accumulator(0x%02X); Result: 0x%02X", ii.instruction, *reg_ptr, cpu->regs.a, cpu->regs.a + *reg_ptr);
#endif

    uint16_t t = cpu->regs.a + *reg_ptr;
    modify_flags_szap(t, cpu->regs, 

    cpu->regs.a = t;
    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void inx(intel8080 *cpu) {
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

#ifdef DEBUG
    instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    LOG_DEBUG(cpu->regs.pc, "%s: Incrementing values ", ii.instruction);

    switch(OP_DST_REG(cpu)) {
        case REG_B:
        case REG_C:
            LOG_DEBUG(cpu->regs.pc, "B: 0x%02X C: 0x%02X", cpu->regs.b - 1, cpu->regs.c - 1);
            break;
        case REG_E:
        case REG_D:
            LOG_DEBUG(cpu->regs.pc, "D: 0x%02X E: 0x%02X", cpu->regs.d - 1, cpu->regs.e - 1);
            break;
        case REG_H:
        case REG_L:
            LOG_DEBUG(cpu->regs.pc, "H: 0x%02X L: 0x%02X", cpu->regs.h - 1, cpu->regs.l - 1);
            break;
        case REG_M:
        case REG_A:
            LOG_DEBUG(cpu->regs.pc, "SP: 0x%02X", cpu->regs.sp - 1);
            break;
    };
#endif

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}

void dcr(intel8080 *cpu) {
    const instr_info_t ii = GET_INSTR(CUR_OP(cpu));
    registers_t *regs = &cpu->regs;
    uint8_t *reg_ptr = get_register(cpu, (CUR_OP(cpu) & 0x38) >> 3 );

    if(reg_ptr) {
        (*reg_ptr)--;
        modify_flags_szap(*reg_ptr, regs, ii.flag_access);
    }

#ifdef DEBUG
    LOG_DEBUG(regs->pc, "%s: Decrementing values ", ii.instruction);

    switch(OP_DST_REG(cpu)) {
        case REG_B:
        case REG_C:
            LOG_DEBUG(regs->pc, "B: 0x%02X C: 0x%02X", regs->b + 1, regs->c + 1);
            break;
        case REG_E:
        case REG_D:
            LOG_DEBUG(regs->pc, "D: 0x%02X E: 0x%02X", regs->d + 1, regs->e + 1);
            break;
        case REG_H:
        case REG_L:
            LOG_DEBUG(regs->pc, "H: 0x%02X L: 0x%02X", regs->h + 1, regs->l + 1);
            break;
        case REG_M:
        case REG_A:
            LOG_DEBUG(regs->pc, "SP: 0x%02X", regs->sp + 1);
            break;
        default:
            fprintf(stderr, "ERROR Unknown DCR instruction: %2X\n", CUR_OP(cpu));
            break;
    };
#endif

    cpu->regs.pc += GET_INSTR_SIZE(cpu);
}
