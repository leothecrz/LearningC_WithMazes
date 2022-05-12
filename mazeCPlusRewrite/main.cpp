
#include <cstdio>
#include <fstream>
#include <ostream>
#include <stdlib.h>
#include <iostream>
#include <filesystem>

#include "gen.h"
#include "solve.h"

int main(void){
    std::ifstream file;
    file.open("map.txt");
    if(!file){
        
        //MAZE GEN
        struct Cell** cellMatrix;
        int height;
        int width;
                
        char wallSym = '#';

        std::cout << "Enter the Height of the Maze(each pixel is 3x3):";
        std::cin >> height;
        std::cout << "Enter the Width of the Maze(each pixel is 3x3):";
        std::cin >> width;

        cellMatrix = genMaze(height, width, time(0), '#');
        reinterpritMaze(wallSym, height, width, cellMatrix);

    } else{
        
        char** maze;
        int** mazeData;

        int rows, cols, yStart, XStart;
        char crumbSym = '.';

        char stringRows[11];
        char stringCols[11];
        int r_i = 0;
        int c_i = 0;
        char c;

        std::ifstream file;
        file.open("map.txt"); // GET ROWS AND COLS
            
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
        
        file.close(); 
	    rows = atoi(stringRows);
	    cols = atoi(stringCols);
        // R AND C

        maze =  (char**) std::malloc( rows * sizeof(char*));
        for(int i=0; i< rows; i++){
            maze[i]= (char*) std::malloc( cols * sizeof(char*));
        }

        mazeData = (int**) std::malloc( rows * sizeof(int*));
        for(int i=0; i< rows; i++){
            mazeData[i]=  (int*) std::malloc( cols * sizeof(int));
        }
        
        getData(maze, mazeData, &yStart, &XStart);

        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                std::cout << mazeData[i][j];
            }
            std::cout << std::endl;           
        }

        dfs(yStart, XStart, mazeData);

        
        for(int i=0; i<rows; i++){
		    for(int j=0; j<cols; j++){

                if (maze[i][j] != 's'){
                    if( mazeData[i][j] == 3 ){
                        maze[i][j] = crumbSym;
                    }
                }
			
		    }
        }
        
        std::cout << std::endl;  
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                std::cout << mazeData[i][j];
            }
            std::cout << std::endl;           
        }

        std::ofstream output("SOLVED.txt");
        std::cout << "\n";        
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                output << maze[i][j]<<" ";
                std::cout << maze[i][j]<<" ";
            }
            output << "\n";
            std::cout << "\n";           
        }
        std::remove("map.txt"); // map.txt is removed to reset state.
    }
}

