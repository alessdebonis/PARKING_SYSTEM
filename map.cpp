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

void showMap(char map[ROW][COLUMN]){ // Diseño usando codigo colores codigo ANSI, recomendado por claude usar esta libreria, diseño unicode 
     // Título
    std::cout << "\033[36m";  // color cian
    std::cout << "╔═════════════════════════════════╗\n";
    std::cout << "║       PARQUEADERO CENTRAL       ║\n";
    std::cout << "╠═════════════════════════════════╣\n";
    std::cout << "\033[0m";

    // Mapa con colores
    for (int i = 0; i < ROW; i++){
        std::cout << "\033[36m║\033[0m ";  // borde izquierdo antes del for de columnas
        for(int j = 0; j < COLUMN; j++){
            if (map[i][j] == SPOT_FREE) {
                std::cout << "\033[32m" << map[i][j] << "\033[0m ";  // verde, espacio libre (P)
            } 
            else if (map[i][j] == 'C') {
                std::cout << "\033[31m" << map[i][j] << "\033[0m ";  // rojo, carro
            } 
            else if (map[i][j] == 'M') {
                std::cout << "\033[35m" << map[i][j] << "\033[0m ";  // magenta, moto
            } 
            else if (map[i][j] == ROAD) {
                std::cout << "\033[33m" << map[i][j] << "\033[0m ";  // amarillo, Vias
            } 
            else if (map[i][j] == ENTRY || map[i][j] == EXIT_GATE) {
                std::cout << "\033[36m" << map[i][j] << "\033[0m ";  // Entrada (E) y Salida (S)
            } 
            else {
                std::cout << "\033[37m" << map[i][j] << "\033[0m ";  // blanco (muros)
            }
        }
        std::cout << "\033[36m║\033[0m\n";  // borde derecho después del for de columnas

    }
    // Leyenda generada con claude
    std::cout << "\033[36m╚═════════════════════════════════╝\033[0m\n";
    std::cout << "\033[36m\033[0m ";
    std::cout << "\033[32mP\033[0m=Libre ";
    std::cout << "\033[31mC\033[0m=Carro ";        
    std::cout << "\033[35mM\033[0m=Moto \n";         
    std::cout << "\033[36mE\033[0m=Entrada ";
    std::cout << "\033[36mS\033[0m=Salida ";
    std::cout << "\033[36m\033[0m\n";
    std::cout << "\n";

}




void updateMap(char map[ROW][COLUMN], std::vector<Spot>&spots){
    for(int i =0; i<spots.size();i++){
        int rowSpace = spots[i].row;
        int colSpace = spots[i].col;

        if(spots[i].occupied){
            map[rowSpace][colSpace] = spots[i].type; // Espacio ocupado por 'C' = carro o 'M'= moto
        }
        else {
            map[rowSpace][colSpace] = SPOT_FREE; // Espacio libre
        }
    }

}
