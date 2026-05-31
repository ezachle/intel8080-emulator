#pragma once

#define LOG_WARNING(pc, format, ...) fprintf(stderr, "WARNING | PC: 0x%04X | " format "\n", pc, ##__VA_ARGS__)
#define LOG_DEBUG(pc, format, ...)   fprintf(stderr, "DEBUG   | PC: 0x%04X | " format "\n", pc, ##__VA_ARGS__)
#define LOG_ERROR(pc, format, ...)   fprintf(stderr, "ERROR   | PC: 0x%04X | " format "\n", pc, ##__VA_ARGS__)
#define LOG(pc, format, ...)         fprintf(stderr, "LOG     | PC: 0x%04X | " format "\n", pc, ##__VA_ARGS__)
