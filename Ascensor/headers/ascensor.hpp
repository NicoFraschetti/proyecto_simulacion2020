#ifndef ASCENSOR_HPP_
#define ASCENSOR_HPP_

#include <eosim/core/model.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include "pedido.hpp"

class Ascensor: public eosim::core::Model {
private:
	// tasa de arribos de los pacientes
	double tasaArribos;
	// evento de arribo de los pacientes y alimentador (fijo)
	PedidoFeeder pF;

public:

    int pisoAscensores[2];
	// distribucion aleatoria de arribos de pacientes (exponencial)
	eosim::dist::NegexpDist arribos;
	// cola de espera por camas
	eosim::utils::EntityQueueFifo cola;

	eosim::core::Renewable ascensor1;

	eosim::core::Renewable ascensor2;

	// constructor del modelo
	Ascensor(double tasaArribos);
	// destructor del modelo
	~Ascensor();
	// inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
	void init();
	// lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
	void doInitialSchedules();
};


#endif
