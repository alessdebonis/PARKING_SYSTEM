// Definicion del struc spot y prototipos de funciones para manejo de los espacios del parqueadero
#ifndef SPOT_H
#define SPOT_H

#include <string> // para std::string (placa del carro)
#include <ctime> // para std::t_time (tipo de dato) (hora de entrada)

struct Spot {
    std::string plate; // string con nombre plate
    std::time_t entryTime; // tipo de dato time_t con nombre entryTime
    bool occupied; // tipo bool, nombre occupied, true = ocupado, false = libre.
};

//prototipos funciones para Spot
void initSpot(Spot*); // deja el epsacio Spot libre
bool validatePlate(std::string plate); // validar formato de placa "ABC123"
void registerEntry(Spot*); // registra cuando ingresa un carro
void registerExit(Spot*); // registra la salida del carro y cuando debe pagar
void showStatus(const Spot*); // muestra el estado actual del spot

#endif