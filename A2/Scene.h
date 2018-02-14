#ifndef scene
#define scene
#include <math.h>
#include "Matrix.h"
#include "Primatives.h"

class ViewSpace {
    public:
        ViewSpace();
        ViewSpace(float psi, float theta, float r);
        int ViewDirection;
        float h;
        float nearPlane; // d
        float farPlane; // f
        Vertex *N;
        Vertex *V;
        Vertex *U;
        Matrix *Space = new Matrix(4,4);
        bool isInViewVolume(Matrix *point);
};

class WorldSpace {
public:
        WorldSpace();
        Matrix *Space = new Matrix(4,4);
};

#endif