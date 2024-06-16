# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -I./header

# Directories
SRC_DIRS = src server utils
OBJ_DIR = obj
BIN_DIR = bin

# Executable name
TARGET = utms.out

# Source files
SRCS = $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS)))

# Object files
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
$(OBJ_DIR)/%.o: %.cpp $(wildcard $(SRC_DIRS)/*.hpp)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET)

run: $(TARGET)
	./$(TARGET) ./csv_files/majors.csv ./csv_files/students.csv ./csv_files/courses.csv ./csv_files/professors.csv
