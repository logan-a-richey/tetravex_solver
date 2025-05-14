# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -fopenmp

# Directories (if you plan to use them)
SRCDIR = .
BUILDDIR = build

# Executable file name
EXEC = solver_program

# Source and object files
SOURCES = $(SRCDIR)/generator.cpp $(SRCDIR)/main.cpp $(SRCDIR)/solver.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(EXEC)

# Linking the final executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compiling the source files into object files
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(BUILDDIR)/*.o $(EXEC)

# Phony targets (not actual files)
.PHONY: all clean
