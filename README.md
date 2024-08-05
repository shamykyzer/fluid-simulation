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
   git clone https://github.com/shamykyzer/fluid-simulation.git
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

## Controls

- **W**: Increase the number of particles
- **S**: Decrease the number of particles
- **+/-**: Increase/Decrease particle size
- **Mouse**: Click and drag to interact with particles
- **Scroll**: Increase/Decrease simulation speed

## Code Structure

- **`main.c`**: Sets up the window and handles the main loop.
- **`particle.c`**: Manages particle initialization and updates.
- **`shader_utils.c`**: Loads and compiles shaders.
- **`text_rendering.c`**: Handles rendering of text.
- **`fluid_simulation.c`**: Implements the fluid simulation logic.
- **Shader files** (`advect.vert`, `advect.frag`, etc.): Used for rendering and simulation.

## References

- For more details on OpenGL, visit the [OpenGL Wikipedia page](https://en.wikipedia.org/wiki/OpenGL).
- Learn more about GLFW on its [Wikipedia page](https://en.wikipedia.org/wiki/GLFW).
- For information on GLEW, check out its [Wikipedia page](https://en.wikipedia.org/wiki/OpenGL_Extension_Wrangler_Library).
- Discover more about GLUT on its [Wikipedia page](https://en.wikipedia.org/wiki/OpenGL_Utility_Toolkit).
- Explore the basics of [Fluid Dynamics](https://en.wikipedia.org/wiki/Fluid_dynamics) on Wikipedia.
- Learn about fluid simulation techniques from [Real-Time Fluid Dynamics for Games](http://developer.download.nvidia.com/books/HTML/gpugems/gpugems_ch38.html).
- For a deeper understanding of fluid simulation in graphics, refer to [Stable Fluids](https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph2007-tutorial-notes.pdf) by Jos Stam.
