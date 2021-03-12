#ifndef ASCENSOR_HPP_
#define ASCENSOR_HPP_
#include <eosim/core/bevent.hpp>
    class Ascensor {
        private:
            int piso;
        public:
            Ascensor();

            ~Ascensor();

            int getPiso();

            void setPiso(int newPiso);

            void subir();

            void bajar();
    };


//eventos a1

const std::string Consulta1 = "ConsultarAscensor1";

class ConsultarAscensor1: public eosim::core::BEvent {
public:
	// constructor
	ConsultarAscensor1(eosim::core::Model& model);
	// destructor
	~ConsultarAscensor1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string SubirA1 = "SubirAscensor1";

class SubirAscensor1: public eosim::core::BEvent {
public:
	// constructor
	SubirAscensor1(eosim::core::Model& model);
	// destructor
	~SubirAscensor1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string BajarA1 = "BajarAscensor1";

class BajarAscensor1: public eosim::core::BEvent {
public:
	// constructor
	BajarAscensor1(eosim::core::Model& model);
	// destructor
	~BajarAscensor1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string PararA1 = "PararAscensor1";

class PararAscensor1: public eosim::core::BEvent {
public:
	// constructor
	PararAscensor1(eosim::core::Model& model);
	// destructor
	~PararAscensor1();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

//eventos a2

const std::string Consulta2 = "ConsultarAscensor2";

class ConsultarAscensor2: public eosim::core::BEvent {
public:
	// constructor
	ConsultarAscensor2(eosim::core::Model& model);
	// destructor
	~ConsultarAscensor2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string SubirA2 = "SubirAscensor2";

class SubirAscensor2: public eosim::core::BEvent {
public:
	// constructor
	SubirAscensor2(eosim::core::Model& model);
	// destructor
	~SubirAscensor2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string BajarA2 = "BajarAscensor2";

class BajarAscensor2: public eosim::core::BEvent {
public:
	// constructor
	BajarAscensor2(eosim::core::Model& model);
	// destructor
	~BajarAscensor2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};

const std::string PararA2 = "PararAscensor2";

class PararAscensor2: public eosim::core::BEvent {
public:
	// constructor
	PararAscensor2(eosim::core::Model& model);
	// destructor
	~PararAscensor2();
	// rutina del evento ligado
	void eventRoutine(eosim::core::Entity* who);
};


#endif
