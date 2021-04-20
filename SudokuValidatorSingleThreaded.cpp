#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>

using namespace std;

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

bool check3x3(int row, int col){
    int digits[9] = {0};
	int i,j;
    for (i = row; i < row + 3; i++) {
		for (j = col; j < col + 3; j++) {
            int num = sudoku[i][j];
			if (num < 1 || num > 9 || digits[num - 1] == 1) {
				return false;
			} else {
				digits[num - 1] = 1;		
			}
        }
    }
    return true;
}

bool checkRow(int row, int col){
    int digits[9] = {0};
	int i;
    for (i = 0; i < 9; i++) {
		int num = sudoku[row][i];
		if (num < 1 || num > 9 || digits[num - 1] == 1) {
			return false;
		} else {
			digits[num - 1] = 1;		
		}
	}
	return true;
}

bool checkColumn(int row, int col){
    int digits[9] = {0};
	int i;	
	for (i = 0; i < 9; i++) {
		int num = sudoku[i][col];
		if (num < 1 || num > 9 || digits[num - 1] == 1) {
			return false;
		} else {
			digits[num - 1] = 1;		
		}
	}
	return true;
}

int main(){
    auto start_time = std::chrono::high_resolution_clock::now();
    int i,j;
    for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {						
			if (i%3 == 0 && j%3 == 0) {
				if(!check3x3(i, j)){
                    cout << "Sudoku solution is invalid!" << endl;
			        return EXIT_SUCCESS;
                }
			}
			if (i == 0) {
				if(!checkColumn(i, j)){
                    cout << "Sudoku solution is invalid!" << endl;
			        return EXIT_SUCCESS;
                }
			}
			if (j == 0) {
				if(!checkRow(i, j)){
                    cout << "Sudoku solution is invalid!" << endl;
			        return EXIT_SUCCESS;
                }
			}
		}
	}

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
	cout << "Sudoku solution is valid!" << endl;
    cout << "Time taken by 1 thread = " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " microseconds." << endl;
	return EXIT_SUCCESS;
}
