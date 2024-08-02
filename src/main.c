#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>  // Include GLUT
#include <stdio.h>
#include "particle.h"
#include "shader_utils.h"
#include "text_rendering.h"

Particle particles[MAX_PARTICLES];
int numParticles = INITIAL_PARTICLES;
float viscosity = 0.99f;
int trailLength = 1;

// Mouse button callback
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        if (numParticles < MAX_PARTICLES) {
            numParticles += 100; // Increase particle count
        }
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        viscosity += 0.01f; // Increase viscosity
        if (viscosity > 1.0f) viscosity = 1.0f; // Cap viscosity
    }
}

// Scroll callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    trailLength += (int)yoffset;
    if (trailLength < MIN_TRAIL) trailLength = MIN_TRAIL;
    if (trailLength > MAX_TRAIL) trailLength = MAX_TRAIL;
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Fluid Simulation", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    GLuint shaderProgram = loadShader("shaders/shader.vert", "shaders/shader.frag");
    glUseProgram(shaderProgram);

    initParticles(particles, numParticles);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, x));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    // Set callbacks for mouse and scroll interactions
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Get mouse position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        mouseX = (mouseX / 800.0) * 2.0 - 1.0;
        mouseY = 1.0 - (mouseY / 600.0) * 2.0;

        // Update particles with mouse position
        updateParticles(particles, numParticles, mouseX, mouseY, viscosity, trailLength);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(particles), particles);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, numParticles);
        glBindVertexArray(0);

        // Render instructions
        glColor3f(1.0, 1.0, 1.0);
        renderText(window, "Right Click: Increase Liquid Volume", -0.95f, 0.90f);
        renderText(window, "Left Click: Increase Viscosity", -0.95f, 0.85f);
        renderText(window, "Mouse Wheel: Change Trail Length", -0.95f, 0.80f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
