#include <stdio.h>
#include "rainbow.h"

#define PI 3.14159265

void newSpringy(float _xpos, float _ypos, int numSprings, int _offset);

int main(int argc, char **argv)
{
    printf("<scene>\n");
	printf("  <description text=\"rainbow springy stars\"/>\n\n");
	printf("  <duration time=\"10.0\"/>\n");
	printf("  <integrator type=\"symplectic-euler\" dt=\"0.01\"/>\n\n");

	int i;
	int numStars = 6;
	int particlesPerStar = 90;

	for (i = 0; i < numStars; i++) {
		float xpos = cos(i * 2 * PI / numStars);
		float ypos = sin(i * 2 * PI / numStars);
		newSpringy(xpos, ypos, particlesPerStar, i * particlesPerStar);
	}
	newSpringy(0, 0, particlesPerStar, i * particlesPerStar);

	printf("\n  <backgroundcolor r=\"0.0\" g=\"0.0\" b=\"0.0\"/>\n");
	printf("</scene>\n");

    return 0;
}
void newSpringy(float _xpos, float _ypos, int numSprings, int _offset) {
    int i, j, k;
    float x, y;
	float dx = 1;
	float dy = 1;
	float vy = 0;
	float vx = 0;
	float radius = 0.01;
	int numParticles = numSprings * 2;

	int particleOffset = _offset * 2;
	int springOffset = _offset;

	for (i = particleOffset; i < particleOffset + numParticles; i++) {
		x = _xpos + dx * cos(i * 2 * PI / numParticles);
		y = _ypos + dy * sin(i * 2 * PI / numParticles);
		printf("  <particle m=\"1.0\" px=\"%f\" py=\"%f\" ", x, y);
		printf("vx=\"%f\" vy=\"%f\" fixed=\"0\" radius=\"%f\"/>\n", vy, vy, radius);
	}
	float kconst = 0.8;
	float lconst = 1.0;
	for (i = particleOffset, j = 0; j < numSprings; i++, j++) {
		printf("  <edge i=\"%d\" j=\"%d\" radius=\"0.001\"/>", i, i + numSprings);

		lconst = 0.2 + 0.2 * sin(3 * 2 * PI * i/numSprings);
		printf("  <springforce edge=\"%d\" k=\"%f\" l0=\"%f\"/>", springOffset + j, kconst, lconst);
	}
	for (i = particleOffset, j = 0; j < numParticles; i++, j++) {
        float r,g,b;
        HSVtoRGB(&r, &g, &b, (j*360/numParticles), 0.9, 0.9);
		
		printf("  <particlecolor i=\"%d\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i, r, g, b);
		printf("  <particlepath i=\"%d\" duration=\"0.4\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i, r, g, b);
    }
	for (i = springOffset; i < springOffset + numSprings; i++) {
        float r,g,b;
        HSVtoRGB(&r, &g, &b, (i*360/numSprings), 0.9, 0.9);
		r = 0.3;
		g = 0.0;
		b = 0.3;	
		printf("  <edgecolor i=\"%d\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i, r, g, b);
    }
}
