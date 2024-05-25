GPP = g++
GPPFLAGS = -std=c++2a -I./header
SRC_DIR = src
OBJ_DIR = obj
EXES = ./utms.out

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
 
clean:  all
	rm -rf $(OBJ_DIR)/*.o

all : $(EXES)

$(EXES) : $(OBJECTS)
	$(GPP) $(GPPFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(wildcard $(SRC_DIR)/*.hpp)
	mkdir -p $(OBJ_DIR)
	$(GPP) $(GPPFLAGS) -c $< -o $@
