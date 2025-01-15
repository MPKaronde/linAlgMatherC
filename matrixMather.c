#include <stdio.h>
#include <stdlib.h>

// defines a matrix
typedef struct
{
    int *data;       // points to linear array representing matric
    int rows;        // number of rows in this matrix
    int size;        // total num items in matrix
    int itemsPerRow; // number of items in each row
} Matrix;

// initializes matrix
void makeMatrix(Matrix *matrix, int rows, int size, int itemsPerRow)
{
    // set items per row and size
    matrix->rows = rows;
    matrix->size = size;
    matrix->itemsPerRow = size / rows;

    // allocate space for matrix data
    matrix->data = (int *)malloc(size * sizeof(int));
}

// set matrix value at point
void setPointValue(Matrix *matrix, int row, int col, int val)
{
    int currentIndex = (matrix->itemsPerRow * row) + col;
    matrix->data[currentIndex] = val;
}

// get item at given point in given matrix
int getPointValue(Matrix *matrix, int row, int col)
{
    int currentIndex = (matrix->itemsPerRow * row) + col;
    return matrix->data[currentIndex];
}

// prints out items in matrix
void printMatrix(Matrix *matrix)
{
    int i = 0;
    for (int x = 0; x < matrix->rows; x++)
    {
        for (int c = 0; c < matrix->itemsPerRow; c++)
        {
            printf("%d, ", matrix->data[i]);
            i++;
        }
        printf("\n");
    }
}

// free memory used by matrix
void freeMatrix(Matrix *matrix)
{
    free(matrix->data);
}

// adds the items in 1 and 2 together
// return 1 if complete and 0 if failed
int addMatrices(Matrix *inp1, Matrix *inp2, Matrix *out)
{
    // cannot complete add
    if (inp1->size != inp2->size || inp1->rows != inp2->rows || out->size != inp1->size || out->rows != inp1->rows)
    {
        return 0;
    }

    // add for item in each position
    for (int x = 0; x < inp1->rows; x++)
    {
        for (int y = 0; y < inp1->itemsPerRow; y++)
        {
            int val = getPointValue(inp1, x, y) + getPointValue(inp2, x, y);
            setPointValue(out, x, y, val);
        }
    }

    // signal completed add
    return 1;
}

// multiplies items in 1 and 2 together
// return 1 if complete and 0 if failed
int multiplyMatrices(Matrix *inp1, Matrix *inp2, Matrix *out)
{
    // cannot complete multiply
    if (inp1->itemsPerRow != inp2->rows || out->rows != inp1->rows || out->itemsPerRow != inp2->itemsPerRow)
    {
        return 0;
    }

    // go through each spot in the return matrix
    for (int r = 0; r < out->rows; r++)
    {
        for (int c = 0; c < out->itemsPerRow; c++)
        {
            int total = 0;
            for (int x = 0; x < inp1->itemsPerRow; x++)
            {
                total += (getPointValue(inp1, r, x) * getPointValue(inp2, x, c));
            }
            setPointValue(out, r, c, total);
        }
    }

    // signal multiply completed
    return 1;
}

int main()
{
    Matrix m1;
    makeMatrix(&m1, 3, 9, 3);

    Matrix m2;
    makeMatrix(&m2, 3, 9, 3);

    Matrix result;
    makeMatrix(&result, 3, 9, 3);

    int i = 0;
    for (int x = 0; x < m1.rows; x++)
    {
        for (int y = 0; y < m1.itemsPerRow; y++)
        {
            setPointValue(&m1, x, y, i);
            setPointValue(&m2, x, y, i);
            i++;
        }
    }

    printMatrix(&m1);
    printf("\n");
    printMatrix(&m2);
    printf("\n");
    printf("X\n");
    printf("\n");

    multiplyMatrices(&m1, &m2, &result);
    printMatrix(&result);

    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&result);
    return 0;
}