#version 330 core

layout (location = 0) in vec2 aPosition; // Input attribute for vertex position
out vec2 TexCoords; // Output variable for texture coordinates

void main() {
    TexCoords = aPosition * 0.5 + 0.5; // Calculate texture coordinates
    gl_Position = vec4(aPosition, 0.0, 1.0); // Set the position of the vertex
}
