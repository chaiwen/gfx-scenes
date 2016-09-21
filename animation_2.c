#include <stdio.h>
#include "rainbow.h"

#define PI 3.14159265

int main(int argc, char **argv)
{
    printf("<scene>\n");
	printf("  <description text=\"\"/>\n\n");
	printf("  <duration time=\"20.0\"/>\n");
	printf("  <integrator type=\"explicit-euler\" dt=\"0.01\"/>\n\n");

    int i, j, k;
    float x, y;

	float dx = 1;
	float dy = 1;
	float radius = 0.03;
	
	int numSprings = 50;
	int numParticles = numSprings * 2;

	float px = 10.0;
	float py = 0.0;

	float vx = 0.0;
	float vy = 0.0;

	for (i = 0; i < numParticles; i++) {
		x = dx * cos((i*360/numParticles) * PI/180);
		y = dy * sin((i*360/numParticles) * PI/180);
		printf("  <particle m=\"1.0\" px=\"%f\" py=\"%f\" ", x, y);
		printf("vx=\"%f\" vy=\"%f\" fixed=\"0\" radius=\"%f\"/>\n", vy, vy, radius);
	}

	float kconst = 1.0;
	float lconst = 1.0;
	for (i = 0; i < numSprings; i++) {
		printf("  <edge i=\"%d\" j=\"%d\" radius=\"0.001\"/>", i, i + numSprings);

		kconst *= 0.9;
		lconst *= 0.8;
		printf("  <springforce edge=\"%d\" k=\"%f\" l0=\"%f\"/>", i, kconst, lconst);
	}
	for (i = 0; i < numParticles; i++) {
        float r,g,b;
        HSVtoRGB(&r, &g, &b, (i*360/numParticles), 0.9, 0.9);
		
		printf("  <particlecolor i=\"%d\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i, r, g, b);
		printf("  <particlepath i=\"%d\" duration=\"1.5\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i, r, g, b);
    }
	for (i = 0; i < numSprings; i++) {
        float r,g,b;
        HSVtoRGB(&r, &g, &b, (i*360/numSprings), 0.9, 0.9);

		r = g = b = 0.3;
		
		printf("  <edgecolor i=\"%d\" r=\"%f\" g=\"%f\" b=\"%f\"/>\n", i, r, g, b);
    }

	//printf("\n  <simplegravity fx=\"0.0\" fy=\"-1.81\"/>\n");
	printf("\n  <backgroundcolor r=\"1.0\" g=\"1.0\" b=\"1.0\"/>\n");
	printf("</scene>\n");

    return 0;
}
