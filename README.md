# MyOctave
Implementation of matrix operations
Copyright Gheorghe Marius Razvan 314CAa 2022-2023

==========Commands========

'L' - Load a matrix with given dimensions into memory
'D' - Display the dimensions of a matrix at the specified index
'P' - Print the matrix at the specified index
'C' - Resize a matrix at the specified index
'M' - Multiply two matrices at specified indices
'O' - Sort matrices in ascending order based on the sum of elements
'T' - Transpose the matrix at the specified index
'R' - Raise a matrix to a given power
'F' - Free the memory of a matrix at the specified index
'Q' - Free all allocated memory and terminate operations
'S' - Multiply two matrices using Strassen's algorithm
=='L'==

Dynamically allocates memory for the matrix to be read. Stores the matrix in a list along with its elements. Increases the total number of matrices with each new entry.

=='D'==

Displays the dimensions of the matrix at the specified index, showing the number of rows and columns.

=='P'==

Prints the matrix at the specified index. Extracts each element in turn from the matrix for display.

=='C'==

Receives the index of the matrix to be resized. Reads the indices for rows and columns, then performs the resizing operation. Allocates memory for the required rows and columns. Allocates memory for the newly formed matrix. Stores the new elements in the matrix. Deletes the matrix at the specified index, replacing it with the newly created matrix.

=='M'==

Multiplies two matrices at the specified indices. Allocates memory for the newly formed matrix. Uses the standard multiplication algorithm, with large elements being calculated using the modulo (10^4+7). Checks for available space for the resulting matrix. After multiplication, the new matrix is added to the list with its dimensions. Increases the number of matrices in the collection.

=='O'==

Calculates the sum of each matrix. Sorts the matrices in ascending order based on their sums. Values are computed modulo (10^4+7).

=='T'==

Allocates memory for the newly formed matrix. The matrix stores transposed elements where rows become columns and columns become rows. Frees memory for the matrix at the specified index, storing the newly created matrix in its place along with its dimensions.

=='R'==

Uses a function to square a matrix. Utilizes an auxiliary matrix to save the previous product. Calls the multiplication function with the initial matrix and the previously created matrix, then frees the allocated memory for the auxiliary matrix.

=='F'==

Deletes the matrix at the specified index. The remaining matrices shift one position to the left. Reduces the matrix count by one.

=='S'==

Implements a recursive function to carry out Strassen’s matrix multiplication. Divides each matrix into blocks of 4 elements, continuing until reaching a dimension of 1. Calculates sums for the next step. Calls the recursive function to form the 7 matrices required. Computes the 4 matrices that will form the result of the multiplication. Frees previously allocated memory.

=='Q'==

Frees all dynamically allocated memory. Terminates the program.
