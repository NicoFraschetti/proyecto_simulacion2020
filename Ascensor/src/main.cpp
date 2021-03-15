#include <iostream>
#include "../headers/modelo_ascensor.hpp"
#include <eosim/core/experiment.hpp>
#include "../headers/utils.hpp"
#include <math.h>


int main()
{
    using namespace eosim::core;
    std::cout << "Ingrese cuantas simulaciones quiere correr" << std::endl;
    int numSimulaciones;
    std::cin >> numSimulaciones;
    std::cout << "Ingrese un 1 para graficar las trayectorias de los ascensores o otro numero para no hacerlo" << std::endl;
    std::cout << "Si desea graficarlas, sea consciente de que la simulacion se hara mas lenta por los accesos a disco" << std::endl;
    int graficos;
    std::cin >> graficos;
    double simTime = 100000.0;
    double promediosEspera[numSimulaciones];
    double promediosUtilizacion[numSimulaciones];
    for (int i = 0; i< numSimulaciones; i++) {
        ModeloAscensor m = ModeloAscensor(3.4, (unsigned long) i + 129, graficos,0);
        Experiment e;
        std::cout << "Inicio simulacion " << i+1 << std::endl;
        m.connectToExp(&e);
        e.setSeed((unsigned long) i + 129);
        e.run(simTime);
        std::cout <<"Tiempo promedio de espera en cola (tonto)" << m.tEspera.getMean()<< '\n';
        std :: cout << "Factor de utilizacion ascensores (tonto) " << m.utilizacionAscensores.getMean() / (m.libreAscensor1.getMax()+m.libreAscensor2.getMax()) << std :: endl;
        promediosUtilizacion[i] = m.utilizacionAscensores.getMean() / (m.libreAscensor1.getMax()+m.libreAscensor2.getMax());
        promediosEspera[i] = m.tEspera.getMean();
        ModeloAscensor m1 = ModeloAscensor(3.4, (unsigned long) i + 129, graficos,1);
        Experiment e1;
        m1.connectToExp(&e1);
        e1.setSeed((unsigned long) i + 129);
        e1.run(simTime);
        std::cout <<"Tiempo promedio de espera en cola (inteligente)" << m1.tEspera.getMean()<< '\n';
        std :: cout << "Factor de utilizacion ascensores (inteligente) " << m1.utilizacionAscensores.getMean() / (m1.libreAscensor1.getMax()+m1.libreAscensor2.getMax()) << std :: endl;
        std::cout << "Fin simulacion " << i+1 << std::endl;
        std::cout << std::endl;

        if(graficos == 1) {
            system("gnuplot -p plot_trayectoria_ascensores.sh");
        }
    }
   /* if(numSimulaciones > 1) {
        std::cout << "Tiempo medio general en cola: " << utils::calcularMediaMuestral(promediosEspera,numSimulaciones) << std::endl;
        std::cout << "Varianza de tiempos en cola: " << utils::calcularVarianzaMuestral(promediosEspera,numSimulaciones) << std::endl;
        std::cout << "Desvio de tiempos en cola: " << sqrt(utils::calcularVarianzaMuestral(promediosEspera,numSimulaciones)) << std::endl;
    }*/
    return 0;
}
