# Makefile for Student Management System

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data

# Source files
SOURCES = $(SRC_DIR)/Student.cpp $(SRC_DIR)/StudentManagementSystem.cpp $(SRC_DIR)/main.cpp
TARGET = $(BUILD_DIR)/student_system

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(DATA_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo "✓ Compilation successful: $(TARGET)"

# Run the program
run: $(TARGET)
	@cd $(BUILD_DIR) && ./student_system

# Load sample data
sample-data:
	@chmod +x scripts/add_sample_data.sh
	@./scripts/add_sample_data.sh

# Clean build artifacts
clean:
	@rm -rf $(BUILD_DIR)/*
	@echo "✓ Build directory cleaned"

# Clean everything including data
clean-all: clean
	@rm -rf $(DATA_DIR)/*
	@echo "✓ All generated files removed"

# Help command
help:
	@echo "Available targets:"
	@echo "  make          - Compile the project"
	@echo "  make run      - Compile and run"
	@echo "  make sample-data - Load sample student data"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make clean-all - Remove build artifacts and data"
	@echo "  make help     - Show this help message"

.PHONY: all run sample-data clean clean-all help
