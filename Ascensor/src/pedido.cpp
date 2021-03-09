#include "../headers/pedido.hpp"
#include <stdlib.h>
class Pedido : PedidoEntity {
    private:
        /*Piso al que le pediremos al ascensor que vaya*/
        int piso;
    public:
        Pedido(){
            piso = rand() % 10;
        }

        ~Pedido() {}

        int getPiso() {
            return piso;
        }

        void setPiso(int newPiso) {
            piso = newPiso;
        }
};
