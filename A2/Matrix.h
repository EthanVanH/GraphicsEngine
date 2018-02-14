/* Matrix.h is a header file that contains the definition of a matrix object and several useful matrix operations
 * A matrix is defined by its size, in rows and columns
 * 
 * Written for Graphics mathematics
 * Ethan VanHoutven
*/
#ifndef matrix
#define matrix
#include <iostream>
using namespace std;    


class Matrix {
    
    public:
        int rows;
        int columns;
        float **m;
        Matrix(int r, int c);
        void MInsertColumn(float *col, int index);
        Matrix* MMultiply(Matrix* m2);
        Matrix* MAdd(Matrix* m2);
        void Print();
};

#endif