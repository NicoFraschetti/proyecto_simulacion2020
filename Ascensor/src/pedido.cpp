#include "../headers/pedido.hpp"
#include <stdlib.h>
#include <iostream>
#include "../headers/ascensor.hpp"

// Definicion de la entidad pedido

Pedido::Pedido() {
    piso = rand() % 10;
}

Pedido::~Pedido() {}

int Pedido::getPiso() {
    return piso;
}

void Pedido::setPiso(int newPiso) {
    piso = newPiso;
}
using namespace eosim::core;
// Definicion del evento ligado PedidoFeeder

PedidoFeeder::PedidoFeeder(Model& model): BEvent(pedidoF, model) {}

PedidoFeeder::~PedidoFeeder() {}

void PedidoFeeder::eventRoutine(Entity* who) {
	// se anuncia la llegada del paciente
	std::cout << "llego un pedido en " << who->getClock() << "\n";
	Ascensor& ascensor = dynamic_cast<Ascensor&>(owner);
	ascensor.q0.push(who);
	ascensor.schedule(ascensor.arribos.sample(), new Pedido(), pedidoF);
}

// Definicion del evento condicional InicioDecision

DecidirAscensor::DecidirAscensor(eosim::core::Model& model): CEvent(model) {}

DecidirAscensor::~DecidirAscensor() {}
// rutina del evento condicional que inicia la actividad de decision del ascensor (ascensor tonto)
void DecidirAscensor::eventRoutine() {
	Ascensor& ascensor = dynamic_cast<Ascensor&>(owner);
	if(!ascensor.q0.empty()) {
        if(ascensor.libreAscensor1.isAvailable(1)) {
            ascensor.q1.push(ascensor.q0.pop()); /*Si esta libre el ascensor 1 lo enviamos ahi*/
        }
        else {
            if(ascensor.libreAscensor2.isAvailable(1)) {
                ascensor.q2.push(ascensor.q0.pop()); /*Si no esta libre el primer ascensor y el segundo si, lo enviamos al segundo*/
            }
            else {
                int random = rand();
                if (random % 2) { /*sino lo enviamos a cualquier ascensor*/
                    ascensor.q1.push(ascensor.q0.pop());
                }
                else {
                    ascensor.q2.push(ascensor.q0.pop());
                }
            }
        }
	}

}
