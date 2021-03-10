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
	Ascensor& ascensor = dynamic_cast<Ascensor&>(owner);
	ascensor.q0.push(dynamic_cast<Pedido&>(who));
	ascensor.schedule(ascensor.arribos.sample(), new Pedido(), pedidoF);
}

// Definicion del evento condicional InicioDecision

InicioDecision::InicioDecision(eosim::core::Model& model): CEvent(model) {}

InicioDecision::~InicioDecision() {}
// rutina del evento condicional que inicia la actividad de decision del ascensor
void InicioDecision::eventRoutine() {
	Ascensor& ascensor = dynamic_cast<Ascensor&>(owner);
	while(!ascensor.q0.empty()) {
		Pedido& pedido = dynamic_cast<Pedido&>(ascensor.q0.pop());
		ascensor.schedule(0.0, pedido, finDecision);
	}

}

FinDecision::FinDecision(Model& model): BEvent(FinDecision, model) {}

FinDecision::~FinDecision() {}

void FinDecision::eventRoutine(Entity* who) {
	ascensor.q1.push(dynamic_cast<Pedido&>(who));
}