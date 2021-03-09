#include "../headers/pedido.hpp"
#include <stdlib.h>
Pedido::Pedido() {
    piso = rand() % 10;
}

Pedido::~Pedido() {}

int Pedido::getPiso() {
    return piso;
}

void Pedido::setPiso(int newPiso) {
    piso = newPiso;
}
