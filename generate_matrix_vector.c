/*
Date: March 29, 2023
Author: Nathan Russell
Purpose:
This program takes two integer command line arguments r and c representing
the size of a matrix A (r -rows and c- columns). The program will create a
matrix having r-rows and c-columns populated with integer entries ranging from
0 to 99. The program will also randomly generate a vector v containing c-values
that are randomly generated integers from 0 to 99. The program will calculate
the product of A*v will be computed.  The dimensions, matrix A, vector v, and
the product of Av will be stored in a struct that will be written to a file.

The MPI implementations will read this struct data, perform the product of Av
im parallel, check it against the solution, and compare the timing of the
sequential implementation. This will provide benchmarking gainst the sequential
implementation.
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

//populate matrices with random integer values
void populateMatrices(struct MatrixProduct *mp) {
  //populate matrix A with random integer values between 0 and 99
  for (int i=0; i< (mp->numRows)*(mp->numCols); ++i) {
    mp->matrixA[i] = rand() % 100;
  }
  //populate vector v with random integer values between 0 and 99
  for (int i=0; i<mp->numCols; ++i) {
    mp->vectorv[i] = rand() % 100;
  }
}

void calculateProduct(struct MatrixProduct *mp) {
  int rows = mp->numRows;
  int cols = mp->numCols;
  for (int r=0; r<rows; ++r) {
    mp->productAv[r] = 0;
    for (int c=0; c<cols; ++c) {
      mp->productAv[r] += mp->matrixA[r*cols + cols];
    }
  }
}

int main(int argc, char *argv[]) {

  int nrows; //number of rows in matrix A
  int ncols; //number of cols in matrix A

  if (argc != 3) { //check if dims are provided
    printf("You must specify two integer parameters for matrix dimension\n");
    exit(1); //kill program for not having enough
  }
  struct MatrixProduct mp; //struct for analysis
  nrows = atoi(argv[1]); //command line integer argument for num rows
  ncols = atoi(argv[2]); //command line integer argument for num cols
  if (nrows < 1 || ncols < 1) { //check if cols or rows are greater than 0
    printf("Dimensions must be integers greater than zero.\n");
    exit(1); //error so exit
  } //close if nrows and ncols
  mp.numRows = nrows; //set struct rows dimension
  mp.numCols = ncols; //set struct cols dimension
  mp.matrixA = (int*) malloc(nrows*ncols*sizeof(int)); //allocate matrix
  mp.vectorv = (int*) malloc(ncols*sizeof(int)); //allocate vector
  mp.productAv = (int*) malloc(nrows*sizeof(int)); //allocate product
  //provide some user feedback
  printf("Generating Matrix with %d rows and %d columns.\n", nrows , ncols );

  populateMatrices(&mp); //populate matrices with random values
  calculateProduct(&mp);


    // FILE* outfile;
    //
    // // open file for writing
    // outfile = fopen("person.bin", "wb");
    // if (outfile == NULL) {
    //     fprintf(stderr, "\nError opened file\n");
    //     exit(1);
    // }
    //
    // struct person input1 = { 1, "rohan", "sharma" };
    //
    // // write struct to file
    // int flag = 0;
    // flag = fwrite(&input1, sizeof(struct person), 1,
    //               outfile);
    // if (flag) {
    //     printf("Contents of the structure written "
    //            "successfully");
    // }
    // else
    //     printf("Error Writing to File!");
    //
    // // close file
    // fclose(outfile);

    return 0;
}
