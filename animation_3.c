#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rainbow.h"

#define PI 3.14159265

void newParticle(float m, float x, float y, float vx, float vy, float r)
{
	printf("  <particle m=\"%f\" px=\"%f\" py=\"%f\" ", m, x, y);
	printf("vx=\"%f\" vy=\"%f\" fixed=\"0\" radius=\"%f\"/>\n", vx, vy, r);
}
void newParticleTag(float m, float x, float y, float vx, float vy, float r)
{
	printf("  <particle m=\"%f\" px=\"%f\" py=\"%f\" ", m, x, y);
	printf("vx=\"%f\" vy=\"%f\" fixed=\"0\" radius=\"%f\" tag=\"teleport\"/>\n", vx, vy, r);
}
void newVortexForce(int i, int j, float kbs, float kvc)
{
	printf("  <vortexforce i=\"%d\" j=\"%d\" kbs=\"%f\" kvc=\"%f\"/>\n", i, j, kbs, kvc);
}
void newCircle(int dx, int dy, int radius, int numVortex, int numParticles, int offset)
{
	int i, j;
	float x, y;
	float particle_radius = 10.0;

	float kbs = 80.0; // Biot-Savart force strength
	float kvc = 300.0; // viscous drag

	for (i = 0; i < numParticles; i++) {
		particle_radius = 1.0 + 7.0 * (float)rand() / (float)RAND_MAX;
		x = dx + radius * cos(i * 2 * PI / numParticles);
		y = dy + radius * sin(i * 2 * PI / numParticles);
		newParticleTag(1.0, x, y, 0, 0, particle_radius);
	}
	for (i = offset; i < offset + numParticles; i++) {
		for (j = 0; j < numVortex; j++) {
			newVortexForce(j, i, kbs, kvc);
		}
	}

	for (i = offset, j = 0; j < numParticles; i++, j++) {
		float r,g,b;
		HSVtoRGB(&r, &g, &b, (j*360/numParticles), 0.3, 1.0);					
		printf("  <particlecolor i=\"%d\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i, r, g, b);
	}
}
int main(int argc, char **argv)
{
    printf("<scene>\n");
	printf("  <description text=\"pastel rainbow vortex\"/>\n\n");
	printf("  <scenetag tag=\"RainbowVortex\"/>\n\n");
	printf("  <duration time=\"50.0\"/>\n");
	printf("  <integrator type=\"symplectic-euler\" dt=\"0.1\"/>\n\n");

	int numVortex = 6;
	int numParticles = 800;
	
	int i, j;
	float x, y, vx, vy;

	for (i = 0; i < numVortex; i++) {
		x = 0 + 57 * cos(i * 2 * PI / numVortex);
		y = 0 + 57 * sin(i * 2 * PI / numVortex);

		float l = sqrt(x * x + y * y);
		vx = x / l;
		vy = y / l;
		newParticle(1000000000.0, x, y, vx, vy, 1);
	}

	for (i = 0; i < numVortex; i++) {
		x = 0 + 60 * cos(0.6 + i * 2 * PI / numVortex);
		y = 0 + 60 * sin(0.6 + i * 2 * PI / numVortex);
		newParticle(1000000000.0, x, y, 0, 0, 1);
	}

	newParticle(10000000.0, 0, 0, 0, 0, 1);
	numVortex = 2 * numVortex + 1;

	for (i = 0; i < numVortex; i++) {
		printf("  <particlecolor i=\"%d\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i, 1.0, 1.0, 1.0);
	}

	newCircle(0, 0, 20, numVortex, numParticles, numVortex + 0 * numParticles);

	printf("\n  <backgroundcolor r=\"1.0\" g=\"1.0\" b=\"1.0\"/>\n");
	printf("</scene>\n");

    return 0;
}
