# Detect the operating system
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)

# Define compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = rsa_example.exe
SRCS = rsa.cpp helperFunctions.cpp
OBJS = $(SRCS:.cpp=.o)

# Platform-specific commands
ifeq ($(UNAME_S),Windows_NT)
    RM = powershell -Command Remove-Item 
else
    RM = rm -f 
endif

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
ifeq ($(UNAME_S),Windows_NT)
	@powershell -Command "Remove-Item -Path $(OBJS) $(TARGET) -Force"
else
	$(RM) $(OBJS) $(TARGET)
endif

.PHONY: all clean

