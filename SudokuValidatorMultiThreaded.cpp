#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <chrono>

using namespace std;

#define num_threads 27

typedef struct {
	int row;
	int column;		
} parameters;

int sudoku[9][9] = {
	{6, 2, 4, 5, 3, 9, 1, 8, 7},
	{5, 1, 9, 7, 2, 8, 6, 3, 4},
	{8, 3, 7, 6, 1, 4, 2, 9, 5},
	{1, 4, 3, 8, 6, 5, 7, 2, 9},
	{9, 5, 8, 2, 4, 7, 3, 6, 1},
	{7, 6, 2, 3, 9, 1, 4, 5, 8},
	{3, 7, 1, 9, 5, 6, 8, 4, 2},
	{4, 9, 6, 1, 8, 2, 5, 7, 3},
	{2, 8, 5, 4, 7, 3, 9, 1, 6}
};

int valid[num_threads] = {0};

void *check3x3(void* param){
    parameters *params = (parameters*) param;
    int row = params->row;
	int col = params->column;
    int digits[9] = {0};
	int i,j;
    for (i = row; i < row + 3; i++) {
		for (j = col; j < col + 3; j++) {
            int num = sudoku[i][j];
			if (num < 1 || num > 9 || digits[num - 1] == 1) {
				pthread_exit(NULL);
			} else {
				digits[num - 1] = 1;		
			}
        }
    }
    valid[row + col/3] = 1;
	pthread_exit(NULL);
}

void *checkRow(void* param){
    parameters *params = (parameters*) param;
    int row = params->row;
    int digits[9] = {0};
	int i;
    for (i = 0; i < 9; i++) {
		int num = sudoku[row][i];
		if (num < 1 || num > 9 || digits[num - 1] == 1) {
			pthread_exit(NULL);
		} else {
			digits[num - 1] = 1;		
		}
	}
	valid[9 + row] = 1;
	pthread_exit(NULL);
}

void *checkColumn(void* param){
    parameters *params = (parameters*) param;
	int col = params->column;
    int digits[9] = {0};
	int i;	
	for (i = 0; i < 9; i++) {
		int num = sudoku[i][col];
		if (num < 1 || num > 9 || digits[num - 1] == 1) {
			pthread_exit(NULL);
		} else {
			digits[num - 1] = 1;		
		}
	}
	valid[18 + col] = 1;
	pthread_exit(NULL);
}

parameters* createData(int i, int j){
    parameters *data = (parameters *) malloc(sizeof(parameters));	
    data->row = i;		
    data->column = j;
    return data;
}

int main(){
	auto start_time = std::chrono::high_resolution_clock::now();
    pthread_t threads[num_threads];
    int threadNumber = 0;
    int i,j;

    for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {						
			if (i%3 == 0 && j%3 == 0) {
				pthread_create(&threads[threadNumber++], NULL, check3x3, createData(i, j));
			}
			if (i == 0) {
				pthread_create(&threads[threadNumber++], NULL, checkColumn, createData(i, j));
			}
			if (j == 0) {
				pthread_create(&threads[threadNumber++], NULL, checkRow, createData(i, j));
			}
		}
	}

    for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);			// Wait for all threads to finish
	}

    for (i = 0; i < num_threads; i++) {
		if (valid[i] == 0) {
			cout << "Sudoku solution is invalid!" << endl;
			return EXIT_SUCCESS;
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
	cout << "Sudoku solution is valid!" << endl;
	cout << "Time taken by 27 threads = " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " microseconds." << endl;
	return EXIT_SUCCESS;
}
