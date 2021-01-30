#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int **allocate_matrix(int rows, int columns)
{
    int i;
    int **matrix = (int **)malloc(columns * sizeof(int *));
    for (i = 0; i < columns; i++)
        matrix[i] = (int *)malloc(rows * sizeof(int));

    return matrix;
}

void free_matrix(int **matrix, int rows, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        int *row = matrix[i];
        free(row);
    }
}

void init_matrix(int **matrix, int rows, int columns)
{
    int i, j;
    int v = 0;

    for (i = 0; i < columns; i++)
        for (j = 0; j < rows; j++)
            matrix[i][j] = ++v;
}

void print_matrix(int **matrix, int rows, int columns)
{
    int i, j;
    for (int i = 0; i < columns; i++)
    {
        printf("|");
        for (j = 0; j < rows; j++)
            printf("\t%d", matrix[i][j]);
        printf("\t|\n");
    }
}

void shuffle_matrix(int **matrix, int rows, int columns)
{
    int i, j, tmp;
    for (i = 0; i < columns; i++)
    {
        long r1 = random() % columns;
        for (j = 0; j < rows; j++)
        {
            long r2 = random() % rows;
            tmp = matrix[i][j];
            matrix[i][j] = matrix[r1][r2];
            matrix[r1][r2] = tmp;
        }
    }
}