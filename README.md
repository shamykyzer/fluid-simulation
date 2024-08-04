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

- **`main.c`:** Main program logic and rendering loop.
- **`particle.h`:** Particle structure and update functions.

## References

For more on fluid simulation, see the [Wikipedia page](https://en.wikipedia.org/wiki/Fluid_simulation).
