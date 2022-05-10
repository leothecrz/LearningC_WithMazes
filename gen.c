
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<time.h>

#include"gen.h"

struct Cell** cellMatrix;
int SEED;

int hSize;
int wSize;

int main(void){

	char WALL_SYMBOL = '#';

	allocateCellMatrix();
	genMaze(&(cellMatrix[1][1]));
	makeMaze(WALL_SYMBOL);	

	return 0;
}

void allocateCellMatrix(void){

	hSize = 0;
	wSize = 0;
	printf("Enter A Height For The Maze(Each pixel is a 3x3 block): ");
	scanf("%d", &hSize);
	printf("Enter A Width For The Maze(Each pixel is a 3x3 block): ");
	scanf("%d", &wSize);
	
	cellMatrix = malloc( hSize * sizeof(struct Cell*) );

	for(int i=0; i< wSize; i++){
		cellMatrix[i]= malloc( wSize * sizeof(struct Cell) );
	}

	for(int i=0; i< hSize; i++){
		for(int j=0; j< wSize; j++){

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
	if(x == -1 | y==-1){ // print whole maze
		
		for(int i=0;i<hSize;i++){
			for(int j=0;j<wSize;j++){
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
		if(x < wSize && y < hSize){
			struct Cell active = cellMatrix[x][y];
			printf("\nY: %d, X: %d, Visited: %d,\n", active.y, active.x, active.visited);
			for(int k=0;k<4;k++){
					printf("  Wall[%d]: %c ",k,active.walls[k]);
				}
				printf("\n\n");
			}
		}
		return;
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

		if((*cell).x == (wSize-1)){
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

		if((*cell).y == (hSize-1)){
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
	} else if (x == (wSize-1) ){
		count += cellMatrix[y][x-1].visited;
	} else {
		count += (	cellMatrix[y][x+1].visited + cellMatrix[y][x-1].visited	);
	}

	if (y == 0){
		count += cellMatrix[y+1][x].visited;
	} else if (y == (hSize-1) ){
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

	while(!isEmpty(&traceback)){
		SEED++;

		struct Cell* active = pop(&traceback);		
		int x = (*active).x;
		int y = (*active).y;
		int visitedCount = getVisited(x,y);

		if(visitedCount > 0){
			SEED++;

			push(&traceback, active);

			srand(SEED);

			int ran = 0; 
			int num;
			while(!ran){
				num = (rand() % 4) + 1;
				struct Cell topCell;
				switch(num){
						case 1:

							if(removeTop(active)){
								ran = 1;
								//topCell=(cellMatrix[(*active).y-1][(*active).x]);
								push(&traceback, &(cellMatrix[(*active).y-1][(*active).x]));

								(cellMatrix[(*active).y -1][(*active).x]).visited = 0;


							}
							break;

						case 2:

							if(removeRight(active)){
								ran = 1;
								//topCell=cellMatrix[(*active).y][(*active).x+1];
								push(&traceback, &(cellMatrix[(*active).y][(*active).x+1]));								

								(cellMatrix[(*active).y][(*active).x +1]).visited = 0;


							}
							break;

						case 3:

							if(removeBottom(active)){
								ran = 1;
								//topCell=cellMatrix[(*active).y+1][(*active).x];
								push(&traceback, &(cellMatrix[(*active).y+1][(*active).x]));								

								(cellMatrix[(*active).y +1][(*active).x]).visited = 0;


							}
							break;

						case 4:

							if(removeLeft(active)){
								ran = 1;
								//topCell=cellMatrix[(*active).y][(*active).x-1];
								push(&traceback, &(cellMatrix[(*active).y][(*active).x-1]));								

								(cellMatrix[(*active).y][(*active).x-1]).visited = 0;

							}
							break;
				}
			}
		}
	}
}

void makeMaze(char sym){

	FILE *pFile;
	pFile = fopen("newMap.txt", "w");
	fprintf(pFile,"%d,%d \n", (hSize*3), (3*wSize) );

	for(int i=0;i<hSize;i++){
		int k=0;
		while(k!=3){
			k++;
			switch(k){
				case 1:
					for(int j=0;j<wSize;j++){
						if (cellMatrix[i][j].walls[0] == '1'){
							fprintf(pFile,"%c%c%c",sym,sym,sym);
						} else {
							fprintf(pFile,"%c %c",sym,sym);
						}
					}
					fprintf(pFile,"\n");

					break;
				case 2:
					for(int j=0;j<wSize;j++){
							if (cellMatrix[i][j].walls[3] == '1'){
								fprintf(pFile,"%c",sym);

							} else {
								fprintf(pFile," ");

							}
							if (cellMatrix[i][j].walls[0] == '0' | cellMatrix[i][j].walls[1]== '0'| cellMatrix[i][j].walls[2]== '0'| cellMatrix[i][j].walls[3]== '0'){
								fprintf(pFile," ");

							} else {
								fprintf(pFile,"%c",sym);

							}
							if (cellMatrix[i][j].walls[1] == '1'){
								fprintf(pFile,"%c",sym);

							} else {
								fprintf(pFile," ");

							}
						}
						fprintf(pFile,"\n");

						break;
				case 3:
					for(int j=0;j<wSize;j++){
							if (cellMatrix[i][j].walls[2] == '1'){
								fprintf(pFile,"%c%c%c",sym,sym,sym);

							} else {
								fprintf(pFile,"%c %c",sym,sym);
							}
						}
						fprintf(pFile,"\n");
						break;
			}
		}
	}
	fprintf(pFile,"Place an 's' and a 'g' in the maze to set its start and goal.\n ");
	fclose(pFile);
}

//STRUCT STACK METHOSD
int isEmpty( struct Stack *stk ){
	
	int length = (stk->length);
	
	if ( (length) > 0 ){
		return 0;
	} else {
		return 1;
	}
}

void push( struct Stack *stk, struct Cell *cell ){

	struct Node *newNode;
	newNode = (struct Node*) malloc(sizeof(struct Node));

	(*newNode).next = ((*stk).top);
	(*newNode).data = cell;

	(*stk).top = newNode;
	(*stk).length += 1;

}

struct Cell* pop(struct Stack *stk){

	if (!isEmpty(stk)){
		struct Node *node = (stk)->top;
		(*stk).length -= 1;
		(*stk).top = (*node).next;

		struct Cell *cell = (*node).data;
		return cell;
	} else {
		exit(1);
	}
}
