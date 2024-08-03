#version 330 core

// Input variable representing the speed
in float speed; 

// Output variable representing the fragment color
out vec4 FragColor; 

void main() {
    // Calculate intensity based on speed, clamped between 0 and 1
    float intensity = clamp(speed * 5.0, 0.0, 1.0); 
    
    // Mix two colors based on intensity and assign to FragColor
    // The colors mixed are blue (vec4(0.0, 0.5, 1.0, 1.0)) and red (vec4(1.0, 0.0, 0.0, 1.0))
    FragColor = mix(vec4(0.0, 0.5, 1.0, 1.0), vec4(1.0, 0.0, 0.0, 1.0), intensity); 
}
