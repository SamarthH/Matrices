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

matrix_t* multiply(const matrix_t* mat1, const matrix_t* mat2);

matrix_t* transpose(const matrix_t* to_transpose);

void row_transform(matrix_t* to_transform, int row1, char oper, int row2, double k); // this causes change of form row1 -> row1 (oper) row2 
																			//where oper is + or -

void col_transform(matrix_t* to_transform, int col1, char oper, int col2, double k); // this causes change of form col1 -> col1 (oper) col2
																		//	where oper is + or -

double determinant(const matrix_t* to_find);

void input(matrix_t* to_fill);

void remove_row(matrix_t* to_remove, int row);

void remove_col(matrix_t** to_remove, int col);

double find_minor(const matrix_t* to_find, int row, int col); //Finds minor of element (row,col) of the matrix_t

matrix_t* cofactor_matrix_t(const matrix_t* to_find);

matrix_t* adjoint(const matrix_t* to_find);

matrix_t* inverse(const matrix_t* to_find);

void solve_linear(const matrix_t* coeff, double* sol, const double* equal);
// To use this, give coefficient matrix, matrix in which solutions must be stored, array of equalities and number of variables.
// equality means a[i]*var[0] + b[i]*var[1] + c[i]*var[2] + ... = equal[i]

#endif