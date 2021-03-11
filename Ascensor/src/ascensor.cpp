#include "../headers/ascensor.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>
using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

Ascensor::Ascensor(double tasaArribos):
            tasaArribos(tasaArribos),
            pF(*this),
            dA(*this),
            arribos(MT19937, tasaArribos),
            libreAscensor1(1, 1),
            libreAscensor2(1, 1) {}

Ascensor::~Ascensor() {}

void Ascensor::init() {
    registerBEvent(&pF);

    registerCEvent(&dA);

    registerDist(&arribos);
}


void Ascensor::doInitialSchedules() {
    schedule(0.0, new Pedido(), pedidoF);
}
