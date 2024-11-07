#ifndef COMMON_DOT_H
#define COMMON_DOT_H


#include <stdio.h>
#include <stdlib.h>

void printMatrix(unsigned int **matrix, unsigned int n);
void printArray(int *array, unsigned int n);
unsigned int **setRectangle(unsigned int n);
unsigned int **fillMatrix(unsigned int n);
unsigned int **snailMatrix(short int n);
int *writeArray(unsigned int n);

#endif