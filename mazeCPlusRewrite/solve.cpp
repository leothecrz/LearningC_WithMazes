
#include "solve.h"
#include <exception>
#include <ios>
#include <iostream>

void getData(char** maze, int** mazeCP, int* y, int* x){
	
	char c;
    char wallSym;

	char stringRows[10];
	char stringCols[10];
	int r_i = 0;
	int c_i = 0;

    int rows;
    int cols;

    std::ifstream file;
    file.open("map.txt");

	if (file){
		
		int flag = 0;
		while( file >> std::noskipws >> c) {
			if( c == '\n'){
				break;
			} else if ( c == ','){
				flag = 1;		
			} else if (!flag){
				stringRows[r_i] = c;
				r_i++;
			} else {
				stringCols[c_i] = c;
				c_i++;
			}
		}
	}
	rows = atoi(stringRows);
	cols = atoi(stringCols);
	
	int gotWalls = 0;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
				
			(file >> std::noskipws >> c);
			
			if ( c == '\n' ){
				(file >> std::noskipws >> c);
			} 
			if ( c == 's' || c == 'S'){
				*y = i;
				*x = j;
			} else if ( (!gotWalls) &&(c != ' ') && (c != 'g') ){
				gotWalls = 1;
				wallSym = c;
			}
			maze[i][j] = c;
		}
	}

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
		
			char terrain = maze[i][j];
			if(terrain == wallSym){
				mazeCP[i][j] = 1;
			} else if (terrain == 'g'){
				mazeCP[i][j] = 2;
			}else if (terrain == 's'){
				mazeCP[i][j] = 9;
			} else {
				mazeCP[i][j] = 0;
			}
		}
	}

}

int dfs(int row, int col, int** mazeCP){

	std::cout << row << " " << col << "\n";

	int* current = &mazeCP[row][col];

	std::cout << (*current) ;

	if(*current == 2){
		std::cout << "goal\n";
		return 1;
	}

	if(*current == 0 || *current == 9) {
		
		*current = 1;

		if(dfs(row-1, col, mazeCP)){
			*current = 3;
			return 1;
		}

		if(dfs(row, col+1, mazeCP)){
			*current = 3;
			return 1;
		}

		if(dfs(row+1, col, mazeCP)){
			*current = 3;
			return 1;
		}

		if(dfs(row, col-1, mazeCP)){
			*current = 3;
			return 1;
		}
	}

	return 0;
}