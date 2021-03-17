#include "../headers/pedido.hpp"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "../headers/modelo_ascensor.hpp"

// Definicion de la entidad pedido

Pedido::Pedido(int seed) {
    srand(seed);
    piso = rand() % 10;
}


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

double Pedido::getTiempoLlegada() {
    return tiempoLlegada;
}

void Pedido::setTiempoLlegada(double tiempo) {
    tiempoLlegada = tiempo;
}
using namespace eosim::core;
// Definicion del evento ligado PedidoFeeder

PedidoFeeder::PedidoFeeder(Model& model): BEvent(pedidoF, model) {}

PedidoFeeder::~PedidoFeeder() {}

void PedidoFeeder::eventRoutine(Entity* who) {
	// se anuncia la llegada del paciente
	//std::cout << "llego un pedido en " << who->getClock() << "\n";
	Pedido& p = dynamic_cast<Pedido&>(*who);
	p.setTiempoLlegada(who -> getClock());
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	ascensor.q0.push(who);
	ascensor.schedule(ascensor.arribos.sample(), new Pedido(), pedidoF);
}

// Definicion del evento condicional InicioDecision

DecidirAscensor::DecidirAscensor(eosim::core::Model& model): CEvent(model) {}

DecidirAscensor::~DecidirAscensor() {}
// rutina del evento condicional que inicia la actividad de decision del ascensor (ascensor tonto)
void DecidirAscensor::eventRoutine() {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	if(!ascensor.q0.empty() && ascensor.inteligencia != 1) {
        Entity* who = ascensor.q0.pop();
        if(ascensor.libreAscensor1.isAvailable(1)) {
            ascensor.q1.push(who); /*Si esta libre el ascensor 1 lo enviamos ahi*/
            //std::cout << "Se eligio el ascensor 1 en " << who -> getClock() << "\n";
        }
        else {
            if(ascensor.libreAscensor2.isAvailable(1)) {
                ascensor.q2.push(who); /*Si no esta libre el primer ascensor y el segundo si, lo enviamos al segundo*/
               // std::cout << "Se eligio el ascensor 2 en " << who -> getClock() << "\n";
            }
            else {
                int random = rand();
                if (random % 2) { /*sino lo enviamos a cualquier ascensor*/
                    ascensor.q1.push(who);
                 //   std::cout << "Se eligio el ascensor 1 en " << who -> getClock() << "\n";
                }
                else {
                    ascensor.q2.push(who);
                   // std::cout << "Se eligio el ascensor 2 en " << who -> getClock() << "\n";
                }
            }
        }
	}
}
double tiempoEstimadoAscensor(eosim::utils::EntityQueueFifo* q, Controlador* c, Pedido* p1) {
    double tiempoParcial = abs(c->getPisoDeseado()-c->getPisoActual())*2.0;
    int lugarAscensor = c->getPisoDeseado();
    for (unsigned int i=0; i<q->size();i++) {
        Entity* who = q->operator[](i);
        Pedido& p = dynamic_cast<Pedido&>(*who);
        tiempoParcial += (abs(lugarAscensor-p.getPiso())+0.0)*2.0;
        lugarAscensor = p.getPiso();
    }
    tiempoParcial += (abs(lugarAscensor-p1->getPiso())+0.0)*2.0;
    return tiempoParcial;
}

DecidirAscensorInteligente::DecidirAscensorInteligente(eosim::core::Model& model): CEvent(model) {}

DecidirAscensorInteligente::~DecidirAscensorInteligente() {}

void DecidirAscensorInteligente::eventRoutine() {
    ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	if(!ascensor.q0.empty() && ascensor.inteligencia == 1) {
        Entity* who = ascensor.q0.pop();
        Pedido& p = dynamic_cast<Pedido&>(*who);
        if(tiempoEstimadoAscensor(&(ascensor.q1),&(ascensor.controlador1), &p) <= tiempoEstimadoAscensor(&(ascensor.q2),&(ascensor.controlador2), &p)) {
            ascensor.q1.push(who);
        }
        else {
            ascensor.q2.push(who);
        }
	}
}
