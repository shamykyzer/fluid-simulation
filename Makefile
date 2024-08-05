CC = gcc
CFLAGS = -Wall -g -I.
LIBS = -lGL -lGLEW -lglfw -lGLU -lGLUT

# Source files
SRC = main.c particle.c shader_utils.c text_rendering.c fluid_simulation.c
# Object files
OBJ = $(SRC:.c=.o)
# Executable
EXEC = fluid_simulation

# Default target
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)
