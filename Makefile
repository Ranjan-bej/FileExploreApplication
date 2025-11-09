# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I./src
LDFLAGS := -lstdc++fs

# Project name
TARGET := linux-file-explorer

# Source files
SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR := obj
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ_FILES)
	@echo "Linking $@..."
	@mkdir -p $(@D)
	@$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(OBJ_DIR) $(TARGET) $(TARGET).exe

# Run the program
run: $(TARGET)
	@./$(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove all build artifacts"
	@echo "  run     - Build and run the program"
	@echo "  help    - Show this help message"

# Set default target
.PHONY: all clean run help

# Dependencies
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/FileExplorer.h $(SRC_DIR)/FileOperations.h $(SRC_DIR)/UIManager.h
$(OBJ_DIR)/FileExplorer.o: $(SRC_DIR)/FileExplorer.cpp $(SRC_DIR)/FileExplorer.h $(SRC_DIR)/FileOperations.h
$(OBJ_DIR)/FileOperations.o: $(SRC_DIR)/FileOperations.cpp $(SRC_DIR)/FileOperations.h
$(OBJ_DIR)/UIManager.o: $(SRC_DIR)/UIManager.cpp $(SRC_DIR)/UIManager.h