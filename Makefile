CC = gcc
CFLAGS = -Wall
LIBS = -lGL -lGLEW -lglfw -lGLU -lglut -lm
SRC_DIR = src
INC_DIR = include

all: fluid_simulation

fluid_simulation: $(SRC_DIR)/main.c $(SRC_DIR)/particle.c $(SRC_DIR)/shader_utils.c $(SRC_DIR)/text_rendering.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $^ -o $@ $(LIBS)

clean:
	rm -f fluid_simulation
