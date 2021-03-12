#include "../headers/ascensor.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>
using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

ModeloAscensor::ModeloAscensor(double tasaArribos, int seedPisos):
            tasaArribos(tasaArribos),
            seedPisos(seedPisos),
            pF(*this),
            dA(*this),
            arribos(MT19937, tasaArribos),
            libreAscensor1(1, 1),
            libreAscensor2(1, 1) {}

ModeloAscensor::~ModeloAscensor() {}

void ModeloAscensor::init() {
    registerBEvent(&pF);

    registerCEvent(&dA);

    registerDist(&arribos);
}


void ModeloAscensor::doInitialSchedules() {
    schedule(0.0, new Pedido(seedPisos), pedidoF);
}
