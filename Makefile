# Compiler
CC = gcc

# Output binary
TARGET = build/chip8

# Source files
SRC = src/main.c src/memory.c src/display.c

# Pedantic warnings
WAR = -Wall -Wextra -pedantic-errors

# Libraries
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(WAR) $(LIBS)

# Clean build files
clean:
	rm -f $(TARGET)

# Rebuild from scratch
re: clean all

run:
	./build/chip8