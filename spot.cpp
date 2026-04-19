#include "spot.h"
#include "cobro.h"
#include <iostream>
#include <cctype>
#include "map.h"

// inicializar un espacion individual con valores vacio y libre.
void initSpot(Spot* s){

    s->plate = "";// placa vacia
    s->entryTime = 0;
    s->occupied = false;
}

bool validatePlate(std::string plate){ // si no tiene 6 caracteres exactos, invalido
    if (plate.size()!= 6){
        return false;
    }

    for(int i = 0; i < 3; i++){ //revisa los 3 primeros caracteres, si alguno no es letra invalido
        if(!std::isalpha(plate[i])){
            return false;
        }
    }
    for(int i = 3; i < 6; i++){//revisa los 3 ultimos caracteres, si alguno no es numero invalido
        if(!std::isdigit(plate[i])){
            return false;
        }
    }

    return true;
}
void initSpots (std::vector<Spot>& spots, char map[16][16]){ // recorre todo el mapa, y crea un Spot para cada 'P' que encuentres.
    for (int i = 0; i < ROW ; i++){ // recorrer las filas
        for(int j =0; j < COLUMN; j++){ // recorrer las columnas
            if(map[i][j] == 'P'){ //si la celda es un parqueadero 'P'
            Spot space; //crea un spot nuevo
            space.row = i; //guarda que fila esta
            space.col = j; //guarda que columna esta
            space.plate = "";// no hay vehiculo
            space.entryTime = 0;//sin hora
            space.occupied = false;// desocupado
            spots.push_back(space); //agregar a la lista, recomendada por claude
        }

        }
    }
}

//buscar el primer espacio libre
int findFreeSpot(std::vector<Spot>& spots){
    int nospace = -1; // inicio variable nospace en -1, por que en la matriz no hay indice -1/
    for(int i =0; i < spots.size(); i++){ //recorre todos los spots
        if(spots[i].occupied == false){ // si en cuentras un espacio libre 
            return i; //retorna cual espacio libre es
        }
    }
    return nospace;// recorrrio todo el mapa y no encontro libre
}

// para buscar el vehiculo por su placa en el spot
int findSpotByPlate (std::vector<Spot>& spots, std::string plate){
    int nospace = -1;// inicio variable nospace en -1, por que en la matriz no hay indice -1/
    for(int i =0; i < spots.size(); i++){
        if(spots[i].occupied == true && spots[i].plate ==plate){ // si el espacio esta ocupado y la placa coincide
            return i; //devuelve su posicion
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

    int freeSpot = 0; //inicio variable local
    int takenSpot = 0; //inicio variable local
    for (int i =0; i< spots.size(); i++){
        if (spots[i].occupied == true) { //si el espacio esta ocupado
            takenSpot++; // suma 1 a espacios ocupados
        }
        else {
            freeSpot++; // suma 1 a espacios libres
        }
    }

    std::cout<<"Espacio Libres: "<<freeSpot<<"\n";
    std::cout<<"Espacio Ocupados: "<<takenSpot<<"\n";
    std::cout<<"Espacios en total: "<<spots.size()<<"\n"; // total espacios
   
}
//mostrar vehiculos registrados, para saber cual es el que debo sacar....
void showVehicles(std::vector<Spot>& spots){ 
    int count = 0; //inicializo una variable local en 0
    for(int i = 0; i < spots.size(); i++){ //recorrer spots
        if(spots[i].occupied == true){// si ese espacio esta ocupado
            std::cout<<"Placa: " <<spots[i].plate<<"\n"; //imprime su placa
            std::cout<<"Fila: "<<spots[i].row<<"\n"; //imprime su fila
            std::cout<<"Columna: "<<spots[i].col<<"\n"; //imprime su columna
            count++; // sumale uno a el conteo de vehiculos registrafos

        }
    }
    if(count==0){
        std::cout<<"No hay vehiculos registrados\n";
    }
}