CXX = g++
CXXFLAGS = -std=c++17 -Wall  -O2 -pg
INCLUDES = -I.

# Updated to include Proactor.cpp in the source files
SRC = kosaraju.cpp main.cpp Proactor.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = kosaraju

# Updated to include Proactor.cpp in the test source files if needed
TEST_SRC = test.cpp kosaraju.cpp Proactor.cpp
# Exclude main.cpp from the test object files to avoid multiple definitions of main
TEST_OBJ = $(filter-out main.o, $(TEST_SRC:.cpp=.o))
TEST_TARGET = test_kosaraju

# Default target
all: $(TARGET)

# Main program target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJ) 
# Test program target
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(TEST_OBJ)

# Generic rule for compiling object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(TARGET) $(TEST_OBJ) $(TEST_TARGET)