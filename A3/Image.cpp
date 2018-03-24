/*REAL QUICK*/
/*Implementation of an image class that stores a 3d array */
/*Being an array of colours at x y coordinates*/
/*also dda algorithm for drawing lines between points*/

#include "Image.h"

Image::Image(){
    for(int i = 0; i < DEFAULT_RES; i++){
        for(int j = 0; j < DEFAULT_RES; j++){
            for(int k = 0; k < 3; k++){
                img[i][j][k] = 125;
            }
        }
    }
}

void Image::DDA(Point* points, int numpoints){
    Point One;
    Point Two;
    float dx;
    float dy;
    float step;
    int nx;
    int ny;

    for(int i = 0; i < numpoints; i++){
        One = points[i];
        for(int j = i + 1; j < numpoints; j++){
            Two = points[j];
            dx = abs(Two.x - One.x);
            dy = abs(Two.y - One.y);

            if(dx >= dy){
                step = dx;
            }else{
                step = dy;
            }

            dx = dx/step;
            dy = dy/step;
        
            nx = One.x;
            ny = One.y;

            for(int k = 0; k < step; k ++){
                img[nx][ny][0] = One.r;
                img[nx][ny][1] = One.g;
                img[nx][ny][2] = One.b;

                nx += round(dx);
                ny += round(dy);
            }
        }
    }
}