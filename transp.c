//
// Created by Jared on 11/11/2018.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>


float* initializeMatrix(int width){
	//Sets the matrix to random values between zero and ten
	float* outputMatrix = malloc(width*width*sizeof(float)); //Give the matrix enough space to hold the necessary elements
	for(int i = 0; i < width; i++){ //Loop over the square of the width
		for(int j = 0; j<width; j++){
			outputMatrix[i*width+j] =10 * (float)rand()/RAND_MAX;
		}
	}
	return outputMatrix;
}

void transpose(int width, int blockWidth, float* inputMatrix, float* outputMatrix){
	//Initialize variables for determining time elapsed
	struct timeval t0; //Initial time
	struct timeval t1; //End time
	gettimeofday(&t0, 0); //Get the initial time

	for (int i = 0; i < width; i += blockWidth) { //Loop over the columns
		for (int j = 0; j < width; j += blockWidth) {  //Loop over the rows
			for (int blockI = i; blockI < i + blockWidth; blockI++) { //Loop over the column inside a specific block
				for (int blockJ = j; blockJ < j + blockWidth; blockJ++) { //Loop over the rows inside a specific block
					outputMatrix[blockI + blockJ*width] = inputMatrix[blockI*width + blockJ]; //Swap the element at position block I, J with the block at J, I
				}
			}
		}
	}
	//Get final time, calculate elapsed time
	gettimeofday(&t1, 0);
	long long elapsed = (t1.tv_sec-t0.tv_sec)*1000000LL + t1.tv_usec-t0.tv_usec;
	printf("%lld \n",elapsed); //Print out the elapsed time
}
void printMatrix(float* inputMatrix, int width){
	//Print the matrix
	for(int i = 0; i < width; i++){
		for(int j = 0; j<width; j++){
			printf("%f ", inputMatrix[i*width+j]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv) {
	//Check if the right arguments are given
	if (argc != 3) {
		printf("Missing arguments!\n""Usage: %s <matrix width> <block width> ...\n", argv[0]);
		return -1;
	}
	//Set the matrix width, block width and initialize the matrices
	int matrixWidth = atoi(argv[1]);
	int blockWidth = atoi(argv[2]);
	float* input = initializeMatrix(matrixWidth);
	float* output = malloc(matrixWidth*matrixWidth*sizeof(float));
	//Print out the matrix ,transpose it, then print the new matrix
	//printMatrix(input, matrixWidth);
	transpose(matrixWidth, blockWidth,input,output);
	//printMatrix(output, matrixWidth);
	//Free the two matrices
	free(input);
	free(output);
}