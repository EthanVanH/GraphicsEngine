
#include <math.h>
#include <stdio.h>
#include "Primatives.h"

Vertex::Vertex(float xcoor, float ycoor, float zcoor){
    x = xcoor;
    y = ycoor;
    z = zcoor;
    w = 1;
    inView = false;
}

float Vertex::GetX(){
    return x;
}

float Vertex::GetY(){
    return y;
}

float Vertex::GetZ(){
    return z;
}

float Vertex::GetW(){
    return w;
}

Matrix* Vertex::GetMatrix(){
    Matrix* m = new Matrix(4,1);
    float* values = new float[4];
    values[0] = x;
    values[1] = y;
    values[2] = z;
    values[3] = w;
    m->MInsertColumn(values,0);

    return m;
}
void Vertex::Print(){
    cout << " x = " << x << " y = " << y << " z = " << z << " w = " << w << '\n';
}


void Vertex::SetX(float xcoor){
    x = xcoor;
}

void Vertex::SetY(float ycoor){
    y = ycoor;
}

void Vertex::SetZ(float zcoor){
    z = zcoor;
}

void Vertex::SetW(float wval){
    w = wval;
}

void Vertex::SetInView(){
    inView = true;
}

void Vertex::SetMatrix(Matrix m){
    // cout << "Final rows" << m->rows<< '\n';

    x = m.m[0][0];
    y = m.m[0][1];
    z = m.m[0][2];
    w = m.m[0][3];
}

//Vector Math operations be here
Vertex Vertex::Projection(){ // put the vector in orthagonal view
    //e = {0,0,-1} centered and away from the screen
    Vertex v2;
    v2.SetX((-1/z)*x - 0);
    v2.SetY((-1/z)*y - 0);
    v2.SetZ(-z);    
    return v2;
}

Vertex Vertex::NDC(float r, float l, float t, float b){
    Vertex v2; // put the vector in NDC values
    v2.SetX(2* (x/((r - l) - (r + l)/( r - l))));
    v2.SetY(2* (y/((t - b) - (t + b)/( t - b))));
    v2.SetZ(z);
    return v2;
}

//rastorize to pixel space
Vertex Vertex::Rastor(float w, float h){
    Vertex v2;
    v2.SetX((x+1)/2*w);
    v2.SetY((1-y)/2*h);
    v2.SetZ(z);
    return v2;
}
//Vector addition
Vertex Vertex::operator+(Vertex &v){
    return Vertex(x + v.x, y + v.y, z + v.z);
}

//Vector subtraction
Vertex Vertex::operator-(Vertex v){
    return Vertex(x - v.x, y - v.y, z - v.z);
}

//negation
Vertex Vertex::operator-(){
    return Vertex(-x,-y,-z);
}

//the ole dot product
float Vertex::DotProduct(Vertex *v){
    return x * v->x + y * v->y + z* v->z; 
}

//the mighty cross product
Vertex Vertex::CrossProduct(Vertex *v){
    return Vertex(y * v->z - z * v->y, 
                  z * v->x - x * v->z, 
                  x * v->y - y * v->x);
}

//Scaler product
Vertex Vertex::operator*(float f){
    return Vertex(x * f, y * f, z * f);
}
//Vector multiplication x = x1 *x2, y = y1 *y2 and so on
Vertex Vertex::operator*(Vertex *v){
    return Vertex(x * v->x, y * v->y, z * v->z);
}


//normal and length
float Vertex::norm(){
    return x * x + y * y + z * z;
}

float Vertex::length() {
    return sqrt(norm());
}

Vertex* Vertex::normalize(){
    float n;
    n = norm();

    if(n > 0 ){
        float factor = 1/ length();
        x *= factor;
        y *= factor;
        z *= factor;
    }
    return this;
}

//some usefull operations i learned on the internet

Vertex Vertex::operator*=(float &f){
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Vertex Vertex::operator/=(float &f){
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

//2d vertex
Vertex2d::Vertex2d(float xcoor, float ycoor){
    x = xcoor;
    y = ycoor;
}
Vertex2d::Vertex2d(Vertex original){
    x = original.GetX()/original.GetZ();
    y = original.GetY()/original.GetZ();
}

void Vertex2d::SetX(float xcoor){
    x = xcoor;
}
void Vertex2d::SetY(float ycoor){
    y = ycoor;
}


//POLYGON from here down
void Polygon::Rotate(char axis, float deg){
    int i;
    float newx;
    float newy;
    float newz;
    Vertex *v;

    for(i = 0; i < vertexCount; i ++){
        v = &verticies[i];
        newx = v->GetX();
        newy = v->GetY();
        newz = v->GetZ();
        //printf("Original vertex was %f %f %f\n",newx,newy,newz);
        if(axis == 'x'){
            newy = (v->GetY() * cos(deg) - v->GetZ() * sin(deg));
            newz = (v->GetY() * sin(deg) + v->GetZ() * cos(deg));
        }
        else if(axis == 'y'){
            newx = (v->GetX() * cos(deg) + v->GetZ() * sin(deg));
            newz = (v->GetX()* -1 * sin(deg) + v->GetZ() * cos(deg));
        }
        else if(axis == 'z'){
            newx = (v->GetX() * cos(deg) - v->GetY() * sin(deg));
            newy = (v->GetX() * sin(deg) + v->GetY() * cos(deg));
        }
        else{
            printf("Unknown transformation axis\n");
        }
        v->SetX(newx);
        v->SetY(newy);
        v->SetZ(newz);
        //printf("new vertex is %f %f %f\n",newx,newy,newz);

    }
}

void Polygon::Scale(float factor){
    int i;
    float newx;
    float newy;
    float newz;
    Vertex *v;

    for(i = 0; i < vertexCount; i++){
        v = &verticies[i];
        newx = v->GetX();
        newy = v->GetY();
        newz = v->GetZ();
        //to scale can i just multiply by .5 across the board?
        
        newx = newx*factor;
        newy = newy*factor;
        newz = newz*factor;

        v->SetX(newx);
        v->SetY(newy);
        v->SetZ(newz);
    }
}



void Polygon::Transform(Matrix* w){
    for(int i = 0; i < vertexCount; i++){
        Vertex v = verticies[i];
        Matrix *m = v.GetMatrix();
        verticies[i].SetMatrix(w->MMultiply(m));
        //transform doesnt bother the norm unless, UNLESS its a non affine transformation
    }
}
