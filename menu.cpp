#include "menu.h"
#include "spot.h"
#include <iostream>

void showMenu(){
    std::cout<<"1. Ver estado del spot\n";
    std::cout<<"2. Registrar entrada\n";
    std::cout<<"3. Registrar salida\n";
    std::cout<<"4. Salir\n";
}

void startProgram(){
    Spot spot; // se crea variable espacio
    initSpot(&spot); // se inicializa el espacio usando su direccion en memoria
    int option = 0;
    do {
        showMenu();
        std::cin>>option;
        std::cin.ignore();

        switch(option){
            case 1:
            showStatus(&spot);
            break;

            case 2:
            registerEntry(&spot);
            break;

            case 3:
            registerExit(&spot);
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