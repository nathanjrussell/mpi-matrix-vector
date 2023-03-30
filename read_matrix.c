/*
Date: March 29, 2023
Author: Nathan Russell
Purpose:
This program takes a filename input that contains struct data written by
generate_matrix_vector.c. The bin files contain the dimensions of a matrix A,
the entries of matrix A, a vector v, and the product of Av.

The files are used to load matrix data into MPI program. The files also contain
the known solution in order to compare outputs and time benchmarks.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// a struct to be read and written
struct MatrixProduct {
    int numRows; //number of rows
    int numCols; //number of cols
    int *matrixA; //single dimension array representing matrix A
    int *vectorv; //single dimension array represenint vector V
    int *productAv; //product of Av
    int seconds; //number of seconds required to perform sequentional Av.
};

//prints matrices for testing purposes (1-d representation)
void printMatrices(struct MatrixProduct *mp) {
  int rows = mp->numRows;
  int cols = mp->numCols;
  for (int r=0; r<rows*cols; ++r) {
    printf(" %d ",mp->matrixA[r]);
  }
  printf("\n");
  for (int c=0; c<cols; ++c) {
    printf(" %d ",mp->vectorv[c]);
  }
  printf("\n");
  for (int r=0; r<rows; ++r) {
    printf(" %d ", mp->productAv[r]);
  }
  printf("\n");
}

void writeFile2Struct(struct MatrixProduct *BM, char *filename)  {
  FILE *infile;
  int rows;
  int cols;
  infile = fopen(filename,"r");
  if (infile==NULL) {
    printf("Problem Opening File\n");
    exit(1);
  }
  fread(BM,sizeof(struct MatrixProduct),1,infile);
  rows = BM->numRows;
  cols = BM->numCols;

  BM->matrixA = (int*) malloc(rows*cols*sizeof(int)); //allocate matrix
  BM->vectorv = (int*) malloc(cols*sizeof(int)); //allocate vector
  BM->productAv = (int*) malloc(rows*sizeof(int)); //allocate product

  fread(BM->matrixA, sizeof(int)*rows*cols,1,infile);
  fread(BM->vectorv, sizeof(int)*cols,1,infile);
  fread(BM->productAv, sizeof(int)*rows,1,infile);
  printMatrices(BM);
}


int main(int argc, char *argv[]) {
  int rows;
  int cols;
  char *filename = argv[1];
  struct MatrixProduct BM;
  if (argc != 2) { //check if dims are provided
    printf("You must specify a file name (test_R_C.bin)\n");
    exit(1); //kill program for not having enough
  }
  writeFile2Struct(&BM, filename);

    return 0;
}
