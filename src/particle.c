#include "particle.h"
#include <stdlib.h>
#include <math.h>

// Initialize particles with random positions and velocities
void initParticles(Particle* particles, int numParticles) {
    for (int i = 0; i < numParticles; ++i) {
        // Set initial position of particle to a random point within [-1, 1] range
        particles[i].x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        particles[i].y = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        
        // Set initial velocity of particle to a random value within [-0.01, 0.01] range
        particles[i].vx = ((float)rand() / RAND_MAX) * 0.02f - 0.01f;
        particles[i].vy = ((float)rand() / RAND_MAX) * 0.02f - 0.01f;
    }
}

// Update particles based on mouse position, viscosity, trail length, and speed factor
void updateParticles(Particle* particles, int numParticles, float mouseX, float mouseY, float viscosity, int trailLength, float speedFactor) {
    for (int i = 0; i < numParticles; ++i) {
        // Calculate distance from particle to mouse position
        float dx = mouseX - particles[i].x;
        float dy = mouseY - particles[i].y;
        float distance = sqrt(dx * dx + dy * dy);
        
        // Prevent division by zero or very small distances
        if (distance < 0.1f) distance = 0.1f;

        // Update particle velocity based on distance to mouse and speed factor
        particles[i].vx += (dx / distance) * 0.001f * speedFactor;
        particles[i].vy += (dy / distance) * 0.001f * speedFactor;

        // Update particle position based on velocity
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;

        // Apply viscosity to slow down particles over time
        particles[i].vx *= viscosity;
        particles[i].vy *= viscosity;

        // Bounce particles off the edges of the screen
        if (particles[i].x > 1.0f || particles[i].x < -1.0f) {
            particles[i].vx *= -0.9f; // Reverse and dampen velocity in x direction
        }
        if (particles[i].y > 1.0f || particles[i].y < -1.0f) {
            particles[i].vy *= -0.9f; // Reverse and dampen velocity in y direction
        }
    }
}