//
// Created by fabia on 2/5/2026.
//


#include "inits.h"

int B = 204;
Nodo arbol[MAX_NODOS];
int total_nodos = 0;

Nodo crearNodo() {
    Nodo n;

    n.k = 0;
    n.hijos = (hijo*) malloc(sizeof(hijo) * B);

    return n;
}

hijo crearPunto(float x, float y) {
    hijo h;

    h.clave.xmin = x;
    h.clave.xmax = x;
    h.clave.ymin = y;
    h.clave.ymax = y;

    h.valor = -1;

    return h;
}

void inicializarArbol() {
    total_nodos = 1; // dejamos espacio para la raiz
}


