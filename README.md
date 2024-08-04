# Fluid Simulation

This project is a fluid simulation using OpenGL and GLFW. It visualizes particles moving in a fluid-like manner, with interactive controls to modify the simulation.

## Features

- **Interactive Particle Dynamics:** Use the mouse to influence particle movement.
- **Customizable Simulation Parameters:** Adjust particle count, size, and speed with keyboard controls.
- **Collision Detection:** Simulates basic collisions between particles and window borders.
- **Real-time Rendering:** Uses OpenGL for fast rendering.

## Getting Started

### Prerequisites

- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [GLUT](https://www.opengl.org/resources/libraries/glut/)

### Installation

1. **Clone the Repository:**

   ```sh
   git clone https://github.com/yourusername/fluid-simulation.git
   cd fluid-simulation
   ```

2. **Install Required Libraries:**

   On Ubuntu or Debian-based systems, run:

   ```sh
   sudo apt-get install libglfw3-dev libglew-dev freeglut3-dev
   ```

3. **Compile the Project:**

   ```sh
   make
   ```

### Usage

Run the compiled executable:

```sh
./fluid_simulation
```

### Controls

- **Mouse Interaction:**
  - **Left Click:** Attract particles toward the mouse position.
- **Keyboard Controls:**
  - **`+`**: Increase particle size
  - **`-`**: Decrease particle size
  - **`W`**: Increase particle count
  - **`S`**: Decrease particle count
- **Scroll Wheel:** Adjust speed

## Code Structure


├── shaders/                  # Shader files used in the simulation
│   ├── advect.frag           # Fragment shader for advection
│   ├── advect.vert           # Vertex shader for advection
│   ├── shader.frag           # Main fragment shader for rendering
│   └── shader.vert           # Main vertex shader for rendering
│
├── src/                      # Source files for the project
│   ├── fluid_simulation.c    # Core logic for fluid simulation
│   ├── main.c                # Entry point of the application
│   ├── particle.c            # Implementation of particle-related functions
│   ├── shader_utils.c        # Implementation of shader utility functions
│   └── text_rendering.c      # Implementation for text rendering
│
├── Makefile                  # Instructions for building the project
└── fluid_simulation          # Compiled executable of the simulation


## References

For more on fluid simulation, see the [Wikipedia page](https://en.wikipedia.org/wiki/Fluid_simulation).
