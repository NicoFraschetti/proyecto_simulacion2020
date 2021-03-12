#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <eosim/core/bevent.hpp>
#include <eosim/core/cevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

class Pedido: public eosim::core::Entity {
    private:
        int piso;
    public:
        //constructor con seed
        Pedido(int seed);
        //constructor sin seed
        Pedido();
        //destructor
        ~Pedido();
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
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

class DecidirAscensor: public eosim::core::CEvent {
public:
    // constructor
    DecidirAscensor(eosim::core::Model& model);
    // destructor
    ~DecidirAscensor();
    // rutina del evento condicional
    void eventRoutine();
};


#endif
