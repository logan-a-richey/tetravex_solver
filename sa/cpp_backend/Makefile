CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -fopenmp

SRC = main.cpp solver.cpp pretty_printer.cpp generator.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = solver_program

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
