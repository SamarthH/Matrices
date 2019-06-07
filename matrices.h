//All matrices must be stored as double**
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef MATRICES_H
#define MATRICES_H
struct matrix{
	double** mat;
	int row;
	int col;
};

typedef struct matrix matrix_t;

void init(matrix_t* to_init); //Initializes a matrix_t with a known no. of rows and colums to a null matrix_t(including allocation)

void copy(const matrix_t* from, matrix_t* to); // Copies matrix 'from' to the matrix 'to'

void delete_mat(matrix_t* to_delete); // Deletes the matrix 'to_delete'

void print(const matrix_t* to_print);

void multiply_scalar(matrix_t* mat1, double k);

int check_square(const matrix_t* to_check);

matrix_t* multiply(const matrix_t* mat1, const matrix_t* mat2); // This returns [mat1]*[mat2]

matrix_t* transpose(const matrix_t* to_transpose); // This returns the transpose of the matrix

void row_transform(matrix_t* to_transform, int row1, char oper, int row2, double k); 
// This causes change of form row1 -> row1 (oper) row2 where oper is '+', '-', or 'c'.
// '+'/'-' => This changes row1 as row1 = row1 +/- k*row2;
// 'c' => This exchanges the pointers to row1 and row2

void col_transform(matrix_t* to_transform, int col1, char oper, int col2, double k); 
// Same as the row_transform but for columns

double determinant(const matrix_t* to_find); // Computes the determinant of the given matrix.
// This exits with code -1 if given matrix is not a square matrix

void input(matrix_t* to_fill);
// This takes the input for the matrix from the user.
// This first takes two integers i.e. number of rows and columns respectively
// Then it takes row*columns doubles and fills them row-wise.

void remove_row(matrix_t* to_remove, int row); // This deletes the 'row'th row from the matrix

void remove_col(matrix_t** to_remove, int col); // This deletes the 'col'th column from the matrix

double find_minor(const matrix_t* to_find, int row, int col); //Finds minor of element (row,col) of the matrix_t

matrix_t* cofactor_matrix_t(const matrix_t* to_find); // This function returns the cofactor matrix

matrix_t* adjoint(const matrix_t* to_find); // This function returns the adjoint of the matrix

matrix_t* inverse(const matrix_t* to_find); // This returns the inverse of the matrix

void solve_linear(const matrix_t* coeff, double* sol, const double* equal);
// To use this, give coefficient matrix, matrix in which solutions must be stored and array of equalities respectively.
// equality means coeff->mat[i][0] * sol[0] + coeff->mat[i][1] * sol[1] + ... == equal[i] 
//The number of variables is taken to be equal to the number of columns in the coeff matrix

#endif
