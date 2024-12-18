# Makefile example for Windows using UCRT64 with wildcards

# Define the target executable name
TARGET = main.exe

# Use wildcards to find all .c files and derive .o files from them
SRCS = $(wildcard *.c)                    # Replace .c with .o to get object files

# Default target to build the executable
all: $(TARGET)

# Rule to link the object files to create the executable
app: 
	gcc -o $(TARGET) $(SRCS)  && ./$(TARGET)



# Clean up object files and the executable
clean:
	rm *.o $(TARGET)
