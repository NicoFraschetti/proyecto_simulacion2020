#include "../headers/pedido.hpp"
#include <stdlib.h>

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

// Definicion del evento ligado PedidoFeeder

PedidoFeeder::PedidoFeeder(Model& model): BEvent(pedidoF, model) {}

PedidoFeeder::~PedidoFeeder() {}

void PedidoFeeder::eventRoutine(Entity* who) {
	// se anuncia la llegada del paciente
	std::cout << "llego un pedido en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	Ascensor& ascensor = dynamic_cast<Ascensor&>(owner);
	ascensor.q0.push(who);
	ascensor.schedule(ascensor.arribos.sample(), new Pedido(), pedidoF);
}