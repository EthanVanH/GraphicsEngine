/*Implementation of the cylinder shape*/
/*class built for modeling a cylinder in 3d space*/
/*Creates an array of verticies in 3d space that represent a cylinder*/
/*model space ranges from -1 to 1 on all 3 axis*/
/*includes a w bit set to 1 for affine transformations*/


#include "ShapeDefinitions.h"
#include "Primatives.h"

void Cylinder::GenerateVerts(){
    int n = resolution;
    int x;
    int y;
    int z;
    cylinderFaces = new Polygon[faces* resolution];
    for(int i = 0; i < surfaces; i++){
        Polygon poly;
        
        poly.verticies = new Vertex[3];
        poly.vertexCount = 0;
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= n; k++){
                if(i%2 == 0){ // top and bottom faces
                    x = cos((2*3.1415/n) * j);
                    y = 2/n * k - 1;
                    z = sin((2*3.1415/n) * j);
                }
                else{//big ole middle
                    x = 2/n * j -1;
                    y = 2/n * k -1; 
                    z = -1; //ehhhhhhhhh
                }
                poly.verticies[poly.vertexCount] = Vertex(x,y,z);
                poly.vertexCount +=1;
            }
        }
        cylinderFaces[i] = poly;
    }
}

Cylinder::Cylinder(int mesh, int n){
    meshType = mesh;
    resolution = n;
    faces =  3 * resolution;
    if(n == 0){
        meshType = TRIANGLE;
        resolution = 10;
    }
    if(meshType == TRIANGLE){
        size = GetNumVertices();
        GenerateVerts();
    }
    if(meshType == POLYGON){
        resolution = 1;
        GenerateVerts();
        cout << "polygon cylinder not implemented";
    }
}

int Cylinder::GetNumFaces(){
    return faces * resolution;
}

int Cylinder::GetNumVertPFace(Polygon *face){
    return face->vertexCount;
}

int Cylinder::GetNumVertPFace(){
    return 3; //TODO
    //if not triangle mesh, panic
}

int Cylinder::GetNumVertices(){
    return faces * resolution * GetNumVertPFace();//TODO
}

int Cylinder::GetResolution(){
    return resolution;
}

int Cylinder::GetMeshType(){
    return meshType;
}

Polygon* Cylinder::GetFaces(){
    return cylinderFaces;
}

void Cylinder::Print(){
    
    for(int i = 0; i < faces; i++){
        for(int j = 0; j < GetNumVertPFace(); j++){
            cylinderFaces[i].verticies[j].Print();
        }
    }
}
