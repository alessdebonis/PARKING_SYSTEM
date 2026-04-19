#include "menu.h"
#include "spot.h"
#include "map.h"
#include <iostream>

void showMenu(){
    std::cout<<"1. Ver estado del spot\n";
    std::cout<<"2. Registrar entrada\n";
    std::cout<<"3. Registrar salida\n";
    std::cout<<"4. Ver vehiculos registrados\n";
    std::cout<<"5. Salir\n";
}

void startProgram(){
    char map [ROW][COLUMN];
    initMap(map);
    std::vector<Spot> spots;
    initSpots(spots,map);

    int option = 0;
    do {
        std::cout << "\033[2J\033[H" << std::flush; // Limpiar pantalla, recomendada por claude
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
            showVehicles(spots);
            break;

            case 5:
            std::cout<<"Saliendo...\n";
            break;

            default:
            std::cout<<"Opcion invalida\n";
            break;
        }
        
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    //std::cout << "\033[2J\033[H";  // limpiar antes de redibujar

    }
    
    while (option != 5);

}