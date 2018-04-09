/*REAL QUICK*/
/*Implementation of an image class that stores a 3d array */
/*Being an array of colours at x y coordinates*/
/*also dda algorithm for drawing lines between points*/

#include "Image.h"

Image::Image(){
    for(int i = 0; i < DEFAULT_RES; i++){
        for(int j = 0; j < DEFAULT_RES; j++){
            for(int k = 0; k < 3; k++){
                img[i][j][k] = DEFAULT_BACKGROUND;
            }
        }
    }
}

void Image::DDA(Point* points, int numpoints){
    Point One;
    Point Two;
    float dx;
    float dy;
    float end;
    float nx;
    float ny;
    
    
    for(int i = 0; i < numpoints; i++){
        One = points[i];
        
        for(int j = i + 1; j < numpoints; j++){
            Two = points[j];
            // cout << "Point x:" << One.x << " y:" << One.y << "\n";
            // cout << "To \n";
            // cout << "Point x:" << Two.x << " y:" << Two.y << "\n";
            dx = abs(Two.x - One.x);
            dy = abs(Two.y - One.y);

            if(dx >= dy){
                end = dx;
            }else{
                end = dy;
            }
            
            dx = dx/end;
            dy = dy/end;
            
            nx = min(One.x, Two.x);
            ny = min(One.y, Two.y);
            
            // cout << "End is " << end << "\n";
            // cout << "dx" << dx << "\n";
            // cout << "dy" << dy << "\n";
            // cout << "nx" << nx << "\n";
            // cout << "ny" << ny << "\n";

            for(int k = 0; k < end; k++){
                int x = round(nx);
                int y = round(ny);
                img[x][y][0] = One.r;
                img[x][y][1] = One.g;
                img[x][y][2] = One.b;

                nx += dx;
                ny += dy;
            }
        }
    }
}