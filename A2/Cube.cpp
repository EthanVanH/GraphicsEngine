#include <stdio.h>
#include <iostream>

#include "ShapeDefinitions.h"
#include "Primatives.h"

Polygon Cube::PolygonFace(int selector){
    Polygon poly;
    Vertex* vertices;
    int vcount;
    int i;
    int j;  
    int n; 
    float k;

    //1 and 2 are y 3 and 4 are x 5 and 6 are z
    int sign; //1  is positive 0 negative
    n = resolution; // for brevitys sake and to help me keep the algorithm straight
    sign = selector%2;
    k = 1.0f;
    if(sign == 1){
        k = -1.0f;
    }
    
    vcount = 0;
    vertices = new Vertex[4];
    
    for (i = 0;i <= n; i++){
        for(j = 0;j <= n; j++){
             // 3 floats per vertex 4
            if(selector < 2){//top and or bottom polygon
                vertices[vcount].SetX((2/n)*i-1.0f); //
                vertices[vcount].SetY(k); // this is ugly...
                vertices[vcount].SetZ((2/n)*j-1.0f); //    
            }
            else if(selector < 4){ // left and or right polygon
                vertices[vcount].SetX(k); //
                vertices[vcount].SetY((2/n)*i-1.0f); // this is ugly...
                vertices[vcount].SetZ((2/n)*j-1.0f); //
            }
            else{ // front and back
                vertices[vcount].SetX((2/n)*i-1.0f); //
                vertices[vcount].SetY((2/n)*j-1.0f); // this is ugly...
                vertices[vcount].SetZ(k); //   
            }
                
            vcount++;      
        }
    }
    poly.vertexCount = vcount;
    poly.verticies = vertices; 
    return poly;
}

void  Cube::PolygonCube(){
    int i;
    cubeFaces = new Polygon[6];
    for(i = 0; i < faces; i++){
        cubeFaces[i] = PolygonFace(i);
    }
    
}

void Cube::TriangleCube(){
    int i;
    
    /*verticies obtained acording to the formula
    / P(i,j) = 2/n *i-1, 2/n*j -1
    / z value is always -1 for into the screen
    / I need to create all the vertices of a plane with one value set before hand
    / so for the faceing the screen planes z is 1 and -1
    / top and bottom y is 1 and -1
    / and on the sides x = 1 and -1
    */
    //this for loop is for each face.
    faces = resolution * resolution * 6;
    cubeFaces = new Polygon[faces];
    for(i = 0; i < faces; i++){
        cubeFaces[i] = PolygonFace(i);
    }
    
    //return vertices;
}

Cube::Cube(int mesh, int n){
    meshType = mesh;
    resolution = n;
    
    if (n == 0){ // just in case i messed up on resolution make sure we dont make a cube with zero verticies
        meshType = POLYGON;
        resolution = 1;
    }

    if (meshType == POLYGON){
        size = 16 /*VERTICIES*/;
        resolution = 1;
        PolygonCube();
    }
    else{
        size = 6 /*sides*/ * n /*triangles per face*/ * 3 /*vertecies per triange*/;
        //triangles boys
        TriangleCube();
    }
}

int Cube::GetNumVertices() {
    return faces * resolution * GetNumVertPFace() ;
}
int Cube::GetResolution() {
    return resolution;
}
int Cube::GetMeshType()  {
    return meshType;
}

int Cube::GetNumFaces(){
    return faces;
}

int Cube::GetNumVertPFace(){
    if(meshType == POLYGON){
        return 4;
    }
    else return 3;
}


Polygon* Cube::GetFaces(){
    return cubeFaces;
}

void Cube::Print(){
    
    for(int i = 0; i < faces; i++){
        for(int j = 0; j < GetNumVertPFace(); j++){
            cubeFaces[i].verticies[j].Print();
        }
    }
}

