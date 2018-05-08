/* CIS*4800 Computer Graphics
 * Assignment 4
 * Written By: Ethan Van Houtven
 * This assignment covers the basics of setting up a scene for 3d graphics
 * Inluding the view space, world space and prospective projection
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
using namespace std;

#define DEMO
#define TESTING    

//#include "shader.hpp"
#include "ShapeDefinitions.h"
#include "Primatives.h"
#include "Image.h"
#include "Matrix.h"
#include "Scene.h"


bool isShape(int posibleShape){
    if(posibleShape < 0 || posibleShape > 6){
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
            #ifdef DEMO
            cout << "Creating Cube\n";
            #endif

            return theShape = new Cube(mesh,1);
        break;
        case CYLINDER:
            #ifdef DEMO
            cout << "Creating cylinder\n";
            #endif

            return theShape = new Cylinder(TRIANGLE,RESOLUTION_DEFAULT);

        break;
        case CONE:
            //CreateCone(mesh);
            #ifdef DEMO
            cout << "Sorry this shape has not yet been implemented\n";
            cout << "Making a cube instead\n";
            #endif

            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        case SPHERE:
            //CreateSphere(mesh);
            #ifdef DEMO
            cout << "Sorry this shape has not yet been implemented\n";
            cout << "Making a cube instead\n";
            #endif 

            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        case TUBE:
            //CreateTube(mesh);
            #ifdef DEMO
            cout << "Sorry this shape has not yet been implemented\n";
            cout << "Making a cube instead\n";
            #endif

            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        case TORUS:
            //CreateTorus(mesh);
            #ifdef DEMO
            cout << "Sorry this shape has not yet been implemented\n";
            cout << "Making a cube instead\n";
            #endif

            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
        default:
            #ifdef DEMO
            cout << "This is not a supported shape\n";
            cout << "Making a cube instead\n";
            #endif

            return theShape = new Cube(mesh,RESOLUTION_DEFAULT);
        break;
    }
    return theShape;
}


void OutputImage(Image *m){
    FILE *fp;
    int hw = int(DEFAULT_RES);
    fp = fopen("output.ppm", "w");
    fprintf(fp, "P6\n%d %d 255\n", hw, hw);
    for(int i = 0; i < hw; i++){
        for(int j = 0; j <hw; j++){
            fputc(m->img[i][j][0], fp);
            fputc(m->img[i][j][1], fp);
            fputc(m->img[i][j][2], fp);
          }
    }
    fclose(fp);
}

void DrawToImage(Shape **shape, int shapeCount, ViewSpace *vs){
    Matrix *imageMatrix;
    Image *image;
    image = new Image();
    bool skip;

    float M = float(DEFAULT_RES);
    float h = float(vs->h);
    float xproj[4] = {0.0, -1*(M/2*h), 0.0, M/2 - 0.5f};
    float yproj[4] = {M/2*h, 0.0, 0.0, M/2 - 0.5f};
    float zproj[4] = {0.0, 0.0, 0.0, vs->d};
    float wproj[4] = {0.0, 0.0, 0.0, 1.0}; 

    imageMatrix = new Matrix(4,4); //puts z in the range 0 to 1, 0 for near plane 1 for far
    imageMatrix->MInsertColumn(xproj, 0);
    imageMatrix->MInsertColumn(yproj, 1);
    imageMatrix->MInsertColumn(zproj, 2);
    imageMatrix->MInsertColumn(wproj, 3);
    
    #ifdef DEMO
    cout << "The screen to image transformation matrix is \n";
    imageMatrix->Print();
    #endif

    for(int s = 0; s < shapeCount; s++){
        Polygon *polys = shape[s]->GetFaces();
        
        for(int i = 0; i < shape[s]->GetNumFaces(); i++){
            // cout << "Poly at i\n";
            // polys[i].Print();
            skip = false;
            polys[i].Transform(imageMatrix);
            Point* points = new Point[polys[i].vertexCount];
            // cout << "imageified\n";
            // polys[i].Print();
            for(int j = 0; j < polys[i].vertexCount; j++){
                
                if(polys[i].isCulled()){
                    #ifdef DEMO
                    cout << "Not Drawing culled polygon " << i <<"\n";
                    polys[i].Print();
                    #endif
                    skip = true;
                    break;
                }
                if(polys[i].verticies[j].inView != true){
                    #ifdef DEMO
                    cout << "Not drawing vertex outside viewVolume\n";
                    cout << polys[i].verticies[j].GetX() << "  ";
                    cout << polys[i].verticies[j].GetY() << "  ";
                    cout << polys[i].verticies[j].GetZ() << "  ";
                    cout << polys[i].verticies[j].GetW() << "\n";
                    #endif
                    skip = true;
                    break;
                }

                
                int row = int(polys[i].verticies[j].GetX()); 
                int col = int(polys[i].verticies[j].GetY()); 
                Point p;
                p.x = ((s + 1) + row)%DEFAULT_RES; //s+1 *100 is a special case for the three object scene
                p.y = ((s + 1) + col)%DEFAULT_RES;
                p.z = polys[i].verticies[j].GetZ();

                p.r = polys[i].colour[0];
                p.g = polys[i].colour[1];
                p.b = polys[i].colour[2];
                points[j] = p;
                //cout << "I bet i segfault here\n" << (s + 1) + row << "   ---   " << (s + 1) + col << "\n";
                image->img[((s + 1) + row)%DEFAULT_RES][((s + 1) + col)%DEFAULT_RES][0] = polys[i].colour[0];
                image->img[((s + 1) + row)%DEFAULT_RES][((s + 1) + col)%DEFAULT_RES][1] = polys[i].colour[1];
                image->img[((s + 1) + row)%DEFAULT_RES][((s + 1) + col)%DEFAULT_RES][2] = polys[i].colour[2];
                //Points now in the form pi = {r,c,0,1}
                //cout << "I was wrong\n";
            }
            //Should draw a line between every rastorized point of a polygon
            if(!skip){
                image->Clip(points, polys[i].vertexCount, vs);
                image->DDA(points, polys[i].vertexCount);
            }
        }
    }
    OutputImage(image);
}

void ModelViewProjection(ViewSpace *viewMatrix, Shape *shape){
    static int whichShape = 0;
    bool projFlag;
    int faceCount = shape->GetNumFaces();
    int vpf;
    Polygon *polys = shape->GetFaces();
    WorldSpace *world;
    
    Matrix *projMatrix;
    /*Generates three different world space transformations so shapes will not occupy the same space*/
    if(whichShape == 0){
        world = new WorldSpace();
        whichShape++;
    }else if(whichShape == 1){
        world = new WorldSpace(0, 100, 0);
        whichShape++;
    }
    else{
        world = new WorldSpace(50, 3, 10);//rotate on z axis
        whichShape++;
    }
    /*Creation of projecton matrix
     * Of form
     * d/h 0 0 0
     * 0 d/h 0 0
     * 0 0 f/(f-d) -fd/f-d
     * 0 0 1 0
     * Where d is the z value representing the near plane of the view volume
    */
    float d = viewMatrix->d; // just shorthanding these so i dont need to deal with it
    float f = viewMatrix->f;
    float h = viewMatrix->h;

    float xproj[4] = {d/h, 0.0, 0.0, 0.0};
    float yproj[4] = {0.0, d/h, 0.0, 0.0};
    float zproj[4] = {0.0, 0.0, f/(f-d), -1*(f*d)/f-d}; //puts z in the range 0 to 1, 0 for near plane 1 for far
    float wproj[4] = {0.0, 0.0, 1.0, 0.0};

    projMatrix = new Matrix(4,4);
    projMatrix->MInsertColumn(xproj, 0);
    projMatrix->MInsertColumn(yproj, 1);
    projMatrix->MInsertColumn(zproj, 2);
    projMatrix->MInsertColumn(wproj, 3);

    #ifdef DEMO
    cout << "The projection matrix is \n";
    projMatrix->Print();
    #endif

    for(int i = 0; i < faceCount; i++ ){
        //transform
        polys[i].Transform(world->Space);
        polys[i].Transform(viewMatrix->Space);
        projFlag = true;
        vpf = polys[i].vertexCount;
        if(polys[i].vertexCount != polys[i].vertexInVV){
            polys[i].vertexInVV = polys[i].vertexCount;
        }
        for(int j = 0; j < vpf; j++){
            if(polys[i].verticies[j].GetW() != 1){
                float x = polys[i].verticies[j].GetX();
                float y = polys[i].verticies[j].GetY();
                float z = polys[i].verticies[j].GetZ();
                float w = polys[i].verticies[j].GetW();
                /*Theres an issue at the axis here I need to check if any of the above are 0*/
                /*If they ARE zero i need to set the result as zero instead of inf or +inf */
                polys[i].verticies[j].SetInView();
                polys[i].verticies[j].SetX(x/w);
                polys[i].verticies[j].SetY(y/w);
                polys[i].verticies[j].SetZ(z/w);
                polys[i].verticies[j].SetW(w/w);
            }
            
        }

        for(int j = 0; j < vpf; j++){
            if(viewMatrix->isInViewVolume(polys[i].verticies[j].GetMatrix()) != true){
               projFlag = false;
            }
        }
        if(projFlag){//project as all verticies are in the view volume
            polys[i].Transform(projMatrix);
        }
    }
}

int main(){
    // int shape = 0;
    // int mesh = 0;
    //int worldSpace[DEFAULT_X][DEFAULT_Y][DEFAULT_Z]; //haha this was so large it segfaulted my program
    ViewSpace *viewSpace;
    Shape* theShape[3];

    //setup scene, so d and f and whatnot
    viewSpace = new ViewSpace();
    
    //get input of what shape and mesh type are desired
    //GetInput(&shape, &mesh);
    //build 3d shape based on input specifications
    theShape[0] = MakeAShape(0, 1); // just gonna make a cube for now no need for input
    theShape[1] = MakeAShape(0, 0);
    theShape[2] = MakeAShape(0, 0);
    
    #ifdef DEMO
    cout << "Cube verticies before being projected to the view plane\n";
    theShape[0]->Print();
    //Place shape in world space,, maybe move it around a smidge
    #endif

    ModelViewProjection(viewSpace, theShape[0]);
    ModelViewProjection(viewSpace, theShape[1]);
    ModelViewProjection(viewSpace, theShape[2]);
    if(CULLING == true){
        viewSpace->Cull(theShape[0]);
        viewSpace->Cull(theShape[1]);
        viewSpace->Cull(theShape[2]);
    }
    #ifdef DEMO
    cout << "Shapes done modeling\n";
    theShape[0]->Print();
    cout << "--------------S1-------------------\n";
    theShape[1]->Print();
    cout << "--------------S2-------------------\n";
    theShape[2]->Print();
    cout << "--------------S3-------------------\n";
    #endif

    DrawToImage(theShape, 3, viewSpace);
    //[View To Projection]x[World To View]x[Model to World]=[ModelViewProjectionMatrix].

    return 0;    
}