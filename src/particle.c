#include "particle.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Initialize particles with random positions and velocities
void initParticles(Particle* particles, int numParticles) {
    srand(time(NULL));
    for (int i = 0; i < numParticles; ++i) {
        particles[i].x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        particles[i].y = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        particles[i].vx = ((float)rand() / RAND_MAX) * 0.01f - 0.005f;
        particles[i].vy = ((float)rand() / RAND_MAX) * 0.01f - 0.005f;
        particles[i].r = 0.0f;
        particles[i].g = 0.0f;
        particles[i].b = 1.0f;
    }
}

// Update particle positions randomly
void updateParticles(Particle* particles, int numParticles, float speedFactor, int mousePressed, double mouseX, double mouseY) {
    for (int i = 0; i < numParticles; ++i) {
        if (mousePressed) {
            particles[i].vx += (mouseX - particles[i].x) * 0.01f;
            particles[i].vy += (mouseY - particles[i].y) * 0.01f;
        } else {
            particles[i].x += particles[i].vx * speedFactor;
            particles[i].y += particles[i].vy * speedFactor;
        }

        // Wrap around the screen edges
        if (particles[i].x > 1.0f) particles[i].x = -1.0f;
        if (particles[i].x < -1.0f) particles[i].x = 1.0f;
        if (particles[i].y > 1.0f) particles[i].y = -1.0f;
        if (particles[i].y < -1.0f) particles[i].y = 1.0f;

        // Check for collisions with window borders
        if (particles[i].x > 1.0f || particles[i].x < -1.0f) {
            particles[i].vx = -particles[i].vx;
            particles[i].r = 1.0f;
            particles[i].g = 0.0f;
            particles[i].b = 0.0f;
        }
        if (particles[i].y > 1.0f || particles[i].y < -1.0f) {
            particles[i].vy = -particles[i].vy;
            particles[i].r = 1.0f;
            particles[i].g = 0.0f;
            particles[i].b = 0.0f;
        }

        // Check for collisions with other particles
        for (int j = i + 1; j < numParticles; ++j) {
            float dx = particles[i].x - particles[j].x;
            float dy = particles[i].y - particles[j].y;
            float distance = sqrt(dx * dx + dy * dy);
            if (distance < 0.01f) { // Adjust this value based on particle size
                // Simple elastic collision response
                float tempVx = particles[i].vx;
                float tempVy = particles[i].vy;
                particles[i].vx = particles[j].vx;
                particles[i].vy = particles[j].vy;
                particles[j].vx = tempVx;
                particles[j].vy = tempVy;

                // Turn both particles red
                particles[i].r = 1.0f;
                particles[i].g = 0.0f;
                particles[i].b = 0.0f;
                particles[j].r = 1.0f;
                particles[j].g = 0.0f;
                particles[j].b = 0.0f;
            }
        }
    }
}