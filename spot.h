// Definicion del struc spot y prototipos de funciones para manejo de los espacios del parqueadero
#ifndef SPOT_H
#define SPOT_H

#include <string> // para std::string (placa del carro)
#include <ctime> // para std::t_time (tipo de dato) (hora de entrada), recomendado por claude
#include <vector>


struct Spot {
    int row;
    int col;
    std::string plate; // string con nombre plate
    std::time_t entryTime; // tipo de dato time_t con nombre entryTime
    bool occupied; // tipo bool, nombre occupied, true = ocupado, false = libre.
};

//prototipos funciones para Spot
void initSpot(Spot*); // deja el epsacio Spot libre
bool validatePlate(std::string plate); // validar formato de placa "ABC123"
void registerEntry(std::vector<Spot>& spots); // registra cuando ingresa un carro
void registerExit(std::vector<Spot>& spots); // registra la salida del carro y cuando debe pagar
void showStatus(std::vector<Spot>& spots); // muestra el estado actual del spot

void initSpots(std::vector<Spot>& spots, char map[16][16]);
int findSpotByPlate(std::vector<Spot>& spots, std::string plate);
int findFreeSpot(std::vector<Spot>& spots);

// ver vehiculos que ya estan registrados
void showVehicles(std::vector<Spot>& spots);

#endif