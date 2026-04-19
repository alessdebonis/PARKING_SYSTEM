#include "cobro.h"

int calculateMinutes(std::time_t entry, std::time_t exit){
    double seconds = std::difftime(exit,entry); // diferencia en segundos
    int minutes = (int) (seconds/60); // convertir segundos a minuto

    // cobrar inmediatamente entra
    if(seconds > 0 && minutes == 0){
        minutes = 1;
    }
    return minutes;
}

int calculateFee (int minutes, char type){
    if (type == 'M'){
        return minutes * MOTO_RATE_PER_MINUTE; //calcular pago moto
    }
    return minutes * CAR_RATE_PER_MINUTE; //calcular pago carros
}