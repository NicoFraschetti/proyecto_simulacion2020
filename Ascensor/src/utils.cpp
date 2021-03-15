#include "../headers/utils.hpp"
#include <iostream>
#include <math.h>

double utils::calcularMediaMuestral(double* muestras, int cantidad) {
    double sumatoriaMuestras = 0;
    for(int i = 0; i< cantidad; i++) {
        sumatoriaMuestras += *(muestras + i)/ cantidad;
    }
    return sumatoriaMuestras;
}

double utils::calcularVarianzaMuestral(double* muestras, int cantidad) {
    double mediaMuestral = utils::calcularMediaMuestral(muestras, cantidad);
    double sumatoriaVarianzas = 0;
    for (int i = 0; i< cantidad; i++) {
        sumatoriaVarianzas += pow((*(muestras + i) - mediaMuestral),2);
    }
    double multiplicador = 1/(cantidad-1.0);
    return multiplicador*sumatoriaVarianzas;
}
