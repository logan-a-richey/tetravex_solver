# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

# Target executable
TARGET = tetravex_solver

# Source files and object files
SRCS = main.c solver.c tile.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run the solver with sample args
#run: $(TARGET)
#	./$(TARGET) 2 1234 2341 3412 4123

