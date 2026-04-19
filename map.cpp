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

/* 
void showMap(char map[ROW][COLUMN]){
    for (int i = 0; i < ROW; i++){
        for(int j =0; j < COLUMN; j++){
            std::cout<< map[i][j]<< " "; // imprime el caracter tipo char mas un espacio.
        }

        std::cout<<"\n"; //salto de linea para terminar cada fila
    }
    
}

*/

void showMap(char map[ROW][COLUMN]){ // Diseño usando codigo colores codigo ANSI, recomendado por claude usar esta libreria 
    for (int i = 0; i < ROW; i++){
        for(int j = 0; j < COLUMN; j++){
            if (map[i][j] == SPOT_FREE) {
                std::cout << "\033[32m" << map[i][j] << "\033[0m ";  // verde, espacio libre (P)
            } else if (map[i][j] == SPOT_TAKEN) {
                std::cout << "\033[31m" << map[i][j] << "\033[0m ";  // rojo, espacio ocupado (X)
            } else if (map[i][j] == ROAD) {
                std::cout << "\033[33m" << map[i][j] << "\033[0m ";  // amarillo, Vias
            } else if (map[i][j] == ENTRY || map[i][j] == EXIT_GATE) {
                std::cout << "\033[36m" << map[i][j] << "\033[0m ";  // Entrada (E) y Salida (S)
            } else {
                std::cout << "\033[37m" << map[i][j] << "\033[0m ";  // blanco (muros)
            }
        }
        std::cout << "\n";
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
