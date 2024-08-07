#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct {
    float x, y;
    float vx, vy;
    float r, g, b; // Color components
} Particle;

void initParticles(Particle* particles, int numParticles);
void updateParticles(Particle* particles, int numParticles, float speedFactor, int mousePressed, double mouseX, double mouseY);

#endif
