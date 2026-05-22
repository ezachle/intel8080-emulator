#pragma once

#define LOG_WARNING(pc, format, ...) printf("WARNING | PC: 0x%04X | " format "\n", pc, ##__VA_ARGS__)
#define LOG_DEBUG(pc, format, ...)   printf("DEBUG   | PC: 0x%04X | " format "\n", pc, ##__VA_ARGS__)
#define LOG_ERROR(pc, format, ...)   printf("ERROR   | PC: 0x%04X | " format "\n", pc, ##__VA_ARGS__)
#define LOG(pc, format, ...)         printf("LOG     | PC: 0x%04X | " format "\n", pc, ##__VA_ARGS__)
