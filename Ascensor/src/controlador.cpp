#include "../headers/modelo_ascensor.hpp"
#include "../headers/controlador.hpp"
#include <iostream>
#include <string>

Controlador::Controlador() {
    pisoActual = 0;
    pisoDeseado = 0;
    tiempoEntradaPedido = 0.0;
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

void Controlador::setTiempoEntradaPedido(double tiempo) {
    tiempoEntradaPedido = tiempo;
}

double Controlador::getTiempoEntradaPedido() {
    return tiempoEntradaPedido;
}

using namespace eosim::core;

void LogTiempos(ModeloAscensor* m, Pedido* p) {
    m->tEspera.log(m -> getSimTime() - p->getClock());
}

void LogUtilizacion(ModeloAscensor* m) {
    m->utilizacionAscensores.log((m->libreAscensor1.getMax()+m->libreAscensor2.getMax())-(m->libreAscensor1.getQuantity()+m->libreAscensor2.getQuantity()));
}

//eventos generales
/*Tomamos el token del ascensor, programamos una consulta de
donde esta el ascensor y una decision del controlador*/
void IniciarControlador(eosim::utils::EntityQueueFifo* q, eosim::core::Renewable* t,Controlador* c, ModeloAscensor* m, std::string eventoConsulta, std::string eventoDecision) {
    if(!q->empty() && t->isAvailable(1)) {
        Entity* who = q->pop();
        Pedido& p = dynamic_cast<Pedido&>(*who);
        LogTiempos(m,&p);
        LogUtilizacion(m);
        c -> setTiempoEntradaPedido(p.getClock());
        t->acquire(1);
        c->setPisoDeseado(p.getPiso());
        delete(who);
        m->schedule(0.0, new Entity(),eventoConsulta);
        m->schedule(0.0, new Entity(),eventoDecision);
    }
}

/*Segun donde este el ascensor y donde queramos ir,
programaremos una senal u otra*/
void DecisionControlador(Entity* who, Controlador* c, ModeloAscensor* m, std::string eventoSubir, std::string eventoBajar, std::string eventoParar) {
    if(c->getPisoDeseado() < c-> getPisoActual()) {
        m ->schedule(0.0, new Entity(), eventoBajar);
    }
    else {
        if(c-> getPisoDeseado() > c->getPisoActual()) {
            m->schedule(0.0, new Entity(), eventoSubir);
        }
        else {
            m->schedule(0.0, new Entity(), eventoParar);
        }
    }
    delete(who);
}

/*Senal del controlador para subir un piso*/
void SubirControlador(Entity* who, ModeloAscensor* m, std::string eventoSubir) {
    m->schedule(0.0, new Entity(), eventoSubir);
    delete(who);
}

/*Senal del controlador para bajar un piso*/
void BajarControlador(Entity* who, ModeloAscensor* m, std::string eventoBajar) {
    m->schedule(0.0, new Entity(), eventoBajar);
    delete(who);
}

/*Senal del controlador para parar*/
void PararControlador(Entity* who, ModeloAscensor* m, std::string eventoParar) {
    m->schedule(0.0, new Entity(), eventoParar);
    delete(who);
}

/*Devolvemos el token, ya que el ascensor esta libre*/
void FinalizarControlador(Entity* who, ModeloAscensor* m, Controlador* c, eosim::core::Renewable* t, FILE* internalFileName, char* externalFileName) {
    LogUtilizacion(m);
    m -> tProcesado.log(m -> getSimTime()-c ->getTiempoEntradaPedido());
    t->returnBin(1);
    delete(who);
    if(m->graficos) {
        internalFileName = fopen(externalFileName,"a");
        fprintf(internalFileName,"%d %lf\n",c->getPisoActual(),m->getSimTime());
        fclose(internalFileName);
    }
}

//eventos c1

IniciarControlador1::IniciarControlador1(Model& model): CEvent(model) {}

IniciarControlador1::~IniciarControlador1() {}

void IniciarControlador1::eventRoutine() {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    IniciarControlador(&(ascensor.q1),&(ascensor.libreAscensor1),&(ascensor.controlador1),&ascensor,Consulta1,DecisionC1);
}

DecisionControlador1::DecisionControlador1(Model& model): BEvent(DecisionC1, model) {}

DecisionControlador1::~DecisionControlador1() {}

void DecisionControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    DecisionControlador(who, &(ascensor.controlador1), &ascensor, SubirC1, BajarC1, PararC1);
}


SubirControlador1::SubirControlador1(Model& model): BEvent(SubirC1, model) {}

SubirControlador1::~SubirControlador1() {}

void SubirControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    SubirControlador(who, &ascensor, SubirA1);
}

BajarControlador1::BajarControlador1(Model& model): BEvent(BajarC1, model) {}

BajarControlador1::~BajarControlador1() {}

void BajarControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    BajarControlador(who, &ascensor, BajarA1);
}

PararControlador1::PararControlador1(Model& model): BEvent(PararC1, model) {}

PararControlador1::~PararControlador1() {}

void PararControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    PararControlador(who, &ascensor, PararA1);
}

FinalizarControlador1::FinalizarControlador1(Model& model): BEvent(FinC1, model) {}

FinalizarControlador1::~FinalizarControlador1() {}

void FinalizarControlador1::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	FinalizarControlador(who, &ascensor, &(ascensor.controlador1), &(ascensor.libreAscensor1), ascensor.trayectoriaA1, "output/trayectoriaA1.txt");
}

//eventos c2

IniciarControlador2::IniciarControlador2(Model& model): CEvent(model) {}

IniciarControlador2::~IniciarControlador2() {}

void IniciarControlador2::eventRoutine() {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    IniciarControlador(&(ascensor.q2),&(ascensor.libreAscensor2),&(ascensor.controlador2),&ascensor,Consulta2,DecisionC2);
}

DecisionControlador2::DecisionControlador2(Model& model): BEvent(DecisionC2, model) {}

DecisionControlador2::~DecisionControlador2() {}

void DecisionControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    DecisionControlador(who, &(ascensor.controlador2), &ascensor, SubirC2, BajarC2, PararC2);
}


SubirControlador2::SubirControlador2(Model& model): BEvent(SubirC2, model) {}

SubirControlador2::~SubirControlador2() {}

void SubirControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    SubirControlador(who, &ascensor, SubirA2);
}

BajarControlador2::BajarControlador2(Model& model): BEvent(BajarC2, model) {}

BajarControlador2::~BajarControlador2() {}

void BajarControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    BajarControlador(who, &ascensor, BajarA2);
}

PararControlador2::PararControlador2(Model& model): BEvent(PararC2, model) {}

PararControlador2::~PararControlador2() {}

void PararControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
    PararControlador(who, &ascensor, PararA2);
}

FinalizarControlador2::FinalizarControlador2(Model& model): BEvent(FinC2, model) {}

FinalizarControlador2::~FinalizarControlador2() {}

void FinalizarControlador2::eventRoutine(Entity* who) {
	ModeloAscensor& ascensor = dynamic_cast<ModeloAscensor&>(owner);
	FinalizarControlador(who, &ascensor, &(ascensor.controlador2), &(ascensor.libreAscensor2), ascensor.trayectoriaA2, "output/trayectoriaA2.txt");
}


