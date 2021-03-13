#include "../headers/modelo_ascensor.hpp"
#include "../headers/controlador.hpp"
#include <iostream>

Controlador::Controlador() {
    pisoActual = 0;
    pisoDeseado = 0;
}

Controlador::~Controlador() {}

int Controlador::getPisoActual() {
    return pisoActual;
}

int Controlador::getPisoDeseado() {
    return pisoDeseado;
}

void Controlador::setPisoActual(int newPiso) {
    pisoActual = newPiso;
}

void Controlador::setPisoDeseado(int newPiso) {
    pisoDeseado = newPiso;
}

using namespace eosim::core;

//eventos c1

IniciarControlador1::IniciarControlador1(Model& model): CEvent(model) {}

IniciarControlador1::~IniciarControlador1() {}
/*Tomamos el token del ascensor, programamos una consulta de
donde esta el ascensor y una decision del controlador*/
void IniciarControlador1::eventRoutine() {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	if(!ascensor.q1.empty() && ascensor.libreAscensor1.isAvailable(1)) {
        Entity* who = ascensor.q1.pop();
        Pedido& p = dynamic_cast<Pedido&>(*who);
        ascensor.tEspera.log(ascensor.getSimTime() - p.getClock());
        ascensor.utilizacionAscensores.log((ascensor.libreAscensor1.getMax()+ascensor.libreAscensor2.getMax())-(ascensor.libreAscensor1.getQuantity()+ascensor.libreAscensor2.getQuantity()));
        ascensor.libreAscensor1.acquire(1);
        ascensor.controlador1.setPisoDeseado(p.getPiso());
        ascensor.schedule(0.0, new Entity(), Consulta1);
        ascensor.schedule(0.0, new Entity(), DecisionC1);
    }
}

DecisionControlador1::DecisionControlador1(Model& model): BEvent(DecisionC1, model) {}

DecisionControlador1::~DecisionControlador1() {}
/*Segun donde este el ascensor y donde queramos ir,
programaremos una senal u otra*/
void DecisionControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    if(ascensor.controlador1.getPisoDeseado() < ascensor.controlador1.getPisoActual()) {
        ascensor.schedule(0.0, new Entity(), BajarC1);
    }
    else {
        if(ascensor.controlador1.getPisoDeseado() > ascensor.controlador1.getPisoActual()) {
            ascensor.schedule(0.0, new Entity(), SubirC1);
        }
        else {
            ascensor.schedule(0.0, new Entity(), PararC1);
        }
    }
}


SubirControlador1::SubirControlador1(Model& model): BEvent(SubirC1, model) {}

SubirControlador1::~SubirControlador1() {}
/*Senal del controlador para subir un piso*/
void SubirControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.schedule(0.0, new Entity(), SubirA1);
}

BajarControlador1::BajarControlador1(Model& model): BEvent(BajarC1, model) {}

BajarControlador1::~BajarControlador1() {}
/*Senal del controlador para bajar un piso*/
void BajarControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.schedule(0.0, new Entity(), BajarA1);
}

PararControlador1::PararControlador1(Model& model): BEvent(PararC1, model) {}

PararControlador1::~PararControlador1() {}
/*Senal del controlador para parar*/
void PararControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.schedule(0.0, new Entity(), PararA1);
}

FinalizarControlador1::FinalizarControlador1(Model& model): BEvent(FinC1, model) {}

FinalizarControlador1::~FinalizarControlador1() {}
/*Devolvemos el token, ya que el ascensor esta libre*/
void FinalizarControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	ascensor.utilizacionAscensores.log((ascensor.libreAscensor1.getMax()+ascensor.libreAscensor2.getMax())-(ascensor.libreAscensor1.getQuantity()+ascensor.libreAscensor2.getQuantity()));
    ascensor.libreAscensor1.returnBin(1);
}

//eventos c2
/*Los comentarios de arriba tambien aplican para estos*/
IniciarControlador2::IniciarControlador2(Model& model): CEvent(model) {}

IniciarControlador2::~IniciarControlador2() {}

void IniciarControlador2::eventRoutine() {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	if(!ascensor.q2.empty() && ascensor.libreAscensor2.isAvailable(1)) {
        Entity* who = ascensor.q2.pop();
        Pedido& p = dynamic_cast<Pedido&>(*who);
        ascensor.tEspera.log(ascensor.getSimTime() - p.getClock());
        ascensor.utilizacionAscensores.log((ascensor.libreAscensor1.getMax()+ascensor.libreAscensor2.getMax())-(ascensor.libreAscensor1.getQuantity()+ascensor.libreAscensor2.getQuantity()));
        ascensor.libreAscensor2.acquire(1);
        ascensor.controlador2.setPisoDeseado(p.getPiso());
        ascensor.schedule(0.0, new Entity(), Consulta2);
        ascensor.schedule(0.0, new Entity(), DecisionC2);
    }
}

DecisionControlador2::DecisionControlador2(Model& model): BEvent(DecisionC2, model) {}

DecisionControlador2::~DecisionControlador2() {}

void DecisionControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    if(ascensor.controlador2.getPisoDeseado() < ascensor.controlador2.getPisoActual()) {
        ascensor.schedule(0.0, new Entity(), BajarC2);
    }
    else {
        if(ascensor.controlador2.getPisoDeseado() > ascensor.controlador2.getPisoActual()) {
            ascensor.schedule(0.0, new Entity(), SubirC2);
        }
        else {
            ascensor.schedule(0.0, new Entity(), PararC2);
        }
    }
}


SubirControlador2::SubirControlador2(Model& model): BEvent(SubirC2, model) {}

SubirControlador2::~SubirControlador2() {}

void SubirControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.schedule(0.0, new Entity(), SubirA2);
}

BajarControlador2::BajarControlador2(Model& model): BEvent(BajarC2, model) {}

BajarControlador2::~BajarControlador2() {}

void BajarControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.schedule(0.0, new Entity(), BajarA2);
}

PararControlador2::PararControlador2(Model& model): BEvent(PararC2, model) {}

PararControlador2::~PararControlador2() {}

void PararControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.schedule(0.0, new Entity(), PararA2);
}

FinalizarControlador2::FinalizarControlador2(Model& model): BEvent(FinC2, model) {}

FinalizarControlador2::~FinalizarControlador2() {}

void FinalizarControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.utilizacionAscensores.log((ascensor.libreAscensor1.getMax()+ascensor.libreAscensor2.getMax())-(ascensor.libreAscensor1.getQuantity()+ascensor.libreAscensor2.getQuantity()));
    ascensor.libreAscensor2.returnBin(1);
}


