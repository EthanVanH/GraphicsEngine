#ifndef scene
#define scene
#include <math.h>
#include "Matrix.h"

class ViewSpace {
    public:
        ViewSpace();
        int ViewDirection;
        float h;
        float nearPlane;
        float farPlane;
        Matrix *Space = new Matrix(4,4);
        bool isInViewVolume(Matrix *point);
};

class WorldSpace {
public:
        WorldSpace();
        Matrix *Space = new Matrix(4,4);
};

#endif