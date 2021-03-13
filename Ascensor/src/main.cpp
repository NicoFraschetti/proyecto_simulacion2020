#include <iostream>
#include "../headers/modelo_ascensor.hpp"
#include <eosim/core/experiment.hpp>


int main()
{
    std::string s;
    using namespace eosim::core;
    for (int i = 0; i< 10; i++) {
        ModeloAscensor m = ModeloAscensor(4, (unsigned long) i + 129);
        Experiment e;
        std::cout << "Inicio simulacion " << i+1 << std::endl;
        m.connectToExp(&e);
        e.setSeed((unsigned long) i + 129);
        e.run(50000.0);
        std::cout <<"Tiempo promedio de espera en cola " << m.tEspera.getMean()<< '\n';
        std :: cout << "Factor de utilizacion ascensores " << m.utilizacionAscensores.getMean() / (m.libreAscensor1.getMax()+m.libreAscensor2.getMax()) << std :: endl;
        std::cout << "Fin simulacion " << i+1 << std::endl;
        std::cout << std::endl;
    }
    return 0;
}
