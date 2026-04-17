#include "spot.h"
#include "cobro.h"
#include <iostream>
#include <cctype>


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

// registrar la entrada de un vehiculo
void registerEntry(Spot* s){
    if (s->occupied){
        std::cout<<"El espacio ya esta ocupado\n"; // si hay un vehiculo, el espacio esta ocupado
        return;
    }
    std::cout<<"ingresa la placa de esta forma ABC123: ";
    std::getline(std::cin, s->plate); //leer la placa del carro
    
    if(validatePlate(s->plate)){
    //si la placa es valida y cumple el formato "ABC123", seguir con el registro.
    s->entryTime = std::time(NULL); //hora actual exacta
    s->occupied = true; //marcar como espaio ocupado
    std::cout<<"Vehiculo registrado\n"; 
    }
    else{
        //si no es valida, avisar y borrar
        std::cout << "Error al ingresar placa, el formato valido es ABC123\n";
        s->plate =""; // limpia la placa incorrecta
    }
}

// registrar s3alida del vehiculo y calcular el pago
void registerExit(Spot* s){
    if (!s->occupied){  //si no hay carro
        std::cout<<"Error\n";
        return;
    }
    std::time_t exitTime = std::time(NULL); // obtener la hora del tiempo de salida
    int minutes = calculateMinutes(s->entryTime, exitTime); // calcular tiempo
    int fee = calculateFee(minutes); // calcular pago
    std::cout << "\n--- RECIBO ---\n";
    std::cout << "Placa: " << s->plate << "\n";
    std::cout << "Tiempo: " << minutes << " minutos\n";
    std::cout << "Total: $" << fee << "\n";
    initSpot(s); // liberar espacio para el siguiente carro
    }

// revisar el estado del espacio a ver si esta libre
void showStatus(const Spot* s){

    if(!s->occupied) {
        std::cout<<"Espacio libre\n";
        return;
    }
    std::cout<<"Espacio Ocupado\n";
    std::cout<<s->plate<<"\n"; //mostrar placa del carro

    // formatear la hora de entrada a texto legible, me ayude con claude...
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", std::localtime(&s->entryTime));
    std::cout<<buffer<<"\n"; // mostrar hora formateada

    // calcular cuanto tiempo lleva y como pagaria
    std::time_t now = std::time(NULL); //hora actual
    int minutes = calculateMinutes(s->entryTime, now); // tiempo en minutos pasados
    int fee = calculateFee(minutes); //estimar pago
    std::cout<<minutes<<"\n";
    std::cout<<fee<<"\n";
}
