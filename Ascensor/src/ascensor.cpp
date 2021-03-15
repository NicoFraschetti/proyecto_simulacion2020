#include "../headers/modelo_ascensor.hpp"
#include "../headers/ascensor.hpp"
#include <iostream>
#include <string>

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
//eventos generales

/*Le pasamos al controlador donde esta el ascensor*/
void ConsultarAscensor(Entity* who, Controlador* c, Ascensor* a) {
    c->setPisoActual(a->getPiso());
    delete(who);
}

/*Subimos 1 piso, planificamos de forma instantanea el notificarlo
(por adelantado) y planificamos en 2 segundos otra decision del controlador,
que seria cuando el ascensor realmente llego*/
void SubirAscensor(Entity* who, ModeloAscensor* m, Ascensor* a, std::string eventoConsulta, std::string eventoDecision) {
    a -> subir();
    m -> schedule(0.0, new Entity, eventoConsulta);
    m -> schedule(2.0, new Entity, eventoDecision);
    delete(who);

}

/*Bajamos 1 piso, planificamos de forma instantanea el notificarlo
(por adelantado) y planificamos en 2 segundos otra decision del controlador,
que seria cuando el ascensor realmente llego*/
void BajarAscensor(Entity* who, ModeloAscensor* m, Ascensor* a, std::string eventoConsulta, std::string eventoDecision) {
    a -> bajar();
    m -> schedule(0.0, new Entity, eventoConsulta);
    m -> schedule(2.0, new Entity, eventoDecision);
    delete(who);

}

/*Programamos el fin del viaje del ascensor (devolver el token)*/
void PararAscensor(Entity* who, ModeloAscensor* m, std::string eventoFin) {
    m -> schedule(0.0, new Entity, eventoFin);
    delete(who);

}

//eventos a1

ConsultarAscensor1::ConsultarAscensor1(Model& model): BEvent(Consulta1, model) {}

ConsultarAscensor1::~ConsultarAscensor1() {}


void ConsultarAscensor1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	ConsultarAscensor(who, &(ascensor.controlador1), &(ascensor.ascensor1));
}


SubirAscensor1::SubirAscensor1(Model& model): BEvent(SubirA1, model) {}

SubirAscensor1::~SubirAscensor1() {}

void SubirAscensor1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	SubirAscensor(who, &ascensor, &(ascensor.ascensor1), Consulta1, DecisionC1);
}


BajarAscensor1::BajarAscensor1(Model& model): BEvent(BajarA1, model) {}

BajarAscensor1::~BajarAscensor1() {}

void BajarAscensor1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	BajarAscensor(who, &ascensor, &(ascensor.ascensor1),Consulta1,DecisionC1);
}

PararAscensor1::PararAscensor1(Model& model): BEvent(PararA1, model) {}

PararAscensor1::~PararAscensor1() {}

void PararAscensor1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	PararAscensor(who, &ascensor, FinC1);
}


//eventos a2
ConsultarAscensor2::ConsultarAscensor2(Model& model): BEvent(Consulta2, model) {}

ConsultarAscensor2::~ConsultarAscensor2() {}

void ConsultarAscensor2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	ConsultarAscensor(who, &(ascensor.controlador2), &(ascensor.ascensor2));

}


SubirAscensor2::SubirAscensor2(Model& model): BEvent(SubirA2, model) {}

SubirAscensor2::~SubirAscensor2() {}

void SubirAscensor2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	SubirAscensor(who, &ascensor, &(ascensor.ascensor2), Consulta2, DecisionC2);

}


BajarAscensor2::BajarAscensor2(Model& model): BEvent(BajarA2, model) {}

BajarAscensor2::~BajarAscensor2() {}

void BajarAscensor2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	BajarAscensor(who, &ascensor, &(ascensor.ascensor2),Consulta2,DecisionC2);

}

PararAscensor2::PararAscensor2(Model& model): BEvent(PararA2, model) {}

PararAscensor2::~PararAscensor2() {}

void PararAscensor2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	PararAscensor(who, &ascensor, FinC2);

}



