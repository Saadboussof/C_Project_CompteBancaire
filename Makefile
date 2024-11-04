# Makefile example for Windows using UCRT64 with wildcards

# Set the compiler and flags
CC = x86_64-w64-mingw32-gcc  # UCRT64 GCC Compiler
CFLAGS = -Wall -Wextra -O2  # Compiler flags for warnings and optimizations

# Define the target executable name
TARGET = main.exe

# Use wildcards to find all .c files and derive .o files from them
SRCS = $(wildcard *.c)                # All C source files
OBJS = $(SRCS:.c=.o)                   # Replace .c with .o to get object files

# Default target to build the executable
all: $(TARGET)

# Rule to link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ && ./$(TARGET)

# Pattern rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm *.o $(TARGET)
