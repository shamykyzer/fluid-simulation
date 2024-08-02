#include <stdlib.h>
#include <math.h>
#include "particle.h"

// Initialize particles with random positions and velocities
void initParticles(Particle* particles, int numParticles) {
    for (int i = 0; i < numParticles; ++i) {
        particles[i].x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        particles[i].y = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        particles[i].vx = 0.0f;
        particles[i].vy = 0.0f;
    }
}

// Update particles based on mouse position and fluid dynamics
void updateParticles(Particle* particles, int numParticles, float mouseX, float mouseY, float viscosity, int trailLength) {
    for (int i = 0; i < numParticles; ++i) {
        for (int j = 0; j < trailLength; ++j) {
            float dx = mouseX - particles[i].x;
            float dy = mouseY - particles[i].y;
            float distance = sqrt(dx * dx + dy * dy);
            if (distance < 0.1f) distance = 0.1f;

            particles[i].vx += dx / distance * 0.01f;
            particles[i].vy += dy / distance * 0.01f;

            particles[i].x += particles[i].vx;
            particles[i].y += particles[i].vy;

            particles[i].vx *= viscosity;
            particles[i].vy *= viscosity;
        }
    }
}
