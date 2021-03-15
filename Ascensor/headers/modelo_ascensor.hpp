#ifndef MODELO_ASCENSOR_HPP_
#define MODELO_ASCENSOR_HPP_

#include <eosim/core/model.hpp>
#include <eosim/utils/entityqueuefifo.hpp>
#include <eosim/core/renewable.hpp>
#include <eosim/dist/negexpdist.hpp>
#include <eosim/statics/timeweighted.hpp>
#include <eosim/statics/observation.hpp>
#include <fstream>
#include "pedido.hpp"
#include "ascensor.hpp"
#include "controlador.hpp"

class ModeloAscensor: public eosim::core::Model {
private:
	// tasa de arribos de los pedidos
	double tasaArribos;

	// evento de arribo de los pacientes y alimentador (fijo)
	PedidoFeeder pF;

	// evento donde se decide que ascensor utilizara el pedido (condicional)
	DecidirAscensor dA;
	DecidirAscensorInteligente dAI;

	//eventos controlador 1
	IniciarControlador1 iC1; //condicional
	DecisionControlador1 dC1;
	SubirControlador1 sC1;
	BajarControlador1 bC1;
	PararControlador1 pC1;
	FinalizarControlador1 fC1;

    //eventos controlador 2
	IniciarControlador2 iC2; //condicional
	DecisionControlador2 dC2;
	SubirControlador2 sC2;
	BajarControlador2 bC2;
	PararControlador2 pC2;
	FinalizarControlador2 fC2;

	//eventos ascensor 1
	ConsultarAscensor1 cA1;
	SubirAscensor1 sA1;
	BajarAscensor1 bA1;
	PararAscensor1 pA1;

	//eventos ascensor 2
	ConsultarAscensor2 cA2;
	SubirAscensor2 sA2;
	BajarAscensor2 bA2;
	PararAscensor2 pA2;


public:

    // seed de los pedidos que generaremos
	int seedPisos;

    //Ascensores
    Ascensor ascensor1;

    Ascensor ascensor2;

    //Controladores
    Controlador controlador1;

    Controlador controlador2;

	// distribucion aleatoria de arribos de pacientes (exponencial)
	eosim::dist::NegexpDist arribos;

	eosim::utils::EntityQueueFifo q0;

	eosim::utils::EntityQueueFifo q1;

	eosim::utils::EntityQueueFifo q2;

	eosim::statics::Observation tEspera;

    eosim::statics::TimeWeighted utilizacionAscensores;

	eosim::core::Renewable libreAscensor1;

	eosim::core::Renewable libreAscensor2;

    FILE *trayectoriaA1;
    FILE *trayectoriaA2;


	int graficos;
	int inteligencia;

	// constructor del modelo
	ModeloAscensor(double tasaArribos, int seedPisos, int graficos, int inteligencia);
	// destructor del modelo
	~ModeloAscensor();
	// inicializa y registra los atributos del modelo, operacion abstracta de eosim::core::Model
	void init();
	// lleva al modelo a su estado inicial, operacion abstracta de eosim::core::Model
	void doInitialSchedules();
};


#endif
