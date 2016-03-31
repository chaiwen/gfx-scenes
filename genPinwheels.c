#include <stdio.h>
#include "rainbow.h"

#define PI 3.14159265
#define NUM_BLADES 8

struct point {
    float x;
    float y;
    float z;
};
struct triangle {
    struct point p1;
    struct point p2;
    struct point p3;
};
struct pinwheel {
    struct triangle blades[NUM_BLADES];
};

void translateTriangle(struct triangle *tri, float x, float y, float z) {
    tri->p1.x += x;
    tri->p2.x += x;
    tri->p3.x += x;

    tri->p1.y += y;
    tri->p2.y += y;
    tri->p3.y += y;

    tri->p1.z += z;
    tri->p2.z += z;
    tri->p3.z += z;
}
void translatePinwheel(struct pinwheel *p, float x, float y, float z) {
    int i = 0;
    for (i = 0; i < NUM_BLADES; i++) {
        translateTriangle(&p->blades[i], x, y, z);
    }
}
void rotateTriangle(struct triangle *tri, float dx, float dy, float dz) {
    // get center of triangle
    //   float cx = (tri->p1.x + tri->p2.x + tri->p3.x) / 3; 
    //   float cy = (tri->p1.y + tri->p2.y + tri->p3.y) / 3; 
    //   float cz = (tri->p1.z + tri->p2.z + tri->p3.z) / 3;

    // move triangle to origin
    //translateTriangle(tri, -cx, -cy, -cz);

    // rotate triangle around center, now at origin
    double dsin = sin(dx * PI / 180.0);
    double dcos = cos(dx * PI / 180.0);

    // rotate around X
    float old_y = tri->p1.y;
    float old_z = tri->p1.z;
    tri->p1.y = dcos * old_y - dsin * old_z;
    tri->p1.z = dsin * old_y + dcos * old_z;

    old_y = tri->p2.y;
    old_z = tri->p2.z;
    tri->p2.y = dcos * old_y - dsin * old_z;
    tri->p2.z = dsin * old_y + dcos * old_z;

    old_y = tri->p3.y;
    old_z = tri->p3.z;
    tri->p3.y = dcos * old_y - dsin * old_z;
    tri->p3.z = dsin * old_y + dcos * old_z;

    // rotate around Y
    dsin = sin(dy * PI / 180.0);
    dcos = cos(dy * PI / 180.0);

    float old_x = tri->p1.x;
    old_z = tri->p1.z;
    tri->p1.x = dcos * old_x + dsin * old_z;
    tri->p1.z = -dsin * old_x + dcos * old_z;

    old_x = tri->p2.x;
    old_z = tri->p2.z;
    tri->p2.x = dcos * old_x + dsin * old_z;
    tri->p2.z = -dsin * old_x + dcos * old_z;

    old_x = tri->p3.x;
    old_z = tri->p3.z;
    tri->p3.x = dcos * old_x + dsin * old_z;
    tri->p3.z = -dsin * old_x + dcos * old_z;

    // rotate around Z
    dsin = sin(dz * PI / 180.0);
    dcos = cos(dz * PI / 180.0);

    old_x = tri->p1.x;
    old_y = tri->p1.y;
    tri->p1.x = dcos * old_x - dsin * old_y;
    tri->p1.y = dsin * old_x + dcos * old_y;

    old_x = tri->p2.x;
    old_y = tri->p2.y;
    tri->p2.x = dcos * old_x - dsin * old_y;
    tri->p2.y = dsin * old_x + dcos * old_y;

    old_x = tri->p3.x;
    old_y = tri->p3.y;
    tri->p3.x = dcos * old_x - dsin * old_y;
    tri->p3.y = dsin * old_x + dcos * old_y;

}
void printTriangle(struct triangle *tri) {

    printf("t %f %f %f %f %f %f %f %f %f\n", tri->p1.x, tri->p1.y, tri->p1.z,
            tri->p2.x, tri->p2.y, tri->p2.z, tri->p3.x, tri->p3.y, tri->p3.z);

}
void initPinwheel(struct pinwheel *p) {
    int i = 0;
    for (i = 0; i < NUM_BLADES; i++) {
        p->blades[i].p1.x = 0;
        p->blades[i].p1.y = 0;
        p->blades[i].p1.z = 0;

        p->blades[i].p2.x = 0;
        p->blades[i].p2.y = 3;
        p->blades[i].p2.z = 0;

        p->blades[i].p3.x = 3;
        p->blades[i].p3.y = 3;
        p->blades[i].p3.z = 0;

        rotateTriangle(&p->blades[i], 0, 10, -45 * i);
    }
}
void printPinwheel(struct pinwheel *p) {
    int i = 0;
    for (i = 0; i < NUM_BLADES; i++) {
        printTriangle(&p->blades[i]);
    }
}

int main(int argc, char **argv)
{
    printf("c 0. 0. 53.6 0.0 0.0 -1.0 35.0 35.0 25.0 640 480\n");

    float mr = 255.0/255;
    float mg = 255.0/255;
    float mb = 255.0/255;

    printf("l p -80. 120. -46.6 1.0 1.0 1.0\n");
    printf("l p 10. -10. 46.6 1.0 1.0 1.0\n");
    printf("l a .3 .3 .3\n");
    //printf("m 0. 0.5 1.0 0.0 0.0 0.0 1.0 0.2 0.2 0.2\n", mr, mg, mb);
    //printf("s 0. 0. 60. 5.\n");

    printf("m %f %f %f 0.8 0.8 0.8 0.9 0.6 0.6 0.6\n", mr, mg, mb);

    struct pinwheel p0;
    initPinwheel(&p0);

    int i = 0;
    float x = 0;
    float y = 0;
    for (i = 0; i < 100; i++) {
        float r,g,b;
        HSVtoRGB(&r, &g, &b, (i*360/800), 0.9, 0.9);
        printf("m %f %f %f 0.8 0.8 0.8 100. 0.7 0.7 0.7\n", r, g, b);
 
        x = cos(i*2 * PI/180);
        y = sin(i*2 * PI/180);
        translatePinwheel(&p0, x, y, -2);
        printPinwheel(&p0);
    }
    return 0;
}
