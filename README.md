# Matrices
This library allows the program to perform some common matrix operations.

## Supported Operations
- Multiply a scalar
- Check if the matrix is a square matrix
- Multiply two matrices
- Transpose a matrix
- Perform row and column transforms
- Compute the minor of an element
- Compute cofactor matrix
- Compute adjugate matrix
- Compute the inverse matrix
- Compute the determinant

## Usage
There are no external dependencies. This only uses standard C libraries.
Just include the 'matrices.h' file as:
```c
#include "matrices.h"
```
After this, you can use the functions. All matrices are to be declared as matrix_t type which is a structure defined as:
```c
struct matrix{
	double** mat;
	int row; // This is the number of rows in the matrix
	int col; // This is the number of columns in the matrix
};

typedef struct matrix matrix_t;
```
## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
## Licence
[GNU Lesser General Public License v3.0](https://www.gnu.org/licenses/lgpl-3.0.en.html)
