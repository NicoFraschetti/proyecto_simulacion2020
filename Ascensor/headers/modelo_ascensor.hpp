#ifndef MODELO_ASCENSOR_HPP_
#define MODELO_ASCENSOR_HPP_

#include <eosim/core/model.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include "pedido.hpp"

class ModeloAscensor: public eosim::core::Model {
private:
	// tasa de arribos de los pedidos
	double tasaArribos;
	// evento de arribo de los pacientes y alimentador (fijo)
	PedidoFeeder pF;
	// evento donde se decide que ascensor utilizara el pedido (condicional)
	DecidirAscensor dA;

public:

    // seed de los pedidos que generaremos
	int seedPisos;

    int pisoAscensores[2];
	// distribucion aleatoria de arribos de pacientes (exponencial)
	eosim::dist::NegexpDist arribos;

	eosim::utils::EntityQueueFifo q0;

	eosim::utils::EntityQueueFifo q1;

	eosim::utils::EntityQueueFifo q2;

	eosim::core::Renewable libreAscensor1;

	eosim::core::Renewable libreAscensor2;

	// constructor del modelo
	ModeloAscensor(double tasaArribos, int seedPisos);
	// destructor del modelo
	~ModeloAscensor();
	// inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
	void init();
	// lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
	void doInitialSchedules();
};


#endif
