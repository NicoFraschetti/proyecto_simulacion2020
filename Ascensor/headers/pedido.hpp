#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

class PedidoEntity: public eosim::core::Entity {
    public:
        //constructor
        PedidoEntity();
        //destructor
        ~PedidoEntity();
        /*Obtenemos el piso al que vamos*/
        int getPiso();
        /*Cambiamos el piso destino
        (en teoria nunca lo usariamos)*/
        void setPiso(int newPiso);
};


// identificador del evento ligado PedidoFeeder
const std::string pedidoF = "PedidoFeeder";

class PedidoFeeder: public eosim::core::BEvent {
public:
	// constructor
	PedidoFeeder(eosim::core::Model& model);
	// destructor
	~PedidoFeeder();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};


#endif
