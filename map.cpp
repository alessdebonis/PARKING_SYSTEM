#include "map.h"
#include <iostream>

void initMap(char map[ROW][COLUMN]){
    char design[ROW][COLUMN] = {
        {'#','#','#','#','#','#','#','E','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'}, 
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'}, 
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','S','#','#','#','#','#','#','#','#'}
        };

    for (int i = 0; i < ROW; i++){
        for(int j =0; j < COLUMN; j++){
            map[i][j] = design[i][j];
        }
    }

}

void showMap(char map[ROW][COLUMN]){
    for (int i = 0; i < ROW; i++){
        for(int j =0; j < COLUMN; j++){
            std::cout<< map[i][j]<< " "; // imprime el caracter tipo char mas un espacio.
        }

        std::cout<<"\n"; //salto de linea para terminar cada fila
    }
    
}

void updateMap(char map[ROW][COLUMN], std::vector<Spot>&spots){
    for(int i =0; i<spots.size();i++){
        int rowSpace = spots[i].row;
        int colSpace = spots[i].col;

        if(spots[i].occupied){
            map[rowSpace][colSpace] = SPOT_TAKEN; // Espacio ocupado
        }
        else {
            map[rowSpace][colSpace] = SPOT_FREE; // Espacio libre
        }
    }

}
