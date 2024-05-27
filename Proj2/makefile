# Define compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude

# Define source and object files
SRC_FILES = main.cpp point.cpp NNC.cpp LOOV.cpp
OBJ_FILES = main.o point.o NNC.o LOOV.o
TARGET = main.exe

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

Point.o: point.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

NNC.o: NNC.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

LOOV.o: LOOV.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Clean up build files
clean:
	rm -f $(OBJ_FILES) $(TARGET)
