#include "menu.h"
#include "spot.h"
#include "map.h"
#include <iostream>

void showMenu(){
    std::cout<<"1. Ver estado del spot\n";
    std::cout<<"2. Registrar entrada\n";
    std::cout<<"3. Registrar salida\n";
    std::cout<<"4. Salir\n";
}

void startProgram(){
    char map [ROW][COLUMN];
    initMap(map);
    std::vector<Spot> spots;
    initSpots(spots,map);

    int option = 0;
    do {
        updateMap(map, spots);
        showMap(map);
        showMenu();
        std::cin>>option;
        std::cin.ignore();

        switch(option){
            case 1:
            showStatus(spots);
            break;

            case 2:
            registerEntry(spots);
            break;

            case 3:
            registerExit(spots);
            break;

            case 4:
            std::cout<<"Saliendo...\n";
            break;

            default:
            std::cout<<"Opcion invalida\n";
            break;
        }
        

    } 
    
    while (option != 4);

}