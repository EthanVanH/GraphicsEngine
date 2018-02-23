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
            cout << "Creating Cube\n";
            return theShape = new Cube(mesh,1);
        break;
        case CYLINDER:
            printf("Creating cylinder\n");
            return theShape = new Cylinder(TRIANGLE,RESOLUTION_DEFAULT);

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

bool onSegment(int p1[2], int p2[2], int p3[2]){
    if (p2[0] <= max(p1[0], p3[0]) && 
    p2[0] >= min(p1[0], p3[0]) && 
    p2[1] <= max(p1[1], p3[1]) && 
    p2[1] >= min(p1[1], p3[1])){
        return true;
    }
    return false;

}


int orientation(int p1[2], int p2[2], int p3[2]){
    int val = (p2[1] - p1[1]) * (p3[0] - p2[0]) -
              (p2[0] - p1[0]) * (p3[2] - p2[2]);
 
    if (val == 0){
        return 0; 
    } // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}


bool doIntersect(int p1[2], int p2[2], int p3[2], int p4[2]){
    int ori1 = orientation(p1, p2, p3);
    int ori2 = orientation(p1, p2, p4);
    int ori3 = orientation(p3, p4, p1);
    int ori4 = orientation(p3, p4, p2);

    // General case
    if (ori1 != ori2 && ori3 != ori4){
        return true;
    }
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (ori1 == 0 && onSegment(p1, p2, p3)){
        return true;
    }
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (ori2 == 0 && onSegment(p1, p2, p4)){ 
        return true;
    }
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (ori3 == 0 && onSegment(p2, p1, p4)){ 
        return true;
    }
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (ori4 == 0 && onSegment(p2, p2, p4)){ 
        return true; 
    }
 
    return false;
}


bool isInside(int n, int **poly, int x, int y){
    int count;
    int i;
    int p[2];
    int ex[2];

    if(n < 3){
        return false;
    }
    
    ex[0] = 999999; // this is just the point at infinity
    ex[1] = y;

    p[0] = x;
    p[1] = y;
    
    count = 0;
    i = 0;
    do{
        int orient = (i + 1)%n;
        if(doIntersect(poly[i],poly[orient], p, ex)){
            if(orientation(poly[i], p, poly[orient]) == 0){
                return onSegment(poly[i], p, poly[orient]);
            }
            count++;
        }
        i = orient;
    }
    while (i != 0);
    return count%2 == 1;
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

void DrawToImage(Shape **shape, int shapeCount){
    Matrix *imageMatrix;
    Image *image;
    int **poly;
    image = new Image();

    float M = float(DEFAULT_RES);

    float xproj[4] = {0.0, -1*(M/2), 0.0, M/2 - 0.5f};
    float yproj[4] = {M/2, 0.0, 0.0, M/2 - 0.5f};
    float zproj[4] = {0.0, 0.0, 0.0, 1.0}; //puts z in the range 0 to 1, 0 for neaer plane 1 for far
    imageMatrix = new Matrix(4,3);
    imageMatrix->MInsertColumn(xproj, 0);
    imageMatrix->MInsertColumn(yproj, 1);
    imageMatrix->MInsertColumn(zproj, 2);
    cout << "The screen to image transformation matrix is \n";
    imageMatrix->Print();

    for(int s = 0; s < shapeCount; s++){
        Polygon *polys = shape[s]->GetFaces();

        int vpf = shape[s]->GetNumVertPFace();

        poly = new int *[vpf];
        for(int i = 0; i < vpf; i++){
            poly[i] = new int[2];
        }

        

        for(int i = 0; i < shape[s]->GetNumFaces(); i++){
            polys[i].Transform(imageMatrix);
            for(int j = 0; j < polys->vertexCount; j++){
                if(polys[i].verticies[j].inView != true){
                    break;
                }
                if(polys[i].verticies[j].GetW() != 0){
                    // float x = polys[i].verticies[j].GetX();
                    // float y = polys[i].verticies[j].GetY();
                    // float w = polys[i].verticies[j].GetW();
                    // /*Theres an issue at the axis here I need to check if any of the above are 0*/
                    // /*If they ARE zero i need to set the result as zero instead of inf or +inf */
                    // polys[i].verticies[j].SetX(x*w);
                    // polys[i].verticies[j].SetY(y*w);
                    // polys[i].verticies[j].SetW(w*w);
                }
                int row = int(polys[i].verticies[j].GetX()*1000 + 0.5);
                int col = int(polys[i].verticies[j].GetY()*1000 + 0.5);
                poly[j][0] = row + (s + 1)*100; //moving these points here... I shouldnt but it was tiny 
                poly[j][1] = col + (s + 1)*100;
                // cout << row << " " << col << '\n';
                image->img[(s + 1)*100 + row][(s + 1)*100 + col][0] = polys[i].colour[0];
                image->img[(s + 1)*100 + row][(s + 1)*100 + col][1] = polys[i].colour[1];
                image->img[(s + 1)*100 + row][(s + 1)*100 + col][2] = polys[i].colour[2];
                //Points now in the form pi = {r,c,0,1}
            }
            /*IF any point falls inside the polygon most recently put into the image colour it the polygon colour*/
            for(int j = 0; j < 500; j++){
                for(int k = 0; k < 500; k++){
                    if(isInside(vpf, poly, j, k)){
                        cout << "Colouring\n";
                        image->img[j][k][0] = polys[i].colour[0];
                        image->img[j][k][1] = polys[i].colour[1];
                        image->img[j][k][2] = polys[i].colour[2];
                    }
                }
            }
        }
    }
    OutputImage(image);
}

void ModelViewProjection(ViewSpace *viewMatrix, Shape *shape){
    static int whichShape = 0;
    bool projFlag;
    int faceCount = shape->GetNumFaces();
    int vpf = shape->GetNumVertPFace();
    Polygon *polys = shape->GetFaces();
    WorldSpace *world;
    
    Matrix *projMatrix;
    cout << "1\n";
    /*Some quick bs for multiple shapes with minimal work*/
    if(whichShape == 0){
        world = new WorldSpace(100, 0, 0);
        whichShape++;
    }else if(whichShape == 1){
        world = new WorldSpace(0, 100, 0);
        whichShape++;
    }
    else{
        world = new WorldSpace(50, 3);//rotate on z axis
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
    float zproj[4] = {0.0, 0.0, f/(f-d), -1*(f*d)/f-d}; //puts z in the range 0 to 1, 0 for neaer plane 1 for far
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
               projFlag = false;  //AGH, NOTHING IS IN VIEW VOLUME AGAIN.TODO
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
    theShape[0] = MakeAShape(0, 0); // just gonna make a cube for now no need for input
    theShape[1] = MakeAShape(0, 0);
    theShape[2] = MakeAShape(0, 0);
    cout << "Cube verticies before being projected to the view plane\n";
    theShape[0]->Print();
    //Place shape in world space,, maybe move it around a smidge
    ModelViewProjection(viewSpace, theShape[0]);
    ModelViewProjection(viewSpace, theShape[1]);
    ModelViewProjection(viewSpace, theShape[2]);
    cout << "Shapes done modeling\n";
    theShape[0]->Print();
    cout << "---------------------------------\n";
    theShape[1]->Print();
    cout << "---------------------------------\n";
    theShape[2]->Print();
    cout << "---------------------------------\n";

    DrawToImage(theShape, 3);
    //[View To Projection]x[World To View]x[Model to World]=[ModelViewProjectionMatrix].

    return 0;    
}