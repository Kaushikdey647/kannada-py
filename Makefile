# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./include
LDFLAGS =

# Debug flags
ifdef DEBUG
CFLAGS += -g -DDEBUG
endif

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable name
EXEC = $(BIN_DIR)/kannada_compiler

# Phony targets
.PHONY: all clean

# Default target
all: $(EXEC)

# Rule to create directories
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into executable
$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Include dependencies
-include $(OBJS:.o=.d)

# Rule to generate dependency files
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

# Run target
run: $(EXEC)
	./$(EXEC) $(ARGS)

# Debug target
debug: CFLAGS += -g -DDEBUG
debug: clean all