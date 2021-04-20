all: single multi
single: SudokuValidatorSingleThreaded.cpp
	g++ -std=c++11 SudokuValidatorSingleThreaded.cpp -o single
multi: SudokuValidatorMultiThreaded.cpp
	g++ -std=c++11 SudokuValidatorMultiThreaded.cpp -o multi