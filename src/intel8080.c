#include "log.h"
#include "intel8080.h"
#include "opcode.h"

void init_memory(memory_t *mem) {
    memset(mem->data, 0, MAX_MEM);
#ifdef CPM
    mem->data[0x0000] = 0xC9;
    mem->data[0x0005] = 0xC9;
    mem->data[0x0006] = 0x00;
    mem->data[0x0007] = 0xFE;
#endif
}

void reset_memory(registers_t *regs, memory_t *mem, const uint16_t start_pc) {
    regs->pc = start_pc;
    regs->sp = 0x0;
    init_memory(mem);
}

static bool load_rom(intel8080 *cpu, char *rom_name) {
    strncpy(cpu->rom_name, rom_name, strlen(rom_name));

    FILE *fp = fopen(rom_name, "rb");
    if(!fp) {
        LOG_ERROR(cpu->regs.pc, "Unable to open fp %s\n", rom_name);
        return false;
    }

    fseek(fp, 0, SEEK_END);
    cpu->rom_size = ftell(fp);
    if(cpu->rom_size > 0xFFFF) {
        LOG_ERROR(cpu->regs.pc, "ROM file is greater than 8192 bytes, file: %"PRIu16, cpu->rom_size);
        fclose(fp);
        return false;
    }
    rewind(fp);

    uint8_t *mem_ptr = NULL;
#ifdef CPM
    mem_ptr = &cpu->mem.data[0x0100];
#else
    mem_ptr = &cpu->mem.data[0x0000];
#endif
    if(!fread(mem_ptr, cpu->rom_size, 1, fp)) {
        LOG_ERROR(cpu->regs.pc, "Failed to read memory from ROM");
        fclose(fp);
        return false;
    }

    fclose(fp);
    LOG(cpu->regs.pc, "Loaded ROM %s", rom_name);
    return true;
}

bool init_8080(intel8080 *cpu, char *rom_name, const uint16_t start_pc) {
    reset_memory(&cpu->regs, &cpu->mem, start_pc);

    cpu->regs.f.unused1 = 1;
    cpu->regs.f.unused2 = 0;
    cpu->regs.f.unused3 = 0;

    cpu->regs.sp = 0;

    cpu->cycles = 0;
    cpu->is_halted = false;
    cpu->ei = false;
    cpu->interrupt_pending = false;
    cpu->interrupt_vector = 0;
    
    if(!load_rom(cpu, rom_name)) {
        LOG_ERROR(cpu->regs.pc, "Failed to load ROM: %s", rom_name);
        return false;
    }

    cpu->quit = false;
    memset(cpu->io.display, 0, sizeof(cpu->io.display));
    cpu->io.scale_factor = 2;

    return true;
}

void destroy_8080(intel8080 *cpu) {
    init_memory(&cpu->mem);
    cpu->rom = NULL;
}

#ifdef CPM
void handle_cpm(intel8080 *cpu) {
    if(cpu->regs.pc == 0x0005) {
        switch(cpu->regs.c) {
            case 2:
                printf("%c", cpu->regs.e);
                break;
            case 9:
                {
                    uint16_t str_addr = cpu->regs.de;
                    while(cpu->mem.data[str_addr] != '$') {
                        printf("%c", cpu->mem.data[str_addr++]);
                    }
                    printf("\n");
                }
                break;
            default:
                LOG_WARNING(cpu->regs.pc, "Unimplemneted CP/M Instruciton %" PRIu8, cpu->regs.c);
                break;
        }
    } else if(cpu->regs.pc == 0x0000) {
        LOG(cpu->regs.pc, "CPM Program Error");
        cpu->quit = true;
    }
}
#endif

void emulate_8080(intel8080 *cpu) {
    memory_t *memory = &cpu->mem;

#ifdef CPM
    handle_cpm(cpu);
    if(cpu->quit) return;
#endif

    uint16_t *pc = &cpu->regs.pc;
    if(cpu->ei && cpu->interrupt_pending) {
        cpu->ei = false;
        cpu->interrupt_pending = false;
        cpu->is_halted = false;
        *pc = cpu->interrupt_vector;
    }

    if(cpu->is_halted)
        return;

    uint8_t *instr = &memory->data[*pc];
    const instr_info_t ii = opcode_map[instr[0]];
    if(ii.op_bytes <= 0) {
        LOG_WARNING(cpu->regs.pc, "Unimplemented opcode: %02X", instr[0]);
        *pc += 1;
    } else {
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

        cpu->cycles += ii.cycles;
#ifdef DEBUG
        printf("%-12s(0x%02X)\tBytes: %" PRIu8"\tCycles: %" PRIu8"\tPC: %04X\n",
                ii.instruction, *instr, ii.op_bytes, ii.cycles, *pc);
        printf("  Registers:\n");
        printf("   sp: 0x%04X\n", cpu->regs.sp);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.sp, cpu->mem.data[cpu->regs.sp]);
        printf("   pc: 0x%04X\n", cpu->regs.pc);
        printf("   af: 0x%04X\n", cpu->regs.psw);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.psw, cpu->mem.data[cpu->regs.psw]);
        printf("    Flags:\n");
        printf("     carry: %" PRIu8"\n", cpu->regs.f.carry);
        printf("     parity: %" PRIu8"\n", cpu->regs.f.parity);
        printf("     aux_carry: %" PRIu8"\n", cpu->regs.f.aux_carry);
        printf("     zero: %" PRIu8"\n", cpu->regs.f.zero);
        printf("     sign: %" PRIu8"\n", cpu->regs.f.sign);
        printf("   bc: 0x%04X\n", cpu->regs.bc);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.bc, cpu->mem.data[cpu->regs.bc]);
        printf("   de: 0x%04X\n", cpu->regs.de);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.de, cpu->mem.data[cpu->regs.de]);
        printf("   hl: 0x%04X\n", cpu->regs.hl);
        printf("    memory[0x%04X](if applicable): 0x%02X\n", cpu->regs.hl, cpu->mem.data[cpu->regs.hl]);
        printf("  Data:");
        for(uint8_t i = 0; i < ii.op_bytes; i++) {
            printf(" %02X", *(instr+i));
        }
        printf("\nTotal Cycles: %" PRIu64, cpu->cycles);
        printf("\n");
#endif
    }
}

