/* CIS*4800 Computer Graphics
 * Assignment 2
 * Written By: Ethan Van Houtven
 * This assignment covers the basics of setting up a scene for 3d graphics
 * Inluding the view space, world space and prospective projection
 * New files from a1 > Matrix.h '.cpp and Scene.h '.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
using namespace std;

//#include "shader.hpp"
#include "ShapeDefinitions.h"
#include "Primatives.h"
#include "Image.h"
#include "Matrix.h"
#include "Scene.h"


bool isShape(int posibleShape){
    if(posibleShape <0 || posibleShape > 6){
        return false;
    }
    return true;
}

bool isMesh(int possibleMesh){
    if(possibleMesh == 0 || possibleMesh == 1 ){
        return true;
    }
    return false;
}

void GetInput(int *shape, int *mesh) {
    //shape types are an enumeration
    int shapeIN = 100;;
    int meshIN = 100;
    
    //for now we will default to polygon mesh of a CUBE
    *shape = CUBE;
    *mesh = TRIANGLE;
    while(isShape(shapeIN) != true  && isMesh(meshIN) != true){
        cout << "Please enter the shape you would like to be generated\n";
        cout << "0 is a cube 1 is a cylinder";
        cin >> shapeIN;
        cout << "Please select a mesh type 0 is polygon mesh 1 is triangle\n";
        cin >> meshIN;

        if(isShape(shapeIN) != true || isMesh(meshIN) != true){
            cout<< "This is not an option- please follow input specifications\n";
        }
    }
    *shape = shapeIN;
    *mesh = meshIN;
}

Shape* MakeAShape(int shape, int mesh) {
    Shape* theShape;
    switch(shape) {
        case CUBE:
            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        case CYLINDER:
            //CreateCylinder(mesh);
            printf("Sorry this shape has not yet been implemented\n");
            printf("Making a cube instead\n");
            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);

        break;
        case CONE:
            //CreateCone(mesh);
            printf("Sorry this shape has not yet been implemented\n");
            printf("Making a cube instead\n");
            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        case SPHERE:
            //CreateSphere(mesh);
            printf("Sorry this shape has not yet been implemented\n");
            printf("Making a cube instead\n");
            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        case TUBE:
            //CreateTube(mesh);
            printf("Sorry this shape has not yet been implemented\n");
            printf("Making a cube instead\n");
            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        case TORUS:
            //CreateTorus(mesh);
            printf("Sorry this shape has not yet been implemented\n");
            printf("Making a cube instead\n");
            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        default:
            printf("This is not a supported shape\n");
            printf("Making a cube instead\n");
            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
    }
    return theShape;
}
// theShape->GetFaces()->verticies[0].GetMatrix()->Print();

void ModelViewProjection(ViewSpace *viewMatrix, Shape *shape){
    bool projFlag;
    int faceCount = shape->GetNumFaces();
    int vpf = shape->GetNumVertPFace();
    Polygon *polys = shape->GetFaces();
    WorldSpace *w = new WorldSpace();
    Matrix *projMatrix;
    
    float d = viewMatrix->nearPlane;

    float xproj[4] = {d, 0.0, 0.0, 0.0};
    float yproj[4] = {0.0, d, 0.0, 0.0};
    float zproj[4] = {0.0, 0.0, d, 0.0};
    float wproj[4] = {0.0, 0.0, 1.0, 0.0};

    projMatrix = new Matrix(4,4);
    projMatrix->MInsertColumn(xproj, 0);
    projMatrix->MInsertColumn(yproj, 1);
    projMatrix->MInsertColumn(zproj, 2);
    projMatrix->MInsertColumn(wproj, 3);

    cout << "The projection matrix is \n";
    projMatrix->Print();

    for(int i = 0; i < faceCount; i++ ){
        //transform
        polys[i].Transform(w->Space);
        polys[i].Transform(viewMatrix->Space);
        projFlag = true;
        for(int j = 0; j < vpf; j++){
            if(viewMatrix->isInViewVolume(polys[i].verticies[j].GetMatrix()) != true){
               projFlag = false;  
            }
        }
        if(projFlag){//project as all verticies are in the view volume
             polys[i].Transform(projMatrix);
             if(polys[i].verticies[0].GetW() != 0){
                for(int j =0; j < polys[i].vertexCount; j++){
                    float x = polys[i].verticies[j].GetX();
                    float y = polys[i].verticies[j].GetY();
                    float z = polys[i].verticies[j].GetZ();
                    float w = polys[i].verticies[j].GetW();

                    polys[i].verticies[j].SetX(x/w);
                    polys[i].verticies[j].SetY(y/w);
                    polys[i].verticies[j].SetZ(z/w);
                    polys[i].verticies[j].SetW(w/w);

                 }
             }
        }
    }

    for(int i = 0; i < faceCount; i++){
        //for each vertex
        //convert to world space
        //convert to view space
        //project
        //viewMatrix->isInViewVolume();
        
    }
}

int main(){
    // int shape = 0;
    // int mesh = 0;
    //int worldSpace[DEFAULT_X][DEFAULT_Y][DEFAULT_Z]; //haha this was so large it segfaulted my program
    ViewSpace *viewSpace;
    Shape* theShape;

    //setup scene, so d and f and whatnot
    viewSpace = new ViewSpace();
    
    
    //get input of what shape and mesh type are desired
    //GetInput(&shape, &mesh);
    //build 3d shape based on input specifications
    theShape = MakeAShape(0, 0); // just gonna make a cube for now no need for input
    cout << "Cube verticies before being projected to the view plane\n";
    theShape->Print();
    //Place shape in world space,, maybe move it around a smidge
    ModelViewProjection(viewSpace, theShape);
    //[View To Projection]x[World To View]x[Model to World]=[ModelViewProjectionMatrix].
    cout << "Cube verticies after being projected to the view plane\n";
    theShape->Print();

    return 0;    
}