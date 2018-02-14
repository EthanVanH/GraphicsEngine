/* 
 * Implementation of the m class
 * Ethan VanHoutven
*/

#include "Matrix.h"

Matrix::Matrix(int r, int c){
    rows = r;
    columns = c;
    m = new float*[r];
    for(int i = 0; i < r; i++){
        m[i] = new float[c];
    }

}

void Matrix::MInsertColumn(float *col, int index){
    for(int i = 0; i < rows; i++){
        m[index][i] = col[i];
    }
}

Matrix* Matrix::MAdd(Matrix* m2){
    Matrix *sum = new Matrix(rows, columns);
    for(int i = 0; i < rows; i++){
	    for(int j = 0; j < columns; j++){
	        sum->m[i][j] = m[i][j] + m2->m[i][j]; 
	    } 
    }

    return sum;
}

//makes terrible assumption that the matricies are the same size
Matrix* Matrix::MMultiply(Matrix *m2){ // NOTE THAT MATRIX IS THE FORM x[COL][ROW] as i am dumb
    Matrix *Product = new Matrix(rows, m2->columns);
    for(int i = 0; i < rows; ++i){
	    for(int j = 0; j < m2->columns; ++j){
	        for(int k = 0; k < columns; ++k){

                Product->m[j][i] += m[i][k] * m2->m[j][k];
	        }
	    }
    }
    return Product;
}

void Matrix::Print(){
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            cout << m[i][j];
            cout << ' ';
        }
        cout << '\n';
    }
}

