/*REAL QUICK*/
/*Implementation of an image class taht just stores a 3d array*/

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