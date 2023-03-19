SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = wolf3d
INCLUDE_PATHS = -I /Users/alexander/opt/homebrew/Cellar/sdl2/2.26.4/include
LIBRARY_PATHS = -L /Users/alexander/opt/homebrew/Cellar/sdl2/2.26.4/lib
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
LINKER_FLAG = -lsdl2

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAG) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)
