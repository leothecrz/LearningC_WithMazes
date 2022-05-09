
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<time.h>
#include"stack.h"
#include"gen.h"

struct Cell** cellMatrix;
int size;
int SEED;

int main(void){

	setSize();
	allocateCellMatrix();
	//printCell(-1,-1);
	genMaze(&(cellMatrix[0][0]));
	makeMaze();

	return 0;
}

void allocateCellMatrix(void){

	cellMatrix = malloc( size * sizeof(struct Cell*) );

	for(int i=0; i< size; i++){
		cellMatrix[i]= malloc( size * sizeof(struct Cell) );
	}

	for(int i=0; i< size; i++){
		for(int j=0; j< size; j++){

			(cellMatrix[i][j]).y = i;
			(cellMatrix[i][j]).x = j;
			(cellMatrix[i][j]).visited = 1;
			for(int k=0;k<4;k++){
				(cellMatrix[i][j]).walls[k]='1';
			}

		}
	}
	return;
}

void printCell(int x,int y){
	if(x == -1 | y==-1){
		
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				struct Cell active = cellMatrix[i][j];
				printf("Y: %d, X: %d, Visited: %d| ", active.y, active.x, active.visited);
				for(int k=0;k<4;k++){
					//printf("Wall[%d]: %c ",k,active.walls[k]);
					printf("%c ",active.walls[k]);
				}
				printf("\n");
			}
		}
	}else{
		if(x < size && y < size){
			struct Cell active = cellMatrix[x][y];
			printf("\nY: %d, X: %d, Visited: %d,\n", active.y, active.x, active.visited);
			for(int k=0;k<4;k++){
					printf("  Wall[%d]: %c ",k,active.walls[k]);
				}
				printf("\n\n");
			}
		}
}
	
void setSize(){
	size = 0;
	printf("Enter a size for the maze: ");
	scanf("%d", &size);
}

int removeTop(struct Cell* cell){

		if((*cell).y == 0){
			return 0;
		} else{
			if( (cellMatrix[((*cell).y)-1][(*cell).x]).visited == 1 ){

				(cellMatrix[((*cell).y)-1][(*cell).x]).visited = 0;
				cellMatrix[((*cell).y)-1][(*cell).x].walls[2] = '0';
				(*cell).walls[0] = '0';
				return 1;

			} else{
				return 0;
			}
		}
}

int removeRight(struct Cell* cell){

		if((*cell).x == (size-1)){
			return 0;
		} else{
			if( (cellMatrix[((*cell).y)][((*cell).x)+1]).visited == 1 ){
				
				(cellMatrix[((*cell).y)][((*cell).x)+1]).visited = 0;				
				cellMatrix[((*cell).y)][((*cell).x)+1].walls[3] = '0';
				(*cell).walls[1] = '0';
				return 1;

			} else{
				return 0;
			}
		}
}

int removeBottom(struct Cell* cell){

		if((*cell).y == (size-1)){
			return 0;
		} else{
			if( (cellMatrix[((*cell).y)+1][((*cell).x)]).visited == 1 ){
				
				(cellMatrix[((*cell).y)+1][(*cell).x]).visited = 0;
				cellMatrix[((*cell).y)+1][((*cell).x)].walls[0] = '0';
				(*cell).walls[2] = '0';
				return 1;

			} else{
				return 0;
			}
		}
}

int removeLeft(struct Cell* cell){

		if((*cell).x == 0){
			return 0;
		} else{
			if( (cellMatrix[((*cell).y)][((*cell).x)-1]).visited == 1 ){

				(cellMatrix[((*cell).y)][((*cell).x)-1]).visited = 0;				
				cellMatrix[((*cell).y)][((*cell).x)-1].walls[1] = '0';
				(*cell).walls[3] = '0';
				return 1;

			} else{
				return 0;
			}
		}
}

int getVisited(int x, int y){
	int count = 0;

	if (x == 0){
		count += cellMatrix[y][x+1].visited;
	} else if (x == (size-1) ){
		count += cellMatrix[y][x-1].visited;
	} else {
		count += (	cellMatrix[y][x+1].visited + cellMatrix[y][x-1].visited	);
	}

	if (y == 0){
		count += cellMatrix[y+1][x].visited;
	} else if (y == (size-1) ){
		count += cellMatrix[y-1][x].visited;
	} else {
		count += (	cellMatrix[y+1][x].visited + cellMatrix[y-1][x].visited	);
	}
	
	return count;

}

void genMaze(struct Cell* start){
	
	struct Stack traceback = {NULL, 0};
	SEED = time(0);
	(*start).visited = 0;

	push(&traceback, start);
	printf("PUSH-size: %d,\n", traceback.length);

	while(!isEmpty(&traceback)){
		SEED++;

		struct Cell* active = pop(&traceback);
		printf("POP-size: %d,\n", traceback.length);

		
		int x = (*active).x;
		int y = (*active).y;
		int visitedCount = getVisited(x,y);

		printf("visitedCount: %d\n", visitedCount);

		if(visitedCount > 0){
			SEED++;

			push(&traceback, active);
			printf("Push-size: %d,\n", traceback.length);

			srand(SEED);

			int ran = 0; 
			int num;
			while(!ran){
				num = (rand() % 4) + 1;
				printf("Switch: %d\n", num);
				struct Cell topCell;
				switch(num){
						case 1:

							if(removeTop(active)){
								ran = 1;
								//topCell=(cellMatrix[(*active).y-1][(*active).x]);
								push(&traceback, &(cellMatrix[(*active).y-1][(*active).x]));
								printf("push-size: %d,\n", traceback.length);

								(cellMatrix[(*active).y -1][(*active).x]).visited = 0;


							}
							break;

						case 2:

							if(removeRight(active)){
								ran = 1;
								//topCell=cellMatrix[(*active).y][(*active).x+1];
								push(&traceback, &(cellMatrix[(*active).y][(*active).x+1]));								
								printf("push-size: %d,\n", traceback.length);

								(cellMatrix[(*active).y][(*active).x +1]).visited = 0;


							}
							break;

						case 3:

							if(removeBottom(active)){
								ran = 1;
								//topCell=cellMatrix[(*active).y+1][(*active).x];
								push(&traceback, &(cellMatrix[(*active).y+1][(*active).x]));								
								printf("push-size: %d,\n", traceback.length);

								(cellMatrix[(*active).y +1][(*active).x]).visited = 0;


							}
							break;

						case 4:

							if(removeLeft(active)){
								ran = 1;
								//topCell=cellMatrix[(*active).y][(*active).x-1];
								push(&traceback, &(cellMatrix[(*active).y][(*active).x-1]));								
								printf("push-size: %d,\n", traceback.length);

								(cellMatrix[(*active).y][(*active).x-1]).visited = 0;

							}
							break;
				}
			}
		}
		printCell(x,y);

	}

}

void makeMaze(){

	printf("\n\n --TEST MAZE v1 --\n");

	FILE *pFile;
	pFile = fopen("newMap.txt", "w");
	fprintf(pFile,"%d,%d \n", (size*3), (3*size) );

	for(int i=0;i<size;i++){
		int k=0;
		while(k!=3){
			k++;
			switch(k){
				case 1:
					for(int j=0;j<size;j++){
						if (cellMatrix[i][j].walls[0] == '1'){
							printf("+++");
							fprintf(pFile,"+++");
						} else {
							printf("+ +");
							fprintf(pFile,"+ +");
						}
					}
					printf("\n");
					fprintf(pFile,"\n");

					break;
				case 2:
					for(int j=0;j<size;j++){
							if (cellMatrix[i][j].walls[3] == '1'){
								printf("+");
								fprintf(pFile,"+");

							} else {
								printf(" ");
								fprintf(pFile," ");

							}
							if (cellMatrix[i][j].walls[0] == '0' | cellMatrix[i][j].walls[1]== '0'| cellMatrix[i][j].walls[2]== '0'| cellMatrix[i][j].walls[3]== '0'){
								printf(" ");
								fprintf(pFile," ");

							} else {
								printf("+");
								fprintf(pFile,"+");

							}
							if (cellMatrix[i][j].walls[1] == '1'){
								printf("+");
								fprintf(pFile,"+");

							} else {
								printf(" ");
								fprintf(pFile," ");

							}
						}
						printf("\n");
						fprintf(pFile,"\n");

						break;
				case 3:
					for(int j=0;j<size;j++){
							if (cellMatrix[i][j].walls[2] == '1'){
								printf("+++");
								fprintf(pFile,"+++");

							} else {
								printf("+ +");
								fprintf(pFile,"+ +");
							}
						}
						printf("\n");
						fprintf(pFile,"\n");
						break;
			}
		}
	}

}
