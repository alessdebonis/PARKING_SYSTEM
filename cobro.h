// Declaraciones de funciones y constantes para el calculo de cobro
#ifndef COBRO_H
#define COBRO_H


#include <ctime>

const int RATE_PER_MINUTE = 190; // tarifa del parqueadero en pesos colombianos

int calculateMinutes(std::time_t entry, std::time_t exit); //calcula los minutos de entrada y salida
int calculateFee(int minutes); // calcula el cobro al carro teniendo en cuenta el tiempo en minutos


#endif