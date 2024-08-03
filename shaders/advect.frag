#version 330 core

in vec2 TexCoords; // Input texture coordinates
out vec4 FragColor; // Output fragment color

uniform sampler2D uVelocity; // Velocity texture
uniform float uDt; // Time step
uniform float uCellSize; // Cell size

void main() {
    vec2 velocity = texture(uVelocity, TexCoords).xy; // Get velocity from texture
    vec2 coord = TexCoords - uDt * velocity / uCellSize; // Calculate new coordinate based on velocity
    FragColor = texture(uVelocity, coord); // Output the color from the new coordinate
}
