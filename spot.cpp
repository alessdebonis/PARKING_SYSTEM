#include "spot.h"
#include "cobro.h"
#include <iostream>
#include <cctype>
#include "map.h"

// inicializar el espacion con valores vacio y libre.
void initSpot(Spot* s){

    s->plate = "";
    s->entryTime = 0;
    s->occupied = false;
}

bool validatePlate(std::string plate){
    if (plate.size()!= 6){
        return false;
    }

    for(int i = 0; i < 3; i++){
        if(!std::isalpha(plate[i])){
            return false;
        }
    }
    for(int i = 3; i < 6; i++){
        if(!std::isdigit(plate[i])){
            return false;
        }
    }

    return true;
}
void initSpots (std::vector<Spot>& spots, char map[16][16]){
    for (int i = 0; i < ROW ; i++){
        for(int j =0; j < COLUMN; j++){
            if(map[i][j] == 'P'){
            Spot space;
            space.row = i;
            space.col = j;
            space.plate = "";
            space.entryTime = 0;
            space.occupied = false;
            spots.push_back(space);
        }

        }
    }
}

int findFreeSpot(std::vector<Spot>& spots){
    int nospace = -1;
    for(int i =0; i < spots.size(); i++){
        if(spots[i].occupied == false){
            return i;
        }
    }
    return nospace;
}

int findSpotByPlate (std::vector<Spot>& spots, std::string plate){
    int nospace = -1;
    for(int i =0; i < spots.size(); i++){
        if(spots[i].occupied == true && spots[i].plate ==plate){
            return i;
        }
    }
    return nospace;
}


// registrar la entrada de un vehiculo, no sabemos cuantos van a entrar
void registerEntry(std::vector<Spot>& spots){
    int position = findFreeSpot(spots); // busca el primer espacio libre, usando la funcion findFreeSpot, guarda su posicion
    
    //Si no hay espaico libre, enviar mensaje de paqueadero lleno
    if (position == -1){ //position recibe -1, de la variable nospace
        std::cout<< "Parqueadero lleno\n";
        return;
    }

    // Se le pide la placa al usuario
    std::cout<<"ingresa la placa de esta forma ABC123: ";
    std::string plate;
    std::getline(std::cin,plate); //leer la placa del carro
    
    if(validatePlate(plate)){ //verifica que el formato de las placas sea el correcto ABC123
        
        if(findSpotByPlate(spots,plate) != -1){ //verifica que la placa no este ya en el parqueadero
            std::cout<<"Este vehiculo ya esta registrado";
            return;
        }
    spots[position].plate = plate;// guardar la plata en el spot libre
    spots[position].entryTime = std::time(NULL); // guarda la hora actual como la hora de entrada
    spots[position].occupied = true; // marca el espacio como ocupado
    std::cout<<"Vehiculo registrado\n"; // avisa al usuario
    }
    else{
        //si no es valida, avisar y borrar
        std::cout << "Error al ingresar placa, el formato valido es ABC123\n";
    }
}

// registrar s3alida del vehiculo y calcular el pago
void registerExit(std::vector<Spot>& spots){
    std::cout<<"Ingresa la placa del vehiculo para salir: ";
    std::string plate;
    std::getline(std::cin, plate);
    int position = findSpotByPlate (spots, plate);
    if(position == -1){
        std::cout<<"Vehiculo no encontrado\n";
        return;
    }
   
    std::time_t exitTime = std::time(NULL); // obtener la hora del tiempo de salida
    int minutes = calculateMinutes(spots[position].entryTime, exitTime); // calcular tiempo
    int fee = calculateFee(minutes); // calcular pago
    std::cout << "\n--- RECIBO ---\n";
    std::cout << "Placa: " << spots[position].plate << "\n";
    std::cout << "Tiempo: " << minutes << " minutos\n";
    std::cout << "Total: $" << fee << "\n";
    initSpot(&spots[position]); // liberar espacio para el siguiente carro
    }

// revisar el estado del espacio a ver si esta libre
void showStatus(std::vector<Spot>& spots){

    int freeSpot = 0;
    int takenSpot = 0;
    for (int i =0; i< spots.size(); i++){
        if (spots[i].occupied == true) {
            takenSpot++;
        }
        else {
            freeSpot++;
        }
    }

    std::cout<<"Espacio Libres: "<<freeSpot<<"\n";
    std::cout<<"Espacio Ocupados: "<<takenSpot<<"\n";
    std::cout<<"Espacios en total: "<<spots.size()<<"\n";
   
}
