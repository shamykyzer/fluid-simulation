#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include "shader_utils.h"

typedef struct {
    GLuint velocity;
    GLuint pressure;
    GLuint divergence;
    GLuint dye;
} RenderTargets;

GLuint quadVAO, quadVBO;
RenderTargets targets;
GLuint advectShader, divergenceShader, pressureSolveShader, gradientSubtractShader, applyForcesShader, updateDyeShader;

void initSimulation(int width, int height);
void stepSimulation(float dt);
void advect(GLuint target, float dt);
void computeDivergence();
void solvePressure();
void subtractPressureGradient();
void renderQuad();

void initSimulation(int width, int height) {
    // Initialize textures and framebuffers for the simulation
    glGenTextures(1, &targets.velocity);
    glBindTexture(GL_TEXTURE_2D, targets.velocity);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

    glGenTextures(1, &targets.pressure);
    glBindTexture(GL_TEXTURE_2D, targets.pressure);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

    glGenTextures(1, &targets.divergence);
    glBindTexture(GL_TEXTURE_2D, targets.divergence);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

    glGenTextures(1, &targets.dye);
    glBindTexture(GL_TEXTURE_2D, targets.dye);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

    advectShader = loadShader("advect.vert", "advect.frag");
    divergenceShader = loadShader("divergence.vert", "divergence.frag");
    pressureSolveShader = loadShader("pressure_solve.vert", "pressure_solve.frag");
    gradientSubtractShader = loadShader("gradient_subtract.vert", "gradient_subtract.frag");
    applyForcesShader = loadShader("apply_forces.vert", "apply_forces.frag");
    updateDyeShader = loadShader("update_dye.vert", "update_dye.frag");

    // Initialize quad for rendering to textures
    float quadVertices[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void stepSimulation(float dt) {
    advect(targets.velocity, dt);
    computeDivergence();
    solvePressure();
    subtractPressureGradient();
    // Optionally update dye or apply forces here
}

void advect(GLuint target, float dt) {
    glUseProgram(advectShader);
    glUniform1f(glGetUniformLocation(advectShader, "uDt"), dt);
    glUniform1i(glGetUniformLocation(advectShader, "uVelocity"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, targets.velocity);

    // Render to target
    glBindFramebuffer(GL_FRAMEBUFFER, target);
    renderQuad();
}

void computeDivergence() {
    // Implement divergence calculation
}

void solvePressure() {
    // Implement pressure solving
}

void subtractPressureGradient() {
    // Implement gradient subtraction
}

void renderQuad() {
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
