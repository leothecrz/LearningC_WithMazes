
#include "gen.h"

struct Cell** genMaze(int height, int width, int SEED, char WALL_SYMBOL){

    const int startXY = 0;

    //cell Matrix Allocation
    struct Cell** cellMatrix;
    cellMatrix = (struct Cell**) malloc(height * sizeof(struct Cell*));
    for(int i=0; width > i; i++){
        cellMatrix[i] = (struct Cell*) malloc(width * sizeof(struct Cell));
    }

    //cell Matrix Initialized
    for(int i=0; i< height; i++){
		for(int j=0; j< width; j++){

			(cellMatrix[i][j]).y = i;
			(cellMatrix[i][j]).x = j;
			(cellMatrix[i][j]).wasVisited = 1;
			for(int k=0;k<4;k++){
				(cellMatrix[i][j]).walls[k]='1';
			}

		}
	}

    Stack traceback;

    cellMatrix[startXY][startXY].wasVisited = 0;
    traceback.push(&(cellMatrix[startXY][startXY]) );

    struct Cell* active;
    while(!traceback.isEmpty()){
        SEED++;

        active = traceback.pop();
        int x = active->x;
        int y = active->y;

        short int count = 0;
        if (x == 0){
            count += cellMatrix[y][x+1].wasVisited;
        } else if (x == (width-1) ){
            count += cellMatrix[y][x-1].wasVisited;
        } else {
            count += (	cellMatrix[y][x+1].wasVisited + cellMatrix[y][x-1].wasVisited);
        }

        if (y == 0){
            count += cellMatrix[y+1][x].wasVisited;
        } else if (y == (height-1) ){
            count += cellMatrix[y-1][x].wasVisited;
        } else {
            count += (	cellMatrix[y+1][x].wasVisited + cellMatrix[y-1][x].wasVisited);
        }

        if (count > 0){
            SEED++;
            
            traceback.push(active);
            srand(SEED);
            int num, ran = 0;
            while (!ran) {
                num = (rand() % 4) + 1;
                switch (num) {
                    case 1:

							if(removeTop(active, cellMatrix)){
								ran = 1;
                                traceback.push(&(cellMatrix[(*active).y-1][(*active).x]));
								(cellMatrix[(*active).y -1][(*active).x]).wasVisited = 0;
							}
							break;

						case 2:

							if(removeRight(active, width, cellMatrix)){
								ran = 1;
                                traceback.push(&(cellMatrix[(*active).y][(*active).x+1]));							
								(cellMatrix[(*active).y][(*active).x +1]).wasVisited = 0;
							}
							break;

						case 3:

							if(removeBottom(active, height, cellMatrix)){
								ran = 1;
                                traceback.push(&(cellMatrix[(*active).y+1][(*active).x]));
								(cellMatrix[(*active).y +1][(*active).x]).wasVisited = 0;
							}
							break;

						case 4:

							if(removeLeft(active, cellMatrix)){
								ran = 1;
                                traceback.push(&(cellMatrix[(*active).y][(*active).x-1]));
								(cellMatrix[(*active).y][(*active).x-1]).wasVisited = 0;
							}
							break;
                }
            }
        }
    }
    return cellMatrix;
}



int removeTop(struct Cell* cell, struct Cell** cellMatrix){

		if((*cell).y == 0){
			return 0;
		} else{
			if( (cellMatrix[((*cell).y)-1][(*cell).x]).wasVisited == 1 ){

				(cellMatrix[((*cell).y)-1][(*cell).x]).wasVisited = 0;
				cellMatrix[((*cell).y)-1][(*cell).x].walls[2] = '0';
				(*cell).walls[0] = '0';
				return 1;

			} else{
				return 0;
			}
		}
}

int removeRight(struct Cell* cell, int width, struct Cell** cellMatrix){

		if((*cell).x == (width-1)){
			return 0;
		} else{
			if( (cellMatrix[((*cell).y)][((*cell).x)+1]).wasVisited == 1 ){
				
				(cellMatrix[((*cell).y)][((*cell).x)+1]).wasVisited = 0;				
				cellMatrix[((*cell).y)][((*cell).x)+1].walls[3] = '0';
				(*cell).walls[1] = '0';
				return 1;

			} else{
				return 0;
			}
		}
}

int removeBottom(struct Cell* cell, int height, struct Cell** cellMatrix){

		if((*cell).y == (height-1)){
			return 0;
		} else{
			if( (cellMatrix[((*cell).y)+1][((*cell).x)]).wasVisited == 1 ){
				
				(cellMatrix[((*cell).y)+1][(*cell).x]).wasVisited = 0;
				cellMatrix[((*cell).y)+1][((*cell).x)].walls[0] = '0';
				(*cell).walls[2] = '0';
				return 1;

			} else{
				return 0;
			}
		}
}

int removeLeft(struct Cell* cell, struct Cell** cellMatrix){

		if((*cell).x == 0){
			return 0;
		} else{
			if( (cellMatrix[((*cell).y)][((*cell).x)-1]).wasVisited == 1 ){

				(cellMatrix[((*cell).y)][((*cell).x)-1]).wasVisited = 0;				
				cellMatrix[((*cell).y)][((*cell).x)-1].walls[1] = '0';
				(*cell).walls[3] = '0';
				return 1;

			} else{
				return 0;
			}
		}
}

void reinterpritMaze(char sym, int height, int width, struct Cell** cellMatrix){
	
	std:std::ofstream map("map.txt");
	map << 3*height << "," << 3*width << "\n";

	for(int i=0; i<height; i++){
		int step = 0;
		while(step != 3){
			step++;
			switch (step) {
				case 1:
					for(int j=0;j<width;j++){
						if (cellMatrix[i][j].walls[0] == '1'){
							map << sym << sym << sym;
							std::cout << sym << sym << sym;
						} else {
							map << sym << " " << sym;
							std::cout << sym << " " << sym;
						}
					}
					map << "\n";
					std::cout << "\n";

					break;
				case 2:
					for(int j=0;j<width;j++){
							if (cellMatrix[i][j].walls[3] == '1'){
								map << sym;
								std::cout << sym;

							} else {
								map << " ";
								std::cout << " ";

							}
							if (cellMatrix[i][j].walls[0] == '0' | cellMatrix[i][j].walls[1]== '0'| cellMatrix[i][j].walls[2]== '0'| cellMatrix[i][j].walls[3]== '0'){
								map << " ";
								std::cout << " ";

							} else {
								map << sym;
								std::cout << sym;

							}
							if (cellMatrix[i][j].walls[1] == '1'){
								map << sym;
								std::cout << sym;

							} else {
								map << " ";
								std::cout << " ";
							}
						}
						map << "\n";
						std::cout << "\n";

						break;
				case 3:
					for(int j=0;j<width;j++){
							if (cellMatrix[i][j].walls[2] == '1'){
								map << sym << sym << sym;
								std::cout << sym << sym << sym;

							} else {
								map << sym << " " << sym;
								std::cout << sym << " " << sym;
							}
						}
						map << std::endl;
						std::cout << std::endl;
						break;

			};
		}
	}
	map << "add an 's' to indicate the mazes start\n";
	map << "add a 'g' to indicate the mazes goal\n";
	map.close();
}