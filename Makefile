CC = g++
EXE = bin/game

SRC_DIR = src
BIN_DIR = bin
OTHER_DIR = others
GLAD_DIR = others/glad
GLM_DIR = others/glm
IMGUI_DIR = others/imgui
STB_IMAGE_DIR = others/stb_image
INCLUDE_DIR = include

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
GLAD_FILE = $(GLAD_DIR)/glad.c
STB_IMAGE_FILE = $(STB_IMAGE_DIR)/stb_image.cpp
IMGUI_FILES = $(wildcard $(IMGUI_DIR)/*.cpp)

OBJS = 	$(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES)) \
		$(BIN_DIR)/glad.o $(BIN_DIR)/stb_image.o \
		$(patsubst $(IMGUI_DIR)/%.cpp,$(BIN_DIR)/%.o,$(IMGUI_FILES))

OPENGL_LIBS = -lglfw -lm -lOpenGL -lGL
INCLUDE = -I$(INCLUDE_DIR) -I$(OTHER_DIR) -I$(GLAD_DIR) -I$(GLM_DIR) -I$(IMGUI_DIR) -I$(STB_IMAGE_DIR)

.PHONY: all clean re

all: $(EXE)
	./$(EXE)

$(EXE): $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) -o $(EXE) $(OPENGL_LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/%.o: $(IMGUI_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/glad.o: $(GLAD_FILE)
	@mkdir -p $(BIN_DIR)
	$(CC) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/stb_image.o: $(STB_IMAGE_FILE)
	@mkdir -p $(BIN_DIR)
	$(CC) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(EXE) $(BIN_DIR)/*.o

re: clean all
