# Makefile for C++ Postfix Calculator Project

# Compiler to use
CXX = g++

# Compiler flags:
# -std=c++17: Use C++17 standard
# -Wall -Wextra -pedantic: Enable all warnings
# -O2: Optimize the code
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

# Include directories
INCLUDES = -I./include

# Source files
SRC = src/main.cpp src/postfixCalc.cpp

# Header files (for dependency tracking)
HEADERS = include/LinkedListStack.hpp include/StackEmptyException.hpp include/CannotEvaluateException.hpp

# Output executable
TARGET = main

# Default target to build the executable
all: $(TARGET)

# Rule to build the executable by compiling source files
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SRC)

# Rule to clean up build artifacts
clean:
	rm -f $(TARGET)
