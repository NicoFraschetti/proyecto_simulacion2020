#ifndef CONTROLADOR_HPP_
#define CONTROLADOR_HPP_
#include <eosim/core/bevent.hpp>
#include <eosim/core/cevent.hpp>
    class Controlador {
        private:
            int pisoDeseado;
            int pisoActual;
        public:
            Controlador();

            ~Controlador();

            int getPisoDeseado();

            int getPisoActual();

            void setPisoDeseado(int newPiso);

            void setPisoActual(int newPiso);

    };


//eventos

class IniciarControlador1: public eosim::core::CEvent {
public:
	// constructor
	IniciarControlador1(eosim::core::Model& model);
	// destructor
	~IniciarControlador1();
	// rutina del evento condicional
	void eventRoutine();
};

const std::string DecisionC1 = "DecisionControlador1";

class DecisionControlador1: public eosim::core::BEvent {
public:
	// constructor
	DecisionControlador1(eosim::core::Model& model);
	// destructor
	~DecisionControlador1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string SubirC1 = "SubirControlador1";

class SubirControlador1: public eosim::core::BEvent {
public:
	// constructor
	SubirControlador1(eosim::core::Model& model);
	// destructor
	~SubirControlador1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string BajarC1 = "BajarControlador1";

class BajarControlador1: public eosim::core::BEvent {
public:
	// constructor
	BajarControlador1(eosim::core::Model& model);
	// destructor
	~BajarControlador1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string PararC1 = "PararControlador1";

class PararControlador1: public eosim::core::BEvent {
public:
	// constructor
	PararControlador1(eosim::core::Model& model);
	// destructor
	~PararControlador1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string FinC1 = "FinalizarControlador1";

class FinalizarControlador1: public eosim::core::BEvent {
public:
	// constructor
	FinalizarControlador1(eosim::core::Model& model);
	// destructor
	~FinalizarControlador1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

//eventos c2
class IniciarControlador2: public eosim::core::CEvent {
public:
	// constructor
	IniciarControlador2(eosim::core::Model& model);
	// destructor
	~IniciarControlador2();
	// rutina del evento condicional
	void eventRoutine();
};

const std::string DecisionC2 = "DecisionControlador2";

class DecisionControlador2: public eosim::core::BEvent {
public:
	// constructor
	DecisionControlador2(eosim::core::Model& model);
	// destructor
	~DecisionControlador2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string SubirC2 = "SubirControlador2";

class SubirControlador2: public eosim::core::BEvent {
public:
	// constructor
	SubirControlador2(eosim::core::Model& model);
	// destructor
	~SubirControlador2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string BajarC2 = "BajarControlador2";

class BajarControlador2: public eosim::core::BEvent {
public:
	// constructor
	BajarControlador2(eosim::core::Model& model);
	// destructor
	~BajarControlador2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string PararC2 = "PararControlador2";

class PararControlador2: public eosim::core::BEvent {
public:
	// constructor
	PararControlador2(eosim::core::Model& model);
	// destructor
	~PararControlador2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string FinC2 = "FinalizarControlador2";

class FinalizarControlador2: public eosim::core::BEvent {
public:
	// constructor
	FinalizarControlador2(eosim::core::Model& model);
	// destructor
	~FinalizarControlador2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};


#endif
