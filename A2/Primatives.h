/*Primitives.h contains definintions of shape primitives used in 3d modeling
/ So vectors and polygons
/ also there is a definition of a matrix here to simplify a 4 by 4 matrix
/ This is more for refrence than use
*/
#ifndef primitives
#define primitives

#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>

#include "Matrix.h"

class Vertex2d;


class Vertex{
    public:
        float x;
        float y;
        float z;
        float w;
        Vertex(){x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f;};
        Vertex(int rgb) : x(rgb), y(rgb), z(rgb) {}
        Vertex(float xcoor, float ycoor, float zcoor);
        float GetX();
        float GetY();
        float GetZ();
        float GetW();
        Matrix* GetMatrix();
        void SetMatrix(Matrix *m);
        void SetX(float xcoor);
        void SetY(float ycoor);
        void SetZ(float zcoor);
        void SetW(float wval);
        //Vector Operations --should I make a specific vecer class or use the cpp one...
        Vertex Projection();
        Vertex NDC(float r, float l, float t, float b);
        Vertex Rastor(float w, float h);
        float DotProduct(Vertex *v);
        Vertex CrossProduct(Vertex *v);
        Vertex* normalize();
        float norm();
        float length();
        Vertex operator*(float f); // scaler multiplication
        Vertex operator*(Vertex *v); // vector multiplication
        Vertex operator+(Vertex &v);
        Vertex operator-(); //negation
        Vertex operator-(Vertex v); // Vector subtraction
        Vertex operator*=(float &f);
        Vertex operator/=(float &f);
        void Print();

};

class Vertex2d{

    public:
        float x;
        float y;
        Vertex2d() : x(0), y(0) {};
        Vertex2d(float xcoor, float ycoor);
        Vertex2d(Vertex original);
        float GetX(){return x;}
        float GetY(){return y;}
        void SetX(float xcoor);
        void SetY(float ycoor);
        Vertex2d operator + (const Vertex2d &v) const
            { return Vertex2d(x + v.x, y + v.y); }
        Vertex2d operator / (float &r) const
            { return Vertex2d(x / r, y / r); }
        Vertex2d operator * (float &r) const
            { return Vertex2d(x * r, y * r); }
        Vertex2d& operator /= (float &r)
            { x /= r, y /= r; return *this; }
        Vertex2d& operator *= (float r)
            { x *= r, y *= r; return *this; }
};

class Polygon {
    public:
        int colour[3];
        Polygon(){colour[0] = rand()%255 ; colour[1] = rand()%255; colour[2] = rand()%255;};
        int vertexCount;
        Vertex* verticies;
        Vertex2d* vertices2d;
        void Transform(Matrix* w);
        void Rotate(char axis, float deg);
        void Scale(float factor);
};


#endif