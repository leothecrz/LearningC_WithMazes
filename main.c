
#include <stdio.h>
#include <stdlib.h>

char** maze;
int** mazeCP;

int rows;
int cols;

int yStart;
int xStart;

enum terrain {
	empty,
	wall,
	goal,
	crumb
};

void allocateMaze(){
	maze = malloc( rows * sizeof(char*));
	for(int i=0; i< rows; i++){
		maze[i]= malloc( cols * sizeof(char*));
	}
}

void allocateMazeCP(){
	mazeCP = malloc( rows * sizeof(char*));
	for(int i=0; i< rows; i++){
		mazeCP[i]= malloc( cols * sizeof(char*));
	}
}

void getMaze(char* mapfile){
	
	char c;
	char C_rows[4] = {'\0'};
	int r_i = 0;
	char C_cols[4] = {'\0'};
	int c_i = 0;

	FILE* file = fopen(mapfile, "r");
	
	if (file){
		
		int flag = 0;

		while( (c = getc(file)) != EOF) {
			if( c == '\n'){
				break;
			} else if ( c == ','){
				flag = 1;		
			} else if (!flag){
				C_rows[r_i] = c;
				r_i++;
			} else {
				C_cols[c_i] = c;
				c_i++;
			}
		}
	}

	rows = atoi(C_rows);
	cols = atoi(C_cols);

	allocateMaze();

	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			c = getc(file);
			
			if ( c == '\n' ){
				c = getc(file);
			} 
			if ( c == 's' || c == 'S'){
				yStart = i;
				xStart = j;
			}

			maze[i][j] = c;
		}
	}


	fclose(file);

}

void getMCP(){
	
	allocateMazeCP();

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			switch(maze[i][j]){
				case '+':
					mazeCP[i][j] = wall;
					break;
				case 'g':
					mazeCP[i][j] = goal;
					break;
				default:
					mazeCP[i][j] = empty;
					break;
			}
		}
	}
}


void printMaze(){
	
	printf("\nROWS: %d, COLS:%d \n",rows, cols);

	for(int i=0;i<rows;i++){
		for (int j=0;j<cols;j++){
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}

	printf("X-START: %d, Y-START: %d\n\n", xStart, yStart); 
}

void printMazeCP(){
	
	printf("\n");
	for(int i=0;i<rows;i++){
		for (int j=0;j<cols;j++){
			printf("%d ", mazeCP[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void addCrumbs(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){

			if (maze[i][j] != 's'){
				if( mazeCP[i][j] == crumb ){
					maze[i][j] = '-';
				}
			}
			
		}
	}
}

int dfs(int row, int col){

	int* current = &mazeCP[row][col];

	if(*current == goal)
		return 1;

	if(*current == empty) {
		*current = wall;


		if(dfs(row-1, col)){
			*current = crumb;
			return 1;
		}

		if(dfs(row, col+1)){
			*current = crumb;
			return 1;
		}

		if(dfs(row+1, col)){
			*current = crumb;
			return 1;
		}

		if(dfs(row, col-1)){
			*current = crumb;
			return 1;
		}
	}
	return 0;
}

int main(void){

	getMaze("map.txt");
	printMaze();	
	getMCP();	
	//printMazeCP();
	dfs(yStart, xStart);
	//printMazeCP();
	addCrumbs();
	printMaze();
	return 0;
}
