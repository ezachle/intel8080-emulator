CC := gcc

INCL := include
# maybe -Wall?
CFLAGS := -Wextra -Werror -I$(INCL)

RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib)
RAYLIB_LDFLAGS := $(shell pkg-config --libs raylib) -lm -lX11

# Added specific names to separate main.c and the
# space invaders main.c
CPU_SRC := src/intel8080.c src/opcode.c
CPU_OBJ := $(CPU_SRC:.c=.o)

INVADERS_SRC := $(wildcard space_invaders/*.c)
INVADERS_OBJ := $(INVADERS_SRC:.c=.o)

.PHONY: all Intel8080 CPM space-invaders clean

all: Intel8080

CPM: CFLAGS += -DCPM
CPM: all

# substitue .c to .o
Intel8080: $(CPU_OBJ)
	$(CC) $(CFLAGS) src/main.c -o $@ $^

SpaceInvaders: $(INVADERS_OBJ) $(CPU_OBJ)
	$(CC) -o $@ $^ $(RAYLIB_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(INVADERS_OBJ) $(CPU_OBJ)
	rm -f Intel8080 SpaceInvaders
