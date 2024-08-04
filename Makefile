CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lGLEW -lglfw -lGL -lm -lglut -lGLU
SOURCES = src/main.c src/fluid_simulation.c src/shader_utils.c src/particle.c src/text_rendering.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = fluid_simulation

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)