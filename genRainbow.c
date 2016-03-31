#include <stdio.h>
#include <math.h>

void HSVtoRGB(float *r, float *g, float *b, float h, float s, float v)
{
    int i;
    float f, p, q, t;
    if (s == 0) {
        *r = *g = *b = v;
        return;
    }
    h /= 60;
    i = h;
    f = h - i;
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));

    switch (i) {
        case 0:
            *r = v;
            *g = t;
            *b = p;
            break;
        case 1:
            *r = q;
            *g = v;
            *b = p;
            break;
        case 2:
            *r = p;
            *g = v;
            *b = t;
            break;
        case 3:
            *r = p;
            *g = q;
            *b = v;
            break;
        case 4:
            *r = t;
            *g = p;
            *b = v;
            break;
        default:
            *r = v;
            *g = p;
            *b = q;
            break;
    }
}

int main(int argc, char **argv)
{
    float i;

    printf("c 24.2 29.3 53.6 0.0 0.0 -1.0 35.0 35.0 25.0 500 400\n");

    float mr = 255.0/255;
    float mg = 255.0/255;
    float mb = 255.0/255;
    printf("m %f %f %f 0.0 0.0 0.0 0.0 0.0 0.0 0.0\n", mr, mg, mb);
    printf("p 0.0 0.0 1 80.0\n");
    printf("l p -80. 120. -46.6 1.0 1.0 1.0\n");

    float y = 12;
    float radius = 25.0;
    float size = 5.0;

    float startx = 25;
    float startz = -52;

    for (i = 0; i < 800; i++)
    {
        float r,g,b;
        HSVtoRGB(&r, &g, &b, (i*360/800), 0.9, 0.9);        

        printf("m %f %f %f 0.8 0.8 0.8 100. 0.0 0.0 0.0\n", r, g, b);

        float x = startx + radius * cos((i * 3.14)/180 + 3.14/4);
        float z = startz + radius * sin((i * 3.14)/180 + 3.14/4);

        printf("s %f %f %f %f\n", x, y, z, size);

        y += 0.05;
        radius = radius * 0.999;
        size = size * 0.997;
    }

    //printf("s 10.0 -10.0 -62.56 5.\n");

    return 0;
}
