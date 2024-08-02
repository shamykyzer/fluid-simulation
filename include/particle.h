#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct {
    float x, y;
    float vx, vy;
} Particle;

#define INITIAL_PARTICLES 1000
#define MAX_PARTICLES 5000
#define MIN_TRAIL 1
#define MAX_TRAIL 10

void initParticles(Particle* particles, int numParticles);
void updateParticles(Particle* particles, int numParticles, float mouseX, float mouseY, float viscosity, int trailLength);

#endif
