#include <stdio.h>
#include "rainbow.h"

#define PI 3.14159265

int main(int argc, char **argv)
{
    printf("<scene>\n");
	printf("  <duration time=\"5.0\"/>\n");
	printf("  <integrator type=\"explicit-euler\" dt=\"0.01\"/>\n\n");

    int i, j, k;
    float x, y;

	float dx = 2.0;
	float dy = -2.0;
	float radius = 0.2;
	
	int numParticles = 60;
	int numGroups = 30;

	float px = 10.0;
	float py = 0.0;

	for (j = 0; j < numGroups; j++) {
		dx *= 0.9;
		dy *= 0.9;
		radius *= 0.8;

		for (i = 0; i < numParticles; i++) {
			x = dx * cos((i*360/numParticles) * PI/180);
			y = dy * sin((i*360/numParticles) * PI/180);
			printf("  <particle m=\"1.0\" px=\"%f\" py=\"%f\" ", px, py);
			printf("vx=\"%f\" vy=\"%f\" fixed=\"0\" radius=\"%f\"/>\n", x, y, radius);
		}
	}

	for (i = 0; i < numParticles; i++) {
        float r,g,b;
        HSVtoRGB(&r, &g, &b, (i*360/numParticles), 0.9, 0.9);
		
		for (j = 0; j < numGroups; j++) {
			printf("  <particlecolor i=\"%d\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i + j*numParticles + k*numGroups*numParticles, r, g, b);
		}
    }

	for (i = 0; i < numParticles; i++) {
        float r,g,b;
        HSVtoRGB(&r, &g, &b, (i*360/numParticles), 0.9, 0.9);
		
		for (j = 0; j < numGroups; j++) {
			printf("  <particlepath i=\"%d\" duration=\"0.5\" ", i + j*numParticles + k*numGroups*numParticles);
			printf("r=\"%f\" g=\"%f\" b=\"%f\"/>\n", r, g, b);
		}
    }
	//printf("\n  <simplegravity fx=\"0.0\" fy=\"-1.81\"/>\n");
	printf("\n  <backgroundcolor r=\"1.0\" g=\"1.0\" b=\"1.0\"/>\n");
	printf("</scene>\n");

    return 0;
}
