#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"

#define MAX_PARTICLES 100000
#define INITIAL_PARTICLES 500
#define INITIAL_PARTICLE_SIZE 2.0f
#define PARTICLE_INCREMENT 100
#define PARTICLE_DECREMENT 100
#define MAX_PARTICLE_SIZE 10.0f
#define MIN_PARTICLE_SIZE 1.0f
#define INITIAL_SPEED 1.0f
#define SPEED_INCREMENT 0.1f
#define MIN_SPEED 0.1f

Particle particles[MAX_PARTICLES];
int numParticles = INITIAL_PARTICLES;
float particleSize = INITIAL_PARTICLE_SIZE;
float speedFactor = INITIAL_SPEED;
int mousePressed = 0;
double mouseX, mouseY;

// Key callback to increase/decrease particle count and size
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_EQUAL: // '+' key (usually shifted '=')
                if (particleSize < MAX_PARTICLE_SIZE) particleSize += 0.5f; // Increase particle size
                break;
            case GLFW_KEY_MINUS: // '-' key
                if (particleSize > MIN_PARTICLE_SIZE) particleSize -= 0.5f; // Decrease particle size
                break;
            case GLFW_KEY_W:
                if (numParticles < MAX_PARTICLES) numParticles += PARTICLE_INCREMENT; // Increase particle count
                break;
            case GLFW_KEY_S:
                if (numParticles > PARTICLE_DECREMENT) numParticles -= PARTICLE_DECREMENT; // Decrease particle count
                break;
        }
    }
}

// Scroll callback to increase/decrease speed
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        speedFactor += SPEED_INCREMENT; // Increase speed
    } else if (yoffset < 0) {
        if (speedFactor > MIN_SPEED) speedFactor -= SPEED_INCREMENT; // Decrease speed
    }
}

// Mouse button callback to track left mouse button state
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mousePressed = 1;
        } else if (action == GLFW_RELEASE) {
            mousePressed = 0;
        }
    }
}

int main(int argc, char** argv) {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Particle Simulation", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Initialize particles
    initParticles(particles, numParticles);

    // Set callbacks for keyboard, scroll, and mouse interactions
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Get mouse position
        glfwGetCursorPos(window, &mouseX, &mouseY);
        mouseX = (mouseX / 800.0) * 2.0 - 1.0;
        mouseY = 1.0 - (mouseY / 600.0) * 2.0;

        // Update particles
        updateParticles(particles, numParticles, speedFactor, mousePressed, mouseX, mouseY);

        // Render particles
        glPointSize(particleSize);
        glBegin(GL_POINTS);
        for (int i = 0; i < numParticles; ++i) {
            glColor3f(particles[i].r, particles[i].g, particles[i].b);
            glVertex2f(particles[i].x, particles[i].y);
        }
        glEnd();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up resources
    glfwTerminate();
    return 0;
}