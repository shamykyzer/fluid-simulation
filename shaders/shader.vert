#version 330 core

// Input attribute location 0: position of the particle
layout (location = 0) in vec2 aPos;

// Input attribute location 1: velocity of the particle (not used in this shader)
layout (location = 1) in vec2 aVel;

// Uniform variable for point size
uniform float uPointSize;

void main() {
    // Set the size of the point
    gl_PointSize = uPointSize;
    
    // Set the position of the point in clip space
    gl_Position = vec4(aPos, 0.0, 1.0);
}