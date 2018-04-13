#ifndef ImageSettings
#define ImageSettings


#define DEFAULT_RES 500

#define COLOUR_VARIABLES 3
#define COLOUR_MAX 255
#define COLOUR_MIN 0
#define DEFAULT_BACKGROUND 255
#define CLIPPING true
#define CULLING true

#include "Primatives.h"
#include "Scene.h"

class Image{
    private:
        void Sort(Point* points, int n);
        Point minPoint(Point a, Point b);
        static int compare(const void *vp1, const void *vp2);
        static int orientation(Point p, Point q, Point r);
        static int distSq(Point p1, Point p2);
        static void swap(Point p1, Point p2);
    public:
        int img[DEFAULT_RES][DEFAULT_RES][COLOUR_VARIABLES];
        Image();
        void DDA(Point* points, int numpoints);
        void Clip(Point* points, int numpoints, ViewSpace *vs);
        
};


#endif