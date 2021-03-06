#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

// identificador del evento ligado PedidoFeeder
const std::string pedidoF = "PedidoFeeder";

class PedidoFeeder: public eosim::core::Bevent {
public:
	// constructor
	PedidoFeeder(eosim::core::Model& model);
	// destructor
	~PedidoFeeder();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

#endif