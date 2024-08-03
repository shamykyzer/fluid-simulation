#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "shader_utils.h"
#include "text_rendering.h"

#define MAX_PARTICLES 100000
#define INITIAL_PARTICLES 50000
#define INITIAL_VISCOSITY 0.98f
#define INITIAL_TRAIL_LENGTH 1
#define INITIAL_SPEED_FACTOR 1.0f
#define INITIAL_PARTICLE_SIZE 2.0f
#define PARTICLE_INCREMENT 100
#define PARTICLE_DECREMENT 100
#define MAX_PARTICLE_SIZE 10.0f
#define MIN_PARTICLE_SIZE 1.0f

Particle particles[MAX_PARTICLES];
int numParticles = INITIAL_PARTICLES;
float viscosity = INITIAL_VISCOSITY;
int trailLength = INITIAL_TRAIL_LENGTH;
float speedFactor = INITIAL_SPEED_FACTOR;
float particleSize = INITIAL_PARTICLE_SIZE;

// Mouse button callback
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        if (numParticles < MAX_PARTICLES) {
            numParticles += PARTICLE_INCREMENT; // Increase particle count
        }
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        viscosity += 0.01f; // Increase viscosity
        if (viscosity > 1.0f) viscosity = 1.0f; // Cap viscosity
    }
}

// Scroll callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        if (numParticles < MAX_PARTICLES) {
            numParticles += PARTICLE_INCREMENT; // Increase particle count
        }
    } else if (yoffset < 0) {
        if (numParticles > PARTICLE_DECREMENT) {
            numParticles -= PARTICLE_DECREMENT; // Decrease particle count
        }
    }
}

// Key callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                speedFactor += 0.1f; // Increase speed
                break;
            case GLFW_KEY_DOWN:
                if (speedFactor > 0.1f) speedFactor -= 0.1f; // Decrease speed
                break;
            case GLFW_KEY_LEFT:
                if (viscosity > 0.01f) viscosity -= 0.01f; // Decrease viscosity
                break;
            case GLFW_KEY_RIGHT:
                if (viscosity < 1.0f) viscosity += 0.01f; // Increase viscosity
                break;
            case GLFW_KEY_EQUAL: // '+' key (usually shifted '=')
                if (particleSize < MAX_PARTICLE_SIZE) particleSize += 0.5f; // Increase particle size
                break;
            case GLFW_KEY_MINUS: // '-' key
                if (particleSize > MIN_PARTICLE_SIZE) particleSize -= 0.5f; // Decrease particle size
                break;
        }
    }
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Fluid Simulation", NULL, NULL);
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

    // Load and use the shader program
    GLuint shaderProgram = loadShader("shaders/shader.vert", "shaders/shader.frag");
    glUseProgram(shaderProgram);

    // Initialize particles
    initParticles(particles, numParticles);

    // Generate and bind Vertex Array Object and Vertex Buffer Object
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_DYNAMIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, x));
    glEnableVertexAttribArray(0);

    // Enable vertex attribute for velocity
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, vx));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    // Set callbacks for mouse, scroll, and keyboard interactions
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Get mouse position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        mouseX = (mouseX / 800.0) * 2.0 - 1.0;
        mouseY = 1.0 - (mouseY / 600.0) * 2.0;

        // Update particles with mouse position
        updateParticles(particles, numParticles, mouseX, mouseY, viscosity, trailLength, speedFactor);

        // Update the buffer data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(particles), particles);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Set the point size uniform
        glUniform1f(glGetUniformLocation(shaderProgram, "uPointSize"), particleSize);

        // Draw the particles
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, numParticles);
        glBindVertexArray(0);
        
        // Render text labels
        glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
        const char* texts[] = {
            "Right Click: Increase Particles",
            "Left Click: Increase Viscosity",
            "Scroll Up: Increase Particles",
            "Scroll Down: Decrease Particles",
            "Arrow Up: Increase Speed",
            "Arrow Down: Decrease Speed",
            "Arrow Left: Decrease Viscosity",
            "Arrow Right: Increase Viscosity",
            "'+': Increase Particle Size",
            "'-': Decrease Particle Size"
        };
        
        float startY = 0.9f;
        float lineHeight = 0.05f;
        for (int i = 0; i < 10; ++i) {
            renderText(-0.95f, startY - i * lineHeight, texts[i]);
        }
        
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}