// Declaraciones de funciones y constantes para el calculo de cobro
#ifndef COBRO_H
#define COBRO_H


#include <ctime>

const int CAR_RATE_PER_MINUTE = 190; // tarifa para carros del parqueadero en pesos colombianos
const int MOTO_RATE_PER_MINUTE = 100; // tarifa para motos del parqueadero en pesos colombianos

int calculateMinutes(std::time_t entry, std::time_t exit); //calcula los minutos de entrada y salida
int calculateFee(int minutes, char type); // calcula el cobro al carro teniendo en cuenta el tiempo en minutos


#endif