#ifndef ImageSettings
#define ImageSettings


#define DEFAULT_RES 500

#define COLOUR_VARIABLES 3
#define COLOUR_MAX 255
#define COLOUR_MIN 0
#define DEFAULT_BACKGROUND 255

#include "Primatives.h"

class Image{
    public:
        int img[DEFAULT_RES][DEFAULT_RES][COLOUR_VARIABLES];
        Image();
        void DDA(Point* points, int numpoints);
};


#endif