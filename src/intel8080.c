#include "log.h"
#include "intel8080.h"
#include "opcode.h"

void reset_memory(registers_t *regs, memory_t *mem, const uint16_t start_pc) {
    regs->pc = start_pc;
    regs->sp = 0x0;

    memset(mem->data, 0, MAX_MEM);
#ifdef CPM

    // inject "out 0,a" at 0x0000 (signal to stop the test)
    mem->data[0x0000] = 0xD3;
    mem->data[0x0001] = 0x00;
  
    // inject "out 1,a" at 0x0005 (signal to output some characters)
    mem->data[0x0005] = 0xD3;
    mem->data[0x0006] = 0x01;
    mem->data[0x0007] = 0xC9;
  
#endif
}

static bool load_rom(intel8080 *cpu, char *rom_name) {
    strncpy(cpu->rom_name, rom_name, strlen(rom_name));

    FILE *fp = fopen(rom_name, "rb");
    if(!fp) {
        LOG_ERROR(cpu->regs.pc, "Unable to open file %s\n", rom_name);
        return false;
    }

    fseek(fp, 0, SEEK_END);
    cpu->rom_size = ftell(fp);
    if(cpu->rom_size > 0xFFFF) {
        LOG_ERROR(cpu->regs.pc, "ROM file is greater than 8192 bytes, file: %"PRIu64, cpu->rom_size);
        fclose(fp);
        return false;
    }
    rewind(fp);

    uint8_t *mem_ptr = &cpu->mem.data[cpu->regs.pc];
    if(!fread(mem_ptr, cpu->rom_size, 1, fp)) {
        LOG_ERROR(cpu->regs.pc, "Failed to read memory from ROM");
        fclose(fp);
        return false;
    }

    fclose(fp);
    LOG(cpu->regs.pc, "Loaded ROM %s", rom_name);
    return true;
}

bool init_8080(intel8080 *cpu, char *rom_name, const uint16_t start_pc, void *userdata) {
    reset_memory(&cpu->regs, &cpu->mem, start_pc);

    cpu->regs.f.unused1 = 1;
    cpu->regs.f.unused2 = 0;
    cpu->regs.f.unused3 = 0;

    cpu->regs.sp = 0;

    cpu->cycles = 0;
    cpu->is_halted = false;
    cpu->ei = false;
    cpu->interrupt_vector = 0;
    
    if(!load_rom(cpu, rom_name)) {
        LOG_ERROR(cpu->regs.pc, "Failed to load ROM: %s", rom_name);
        return false;
    }

    cpu->quit = false;

    cpu->userdata = userdata;

    return true;
}

void destroy_8080(intel8080 *cpu) {
    reset_memory(&cpu->regs, &cpu->mem, 0);
    cpu->rom = NULL;
}

#ifdef CPM
static bool run_test(intel8080 *cpu, char* rom_name) {
    if(!load_rom(cpu, rom_name)) {
        LOG_ERROR(cpu->regs.pc, "Failed to load ROM: %s", rom_name);
        return false;
    }

    bool rc = init_8080(cpu, rom_name, 0x0100, NULL);

    while(!cpu->quit && cpu->regs.pc < 0xFFFF)
        emulate_8080(cpu);

    return true;
}

static bool handle_cpm(intel8080 *cpu) {
    if(cpu->regs.pc == 0x0005) {
        switch(cpu->regs.c) {
            case 2:
                printf("%c", cpu->regs.e);
                fflush(stdout);
                break;
            case 9:
                uint16_t str_addr = cpu->regs.de;
                while(cpu->mem.data[str_addr] != '$') {
                    printf("%c", cpu->mem.data[str_addr++]);
                }
                printf("\n");
                fflush(stdout);
                break;
            default:
                LOG_WARNING(cpu->regs.pc, "Unimplemneted CP/M Instruciton %" PRIu8, cpu->regs.c);
                break;
        }
        ret(cpu);
        cpu->cycles += 20;
        return true;
    } else if(cpu->regs.pc == 0x0000) {
        cpu->quit = true;
    }

    return false;
}
#endif

bool run_cpm_tests(intel8080 *cpu) {
#ifdef CPM
    bool rc = run_test(cpu, "cpu_tests/TST8080.COM");
    if(!rc) return false;

    rc = run_test(cpu, "cpu_tests/CPUTEST.COM");
    if(!rc) return false;

    rc = run_test(cpu, "cpu_tests/8080PRE.COM");
    if(!rc) return false;

    rc = run_test(cpu, "cpu_tests/8080EXM.COM");
    if(!rc) return false;
#endif
    return true;
}


void emulate_8080(intel8080 *cpu) {
    memory_t *memory = &cpu->mem;
    //PRINT_STATE(cpu);
    //PRINT_FLAGS(cpu);

#ifdef CPM
    if(handle_cpm(cpu) || cpu->quit) return;
#ifdef VERBOSE
    fprintf(stderr, "PC: %04X AF: %04X BC: %04X DE: %04X HL: %04X SP: %04X, CYC: %" PRIu64"\t (%02X %02X %02X %02X)\n",
            *pc,
            cpu->regs.psw,
            cpu->regs.bc,
            cpu->regs.de,
            cpu->regs.hl,
            cpu->regs.sp,
            cpu->cycles,
            memory->data[*pc],
            memory->data[*pc+1],
            memory->data[*pc+2],
            memory->data[*pc+3]);
#endif
#endif

    uint16_t *pc = &cpu->regs.pc;
    uint8_t *instr = &memory->data[*pc];
    instr_info_t ii = opcode_map[instr[0]];

    if(cpu->ei && cpu->interrupt_vector) {
        cpu->ei = false;
        cpu->is_halted = false;
        ii = opcode_map[cpu->interrupt_vector];
        cpu->interrupt_vector = 0;
    }

    if(cpu->is_halted)
        return;

    if(ii.op_bytes <= 0) {
        LOG_WARNING(cpu->regs.pc, "Unimplemented opcode: %02X", instr[0]);
        *pc += 1;
    } else {
#ifdef DEBUG
        fprintf(stderr, "%-12s(0x%02X)\tBytes: %" PRIu8"\tCycles: %" PRIu8"\tPC: %04X\n",
                ii.instruction, *instr, ii.op_bytes, ii.cycles, *pc);
        fprintf(stderr, "  Registers:\n");
        fprintf(stderr, "   sp: 0x%04X\n", cpu->regs.sp);
        fprintf(stderr, "    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.sp, cpu->mem.data[cpu->regs.sp]);
        fprintf(stderr, "   pc: 0x%04X\n", cpu->regs.pc);
        fprintf(stderr, "   af: 0x%04X\n", cpu->regs.psw);
        fprintf(stderr, "    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.psw, cpu->mem.data[cpu->regs.psw]);
        fprintf(stderr, "    Flags:\n");
        fprintf(stderr, "     carry: %" PRIu8"\n", cpu->regs.f.carry);
        fprintf(stderr, "     parity: %" PRIu8"\n", cpu->regs.f.parity);
        fprintf(stderr, "     aux_carry: %" PRIu8"\n", cpu->regs.f.aux_carry);
        fprintf(stderr, "     zero: %" PRIu8"\n", cpu->regs.f.zero);
        fprintf(stderr, "     sign: %" PRIu8"\n", cpu->regs.f.sign);
        fprintf(stderr, "   bc: 0x%04X\n", cpu->regs.bc);
        fprintf(stderr, "    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.bc, cpu->mem.data[cpu->regs.bc]);
        fprintf(stderr, "   de: 0x%04X\n", cpu->regs.de);
        fprintf(stderr, "    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.de, cpu->mem.data[cpu->regs.de]);
        fprintf(stderr, "   hl: 0x%04X\n", cpu->regs.hl);
        fprintf(stderr, "    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.hl, cpu->mem.data[cpu->regs.hl]);
        fprintf(stderr, "  Data:");
        for(uint8_t i = 0; i < ii.op_bytes; i++) {
            fprintf(stderr, " %02X", *(instr+i));
        }
        fprintf(stderr, "\nTotal Cycles: %" PRIu64, cpu->cycles);
        fprintf(stderr, "\n");
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

    cpu->cycles += ii.cycles;
}
