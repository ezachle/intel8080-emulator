CC := gcc

# tell compiler where additional header files are
INCL := include
CFLAGS := -Werror -I$(INCL) $(shell pkg-config --cflags raylib)
LDFLAGS := $(shell pkg-config --libs raylib) -lm -lX11

SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:.c=.o)

BUILD_NAME := Intel8080

.PHONY: all debug clean

all: $(BUILD_NAME)

debug: CFLAGS += -O0 -DDEBUG -g
debug: all

cpm-debug: CFLAGS += -O0 -DCPM -DDEBUG -g
cpm-debug: all

cpm: CFLAGS += -DCPM
cpm: all

# Compiles all the .c files in src into .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
# $< means the first parameter of the recipe
# $@ means the output
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm $(BUILD_NAME) $(OBJ)
