#include "../headers/modelo_ascensor.hpp"
#include "../headers/ascensor.hpp"

Ascensor::Ascensor() {
    piso = 1;
}

Ascensor::~Ascensor() {}

int Ascensor::getPiso() {
    return piso;
}

void Ascensor::setPiso(int newPiso) {
    piso = newPiso;
}

void Ascensor::subir() {
    setPiso(getPiso()+1);
}

void Ascensor::bajar() {
    setPiso(getPiso()-1);
}

using namespace eosim::core;

//eventos a1

ConsultarAscensor1::ConsultarAscensor1(Model& model): BEvent(Consulta1, model) {}

ConsultarAscensor1::~ConsultarAscensor1() {}

void ConsultarAscensor1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.controlador1.setPisoActual(ascensor.ascensor1.getPiso());
}


SubirAscensor1::SubirAscensor1(Model& model): BEvent(SubirA1, model) {}

SubirAscensor1::~SubirAscensor1() {}

void SubirAscensor1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.ascensor1.subir();
    ascensor.schedule(0.0, new Entity, Consulta1);
    ascensor.schedule(2.0, new Entity, DecisionC1);
}


BajarAscensor1::BajarAscensor1(Model& model): BEvent(BajarA1, model) {}

BajarAscensor1::~BajarAscensor1() {}

void BajarAscensor1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.ascensor1.bajar();
    ascensor.schedule(0.0, new Entity, Consulta1);
    ascensor.schedule(2.0, new Entity, DecisionC1);
}

PararAscensor1::PararAscensor1(Model& model): BEvent(PararA1, model) {}

PararAscensor1::~PararAscensor1() {}

void PararAscensor1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.schedule(0.0, new Entity, FinC1);
}


//eventos a2

ConsultarAscensor2::ConsultarAscensor2(Model& model): BEvent(Consulta2, model) {}

ConsultarAscensor2::~ConsultarAscensor2() {}

void ConsultarAscensor2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.controlador2.setPisoActual(ascensor.ascensor2.getPiso());
}


SubirAscensor2::SubirAscensor2(Model& model): BEvent(SubirA2, model) {}

SubirAscensor2::~SubirAscensor2() {}

void SubirAscensor2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.ascensor2.subir();
    ascensor.schedule(0.0, new Entity, Consulta2);
    ascensor.schedule(2.0, new Entity, DecisionC2);
}


BajarAscensor2::BajarAscensor2(Model& model): BEvent(BajarA2, model) {}

BajarAscensor2::~BajarAscensor2() {}

void BajarAscensor2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.ascensor2.bajar();
    ascensor.schedule(0.0, new Entity, Consulta2);
    ascensor.schedule(2.0, new Entity, DecisionC2);
}

PararAscensor2::PararAscensor2(Model& model): BEvent(PararA2, model) {}

PararAscensor2::~PararAscensor2() {}

void PararAscensor2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    ascensor.schedule(0.0, new Entity, FinC2);
}



