#include <iostream>
#include "../headers/modelo_ascensor.hpp"
#include <eosim/core/experiment.hpp>
#include "../headers/utils.hpp"
#include <math.h>


int main()
{
    using namespace eosim::core;
    std::string c;
    std::cout << "Ingrese cuantas simulaciones quiere correr" << std::endl;
    int numSimulaciones;
    std::cin >> numSimulaciones;
    std::cout << "Ingrese la tasa de arribos (en promedio cada cuantos segundos llega un pedido?)" << std::endl;
    double arribos;
    std::cin >> arribos;
    double simTime;
    std::cout << "Ingrese el tiempo de las simulaciones" << std::endl;
    std::cin >>simTime;
    std::cout << "Ingrese un 1 para graficar las trayectorias de los ascensores o otro numero para no hacerlo" << std::endl;
    std::cout << "Si desea graficarlas, sea consciente de que la simulacion se hara mas lenta por los accesos a disco" << std::endl;
    int graficos;
    std::cin >> graficos;
    double promediosEspera[numSimulaciones];
    double promediosUtilizacion[numSimulaciones];
    double promediosProcesado[numSimulaciones];
    for (int i = 0; i< numSimulaciones; i++) {
        //estrategia tonta
        ModeloAscensor m = ModeloAscensor(arribos, (unsigned long) i + 256, graficos,0);
        Experiment e;
        std::cout << "Inicio simulacion " << i+1 << std::endl;
        m.connectToExp(&e);
        e.setSeed((unsigned long) i + 256);
        e.run(simTime);
        std::cout <<"Tiempo promedio de espera en cola (tonto)" << m.tEspera.getMean()<< '\n';
        std :: cout << "Factor de utilizacion ascensores (tonto) " << m.utilizacionAscensores.getMean() / (m.libreAscensor1.getMax()+m.libreAscensor2.getMax()) << std :: endl;
        std::cout <<"Tiempo promedio en el sistema (tonto)" << m.tProcesado.getMean()<< '\n';
        promediosUtilizacion[i] = m.utilizacionAscensores.getMean() / (m.libreAscensor1.getMax()+m.libreAscensor2.getMax());
        promediosEspera[i] = m.tEspera.getMean();
        promediosProcesado[i] = m.tProcesado.getMean();
        if(graficos == 1) {
            system("gnuplot -p plot_trayectoria_ascensores.sh");
            std::cout << "Ingrese una tecla para continuar" << std::endl;
            std :: cin >> c;
        }
        //estrategia inteligente
        ModeloAscensor m1 = ModeloAscensor(arribos, (unsigned long) i + 256, graficos,1);
        Experiment e1;
        m1.connectToExp(&e1);
        e1.setSeed((unsigned long) i + 256);
        e1.run(simTime);
        std::cout <<"Tiempo promedio de espera en cola (inteligente)" << m1.tEspera.getMean()<< '\n';
        std :: cout << "Factor de utilizacion ascensores (inteligente) " << m1.utilizacionAscensores.getMean() / (m1.libreAscensor1.getMax()+m1.libreAscensor2.getMax()) << std :: endl;
        std::cout <<"Tiempo promedio en el sistema (inteligente)" << m1.tProcesado.getMean()<< '\n';
        std::cout << "Fin simulacion " << i+1 << std::endl;
        std::cout << std::endl;

        if(graficos == 1) {
            system("gnuplot -p plot_trayectoria_ascensores.sh");
            std::cout << "Ingrese una tecla para continuar" << std::endl;
            std :: cin >> c;
        }
    }
    if(numSimulaciones > 1) {
        std::cout << "Estadisticos generales (calculados con el ascensor tonto)" << std::endl;
        std::cout << "Tiempo medio general en cola: " << utils::calcularMediaMuestral(promediosEspera,numSimulaciones) << std::endl;
        std::cout << "Varianza de tiempos en cola: " << utils::calcularVarianzaMuestral(promediosEspera,numSimulaciones) << std::endl;
        std::cout << "Desvio de tiempos en cola: " << sqrt(utils::calcularVarianzaMuestral(promediosEspera,numSimulaciones)) << std::endl;
        std::cout << "Media general utilizacion: " << utils::calcularMediaMuestral(promediosUtilizacion,numSimulaciones) << std::endl;
        std::cout << "Varianza general utilizacion: " << utils::calcularVarianzaMuestral(promediosUtilizacion,numSimulaciones) << std::endl;
        std::cout << "Desvio general utilizacion: " << sqrt(utils::calcularVarianzaMuestral(promediosUtilizacion,numSimulaciones)) << std::endl;
        std::cout << "Media general procesado: " << utils::calcularMediaMuestral(promediosProcesado,numSimulaciones) << std::endl;
        std::cout << "Varianza general procesado: " << utils::calcularVarianzaMuestral(promediosProcesado,numSimulaciones) << std::endl;
        std::cout << "Desvio general procesado: " << sqrt(utils::calcularVarianzaMuestral(promediosProcesado,numSimulaciones)) << std::endl;
    }
    return 0;
}
