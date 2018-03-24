#ifndef ImageSettings
#define ImageSettings


#define DEFAULT_RES 500
#include "Primatives.h"

class Image{
    public:
        int img[DEFAULT_RES][DEFAULT_RES][3];
        Image();
        void DDA(Point* points, int numpoints);
};


#endif