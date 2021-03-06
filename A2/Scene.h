#ifndef scene
#define scene
#include <math.h>
#include "Matrix.h"
#include "Primatives.h"

class ViewSpace {
        void SetupViewSpace(float psi, float theta, float r);
    public:
        ViewSpace();
        ViewSpace(float psi, float theta, float r);
        int ViewDirection;
        float h;
        float d;
        float f;
        Vertex nearPlane; // d
        Vertex farPlane; // f
        
        Vertex *N;
        Vertex *V;
        Vertex *U;
        Matrix *Space = new Matrix(4,4);
        bool isInViewVolume(Matrix *point);

};

class WorldSpace {
public:
        WorldSpace();
        WorldSpace(float tx, float ty, float tz);//translation
        WorldSpace(float a, int axis); //rotation
        Matrix *Space = new Matrix(4,4);
};

#endif