//All matrices must be stored as double**
#include "matrices.h"

void init(matrix_t* to_init){
	to_init->mat = (double**) malloc(to_init->row*sizeof(double*));
	for(int i=0; i<to_init->row; i++){
		to_init->mat[i] = (double*) malloc(to_init->col*sizeof(double));
		for(int j=0; j<to_init->col; j++){
			to_init->mat[i][j] = 0;
		}
	}
}

void copy(const matrix_t* from, matrix_t* to){
	to->row = from->row;
	to->col = from->col;
	init(to);
	for (int i = 0; i < to->row; ++i)
	{
		for (int j = 0; j < to->col; ++j)
		{
			to->mat[i][j] = from->mat[i][j];
		}
	}
}

void delete_mat(matrix_t* to_delete){
	if(to_delete == NULL){
		exit(-3);
	}
	for (int i = 0; i < to_delete->row; ++i)
	{
		free(to_delete->mat[i]);
	}
	free(to_delete->mat);
}

void print(const matrix_t* to_print){
	if(to_print == NULL){
		printf("INVALID");
		exit(-2);
	}
	printf("\n");
	for (int i = 0; i < to_print->row; ++i)
	{ 
		for (int j = 0; j < to_print->col; ++j)
		{
			printf("%.4lf\t",to_print->mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void multiply_scalar(matrix_t* mat1, double k){
	for (int i = 0; i < mat1->row; ++i)
	{
		for (int j = 0; j < mat1->col; ++j)
		{
			mat1->mat[i][j] = k*mat1->mat[i][j];
		}
	}
}

matrix_t* multiply(const matrix_t* mat1, const matrix_t* mat2){
	if(mat1->col != mat2->row){
		return NULL;
	}
	matrix_t* new = malloc(sizeof(matrix_t));
	new->row = new->col = 0;
	new->row = mat1->row;
	new->col = mat2->col;
	init(new);
	for(int i=0 ; i<mat1->row; i++){
		for(int j=0; j<mat2->col; j++){
			for(int k=0; k<mat1->col; k++){
				new->mat[i][j] = (mat1->mat)[i][k]*(mat2->mat)[k][j];
			}
		}
	}
	return new;
}

matrix_t* transpose(const matrix_t* to_transpose){
	matrix_t* temp = malloc(sizeof(matrix_t));
	temp->row = to_transpose->col;
	temp->col = to_transpose->row;
	init(temp);
	for (int i = 0; i < to_transpose->col; ++i)
	{
		for (int j = 0; j < to_transpose->row; ++j)
		{
			temp->mat[i][j] = to_transpose->mat[j][i];
		}
	}
	return temp;
}

int check_square(const matrix_t* to_check){
	if(to_check->row == to_check->col){
		return 1;
	}
	return 0;
}

void row_transform(matrix_t* to_transform, int row1, char oper, int row2, double k){
	if(row1 == row2 || row1 >= to_transform->row ||row2 >= to_transform->row){
		exit(-4);
	}
	switch (oper)
	{
		case '+':
		{
			for (int i = 0; i < to_transform->col; ++i)
			{
				to_transform->mat[row1][i] += k*(to_transform->mat[row2][i]); 
			}
		}break;

		case '-':
		{
			for (int i = 0; i < to_transform->col; ++i)
			{
				to_transform->mat[row1][i] -= k*(to_transform->mat[row2][i]); 
			}
		}break;

		case 'c':
		{
			double* temp = to_transform->mat[row1];
			to_transform->mat[row1] = to_transform->mat[row2];
			to_transform->mat[row2] = temp;
		}break;
	}
}

void col_transform(matrix_t* to_transform, int col1, char oper, int col2, double k){
	if(col1 == col2 || col1 >= to_transform->col ||col2 >= to_transform->col){
		exit(-5);
	}
	switch (oper)
	{
		case '+':
		{
			for (int i = 0; i < to_transform->row; ++i)
			{
				to_transform->mat[i][col1] += k*to_transform->mat[i][col2]; 
			}
		}break;

		case '-':
		{
			for (int i = 0; i < to_transform->row; ++i)
			{
				to_transform->mat[i][col1] -= k*to_transform->mat[i][col2]; 
			}
		}break;

		case 'c':
		{
			//To make better
			matrix_t* temp;
			temp = transpose(to_transform);
			row_transform(to_transform,col1,'c',col2,0);
			to_transform = transpose(temp);
			delete_mat(temp);
			free(temp);
			//Not the best method BUT I am lazy
		}break;
	}
}

double determinant(const matrix_t* to_find){
	if(!check_square(to_find)){
		exit(-1) ;
	}
	//First create upper triangular matrix_t
	matrix_t temp;
	copy(to_find,&temp);
	matrix_t temp2;
	copy(&temp,&temp2);
	int count=0;
	for (int i = 0; i < temp.row-1 && temp.mat[i][i] != 0; ++i)
	{
		for(int j = i+1; j< temp.col; j++){
			row_transform(&temp,j,'-',i,(temp.mat[j][i])/(temp.mat[i][i]));
		}
		count++;
	}
	if(count != temp.row -1){
		for (int i = 0; i < temp.row; ++i)
		{
			if(temp.mat[i][i] == 0 /*&& to_find->mat[i][i] != 0 */&& i != temp.row - 1){
				int change;
	//			change = (rand())%(temp2.row);
				change = (rand())%i;
	/*			change = i+1;
	*/			row_transform(&temp2,i,'c',change,0);
				double det = determinant(&temp2);
				delete_mat(&temp2);
				delete_mat(&temp);
				return det;
			}
		}
	}
	if(temp.mat[(temp.row)-1][(temp.row)-1] == 0){
		return 0;
	}
	double det = 1;
	for (int i = 0; i < temp.row; ++i)
	{
		det = det*temp.mat[i][i];
	}
	delete_mat(&temp);
	delete_mat(&temp2);
	return det;
}

void input(matrix_t* to_fill){
	scanf("%d%d",&(to_fill->row),&(to_fill->col));
	init(to_fill);
	for (int i = 0; i < to_fill->row; ++i)
	{
		for (int j = 0; j < to_fill->col; ++j)
		{
			scanf("%lf",&(to_fill->mat[i][j]));
		}
	}
}

void remove_row(matrix_t* to_remove, int row){
	for (int i = row; i < (to_remove->row)-1; i++)
	{
		to_remove->mat[i] = to_remove->mat[i+1];
	}
	free((to_remove->mat[((to_remove->row)--)]));
}

void remove_col(matrix_t** to_remove, int col){
	matrix_t* tem;
	tem = transpose(*to_remove);
	delete_mat(*to_remove);
	remove_row(tem,col);
	*to_remove = transpose(tem);
	delete_mat(tem);
	free(tem);
}

double find_minor(const matrix_t* to_find, int row, int col){
	matrix_t temp;
	copy(to_find,&temp);
	matrix_t* temp2 = &temp;
	remove_row(temp2,row);
	remove_col(&temp2,col);
	double minor = determinant(temp2);
	delete_mat(&temp);
	return minor;
}

matrix_t* cofactor_matrix_t(const matrix_t* to_find){
	matrix_t* cof = malloc(sizeof(matrix_t));
	cof->row = to_find->row;
	cof->col = to_find->col;
	init(cof);
	for (int i = 0; i < cof->row; ++i)
	{
		for (int j = 0; j < cof->col; ++j)
		{
			cof->mat[i][j] = pow(-1,i+j)*find_minor(to_find,i,j);
		}
	}
	return cof;
}

matrix_t* adjoint(const matrix_t* to_find){
	matrix_t* temp = cofactor_matrix_t(to_find);
	matrix_t* adjoint = transpose(temp);
	delete_mat(temp);
	free(temp);
	return adjoint; 
}

matrix_t* inverse(const matrix_t* to_find){
	matrix_t* inverse = adjoint(to_find);
	double det = determinant(to_find);
	if(det){
		multiply_scalar(inverse,(1.0/det));
		return inverse;
	}
	return NULL;
}

void solve_linear(const matrix_t* coeff, double* sol, const double* equal){
	int numvar = coeff->col;
	if(coeff->row < numvar){
		exit(-1);
	}
	//Creating Upper Triangular Matrix Equivalent
		matrix_t temp;
		copy(coeff,&temp);
	//	matrix_t temp2;
	//	copy(&temp,&temp2);
		double* tempequal = (double*) malloc((coeff->row)*sizeof(double));
		for (int l = 0; l < coeff->row; ++l)
		{
			tempequal[l] = equal[l];
		}
		int i;
		for (i = 0; i < temp.col && temp.mat[i][i] != 0; i++)
		{
			for(int j = i+1; j< temp.row; j++){
				double factor = (temp.mat[j][i])/(temp.mat[i][i]);
				row_transform(&temp,j,'-',i,factor);
				tempequal[j] = tempequal[j] - factor*tempequal[i];
			}
		}
		if(i != temp.row){
			for (int k = 0; k < temp.row; ++k)
			{
				if(temp.mat[k][k] == 0 && k != temp.row - 1){
					int change;
					change = (rand())%(temp.row);
					row_transform(&temp,k,'c',change,0);
					double tempswap = tempequal[k];
					tempequal[k] = tempequal[change];
					tempequal[change] = tempswap;
					solve_linear(&temp,sol,equal);
					free(tempequal);
					delete_mat(&temp);
					return;
				}
			}
		}
		if(temp.mat[i-1][i-1] == 0){
			if(tempequal[i-1] == 0){
				printf("INFINITE SOLUTIONS");
				exit(-3);
			}
			else{
				printf("NO SOLUTION");
				exit(-4);
			}
		}
	//Done
	if(0)
	{
		print(&temp);
		for (int j = 0; j < coeff->row; ++j)
		{
			printf("%lf\n",tempequal[j]);
		}
	}
	for (int j = numvar; j < temp.row; ++j)
	{
		if(tempequal[j]){
			printf("INCONSISTENT EQUATIONS");
			delete_mat(&temp);
		//	delete_mat(&temp2);
			free(tempequal);
			exit(-5);
		}
	}
	for (int j = numvar-1; j >= 0; j--)
	{
		sol[j] = tempequal[j];
		for (int k = j+1; k < numvar; ++k)
		{
			sol[j] = sol[j] - (sol[k])*(temp.mat[j][k]);
		}
		sol[j] = (sol[j])/(temp.mat[j][j]);
	}
	delete_mat(&temp);
	//delete_mat(&temp2);
	free(tempequal);
}