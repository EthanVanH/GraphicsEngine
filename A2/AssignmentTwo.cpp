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

void WorldTransforms(Shape *shape){

}


void DrawToImage(Shape *shape){
    Matrix *imageMatrix;
    Polygon *polys = shape->GetFaces();

    int* image = new int[500*500*3];
    float M = 500;

    float xproj[4] = {0.0, -1*(M/2), 0.0, M/2 - 0.5f};
    float yproj[4] = {M/2, 0.0, 0.0, M/2 - 0.5f};
    float zproj[4] = {0.0, 0.0, 0.0, 1.0}; //puts z in the range 0 to 1, 0 for neaer plane 1 for far

    imageMatrix = new Matrix(4,3);
    imageMatrix->MInsertColumn(xproj, 0);
    imageMatrix->MInsertColumn(yproj, 1);
    imageMatrix->MInsertColumn(zproj, 2);

    

    for(int i = 0; i < shape->GetNumFaces(); i++){
        polys[i].Transform(imageMatrix);
        for(int j = 0; j < polys->vertexCount; j++){
            if(polys[i].verticies[j].inView != true){
                break;
            }
            int row = int(polys[i].verticies[j].GetX() + 0.5);
            int col = int(polys[i].verticies[j].GetY() + 0.5);
            printf("Suspect 1 %d %d\n",row,col); //TODO fix this. 
            image[row + col] = polys[i].colour[0];
            image[row + col + 1] = polys[i].colour[1];
            image[row + col + 2] = polys[i].colour[2];

            printf("image at %d %d is %d\n",row, col, *polys[i].colour);
        }
    }
    //Points now in the form pi = {r,c,0,1}
    delete[] image;
}

void ModelViewProjection(ViewSpace *viewMatrix, Shape *shape){
    bool projFlag;
    int faceCount = shape->GetNumFaces();
    int vpf = shape->GetNumVertPFace();
    Polygon *polys = shape->GetFaces();
    WorldSpace *world = new WorldSpace();
    Matrix *projMatrix;
    
    /*Creation of projecton matrix
     * Of form
     * d 0 0 0
     * 0 d 0 0
     * 0 0 d 0
     * 0 0 1 0
     * Where d is the z value representing the near plane of the view volume
    */
    WorldTransforms(shape);

    float d = viewMatrix->d; // just shorthanding these so i dont need to deal with it
    float f = viewMatrix->f;
    float h = viewMatrix->h;

    float xproj[4] = {d/h, 0.0, 0.0, 0.0};
    float yproj[4] = {0.0, d/h, 0.0, 0.0};
    float zproj[4] = {0.0, 0.0, f/(f-d), -1*(f*d/f-d)}; //puts z in the range 0 to 1, 0 for neaer plane 1 for far
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
        polys[i].Transform(world->Space);
        polys[i].Transform(viewMatrix->Space);
        projFlag = true;
        for(int j = 0; j < vpf; j++){
            if(viewMatrix->isInViewVolume(polys[i].verticies[j].GetMatrix()) != true){
               projFlag = false;  //AGH, NOTHING IS IN VIEW VOLUME AGAIN. FUCK. TODO
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

                    polys[i].verticies[j].SetInView();

                    polys[i].verticies[j].SetX(x/w);
                    polys[i].verticies[j].SetY(y/w);
                    polys[i].verticies[j].SetZ(z/w);
                    polys[i].verticies[j].SetW(w/w);

                 }
             }
        }
        DrawToImage(shape);
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