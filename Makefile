# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g -std=gnu99

# Include directory
INCLUDES = -Iinclude

# Source and object files
SRC = src/main.c \
      src/parser.c \
      src/executor.c \
      src/builtins.c \
      src/shell_signal.c

OBJ = $(SRC:.c=.o)

# Output binary
TARGET = mini-shell

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Compile source files
src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)

# Full rebuild
rebuild: clean all

.PHONY: all clean rebuild
