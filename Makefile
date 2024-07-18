# Compiler and linker
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS =

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
BIN_DIR = bin

# Output executable
TARGET = $(BIN_DIR)/kannada_compiler

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Create directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Clean up
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
