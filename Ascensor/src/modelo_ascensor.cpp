#include "../headers/modelo_ascensor.hpp"
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

            //eventos controlador 1
            iC1(*this), //condicional
            dC1(*this),
            sC1(*this),
            bC1(*this),
            pC1(*this),
            fC1(*this),

            //eventos controlador 2
            iC2(*this), //condicional
            dC2(*this),
            sC2(*this),
            bC2(*this),
            pC2(*this),
            fC2(*this),

            //eventos ascensor 1
            cA1(*this),
            sA1(*this),
            bA1(*this),
            pA1(*this),

            //eventos ascensor 2
            cA2(*this),
            sA2(*this),
            bA2(*this),
            pA2(*this),

            tEspera("Tiempos de Espera para subir al ascensor"),
            utilizacionAscensores("Factor de utilizacion ascensores", *this),
            arribos(MT19937, tasaArribos),
            libreAscensor1(1, 1),
            libreAscensor2(1, 1) {}

ModeloAscensor::~ModeloAscensor() {}

void ModeloAscensor::init() {
    registerBEvent(&pF);

    registerCEvent(&dA);

    //eventos controlador 1
    registerCEvent(&iC1); //condicional
    registerBEvent(&dC1);
    registerBEvent(&sC1);
    registerBEvent(&bC1);
    registerBEvent(&pC1);
    registerBEvent(&fC1);

    //eventos controlador 2
    registerCEvent(&iC2); //condicional
    registerBEvent(&dC2);
    registerBEvent(&sC2);
    registerBEvent(&bC2);
    registerBEvent(&pC2);
    registerBEvent(&fC2);

    //eventos ascensor 1
    registerBEvent(&cA1);
    registerBEvent(&sA1);
    registerBEvent(&bA1);
    registerBEvent(&pA1);

    //eventos ascensor 2
    registerBEvent(&cA2);
    registerBEvent(&sA2);
    registerBEvent(&bA2);
    registerBEvent(&pA2);


    registerDist(&arribos);
}


void ModeloAscensor::doInitialSchedules() {
    schedule(0.0, new Pedido(seedPisos), pedidoF);
}
