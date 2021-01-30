#ifndef MATRIX_H
#define MATRIX_H

int **allocate_matrix(int rows, int columns);
void free_matrix(int **matrix, int rows, int columns);
void init_matrix(int **matrix, int rows, int columns);
void print_matrix(int **matrix, int rows, int columns);
void shuffle_matrix(int **matrix, int rows, int columns);

#endif