#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

class Pedido: public eosim::core::Entity {
    private:
        int piso;
    public:
        //constructor
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

class InicioDecision: public eosim::core::CEvent {
public:
    // constructor
    InicioDecision(eosim::core::Model& model);
    // destructor
    ~InicioDecision();
    // rutina del evento condicional
    void eventRoutine();
};

// identificador del evento de finalizacion de la decision
const std::string finDecision = "FinDecision";

class FinDecision: public eosim::core::BEvent {
public:
    // constructor
    FinDecision(eosim::core::Model& model);

    ~FinDecision();

    void eventRoutine(eosim::core::Entity* who);
}


#endif
