//
// Created by Jared on 11/15/2018.
//


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>




float* initializeMatrix(int height, int width){
	//Initialize the matrix of height and width with random nubers between 0 and ten
	float* outputMatrix = malloc(width*height*sizeof(float)); //Assign the result a size of width by height
	for(int i = 0; i < width; i++){ //Loop over the columns
		for(int j = 0; j<height; j++){ //Loop over the rows
			outputMatrix[i+j*width] =10 * (float)rand()/RAND_MAX; //Set the number
		}
	}
	return outputMatrix;
}

void transpose(int matrixWidth, int matrixHeight, int blockWidth, float* inputMatrix, float* outputMatrix){
	//Initialize variables for determining time elapsed
	struct timeval t0;
	struct timeval t1;
	gettimeofday(&t0, 0);
	//Loop through the input matrix to transpose it
	for (int i = 0; i < matrixWidth; i += blockWidth) { //Loop over the matrix columns
		for (int j = 0; j < matrixHeight; j += blockWidth) { //Loop over the matrix rows
			for (int blockI = i; blockI < i + blockWidth && blockI<matrixWidth; blockI++) { //Loop over the block columns, check if it exceeds the matrix dimensions
				for (int blockJ = j; blockJ < j + blockWidth && blockJ <matrixHeight; blockJ++) { //Loop over the block rows, check if it exceeds the matrix dimensions
					outputMatrix[blockI*matrixHeight+blockJ] = inputMatrix[blockI + blockJ*matrixWidth];// Transpose the element
				}
			}
		}
	}
	//Get final time, calculate elapsed time
	gettimeofday(&t1, 0);
	long long elapsed = (t1.tv_sec-t0.tv_sec)*1000000LL + t1.tv_usec-t0.tv_usec;
	printf("%lld \n",elapsed);
}
void printMatrix(float* inputMatrix, int width, int height){
	//Loop through the rows then columns then print each element.
	for(int i = 0; i < width; i++){
		for(int j = 0; j<height; j++){
			printf("%f ", inputMatrix[i+j*width]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv) {
	//Check if the right arguments are given
	if (argc != 4) {
		printf("Missing arguments!\n""Usage: %s <matrix height> <matrix width> <block width> ...\n", argv[0]);
		return -1;
	}
	//Initialize the matrix height and width along with the block width
	int matrixHeight = atoi(argv[1]);
	int matrixWidth = atoi(argv[2]);
	int blockWidth = atoi(argv[3]);
	//Initialize the input and output matrices
	float* input = initializeMatrix(matrixHeight, matrixWidth);
	float* output = malloc(matrixWidth*matrixHeight*sizeof(float));
	//Print the input matrix, transpose it into the output then print the output matrix
	//printMatrix(input, matrixWidth, matrixHeight);
	transpose(matrixWidth, matrixHeight, blockWidth,input,output);
	//printMatrix(output, matrixHeight, matrixWidth);
	//Free the matrices
	free(input);
	free(output);
}