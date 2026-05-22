#include "log.h"
#include "intel8080.h"

void init_memory(memory_t *mem) {
    memset(mem->data, 0, MAX_MEM);
}

void reset_memory(registers_t *regs, memory_t *mem) {
    regs->pc = 0x0;
    regs->sp = 0x0;
    init_memory(mem);
}

bool init_8080(intel8080 *cpu, char *rom_name) {
    strncpy(cpu->rom_name, rom_name, strlen(rom_name));

    FILE *fp = fopen(rom_name, "rb");
    if(!fp) {
        printf("Unable to open fp %s\n", rom_name);
        return false;
    }

    fseek(fp, 0, SEEK_END);
    cpu->rom_size = ftell(fp);
    if(cpu->rom_size > 0xFFFF) {
        printf("ROM file is greater than 8192 bytes, file: %"PRIu16, cpu->rom_size);
        fclose(fp);
        return false;
    }
    rewind(fp);

    reset_memory(&cpu->regs, &cpu->mem);

    if(!fread(cpu->mem.data, cpu->rom_size, 1, fp)) {
        printf("Failed to read memory from ROM\n");
        fclose(fp);
        return false;
    }

    fclose(fp);

    memset(cpu->io.display, 0, sizeof(cpu->io.display));
    cpu->io.scale_factor = 2;

    cpu->cycles = 0;
    cpu->is_halted = false;
    cpu->ei = false;

    return true;
}

void destroy_8080(intel8080 *cpu) {
    init_memory(&cpu->mem);
    cpu->rom = NULL;
}
