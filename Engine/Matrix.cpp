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

Matrix::Matrix(int r, int c, float **array){
    rows = r;
    columns = c;
    m = array;
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

Matrix* Matrix::Invert(){
    float **invertedM;

    invertedM = new float*[rows];
    for(int i = 0; i < rows; i++){
        invertedM[i] = new float[columns];
    }

    float determinant = 0.0;

    for(int i = 0; i < columns; i++){
        cout << "asd ";
        determinant +=  (m[0][i] * (m[1][(i+1)%3] * m[2][(i+2)%3] - m[1][(i+2)%3] * m[2][(i+1)%3]));
    }

    cout << "Determinant " << determinant << "\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            invertedM[i][j] = ((m[(j+1)%3][(i+1)%3] * m[(j+2)%3][(i+2)%3]) - (m[(j+1)%3][(i+2)%3] * m[(j+2)%3][(i+1)%3]))/ determinant; 
            cout << invertedM[i][j] << "\t";
        }
        cout << "\n";
    }
    Matrix *Inverted = new Matrix(rows,columns,invertedM);
    return Inverted;
}


Matrix Matrix::MMultiply(Matrix *m2){ // NOTE THAT MATRIX IS THE FORM x[COL][ROW] as i am dumb
    Matrix Product = Matrix(rows, m2->columns);
    //  Print();
    //  cout << "^ Multiplying by below\n";
    //  m2->Print();
    for(int i = 0; i < rows; ++i){
	    for(int j = 0; j < m2->columns; ++j){
	        for(int k = 0; k < columns; ++k){
                
                Product.m[j][i] += m[i][k] * m2->m[j][k];
	        }
	    }
    }
    //  cout << "Resulting in ..\n";
    //  Product.Print();
    //  cout << "----------\n";
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

