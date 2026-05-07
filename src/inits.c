//
// Created by fabia on 2/5/2026.
//


#include "../include/inits.h"
#include "../include/Estructuras.h"



/**
 * arreglo global que representa el arbol
 */
Nodo arbol[MAX_NODOS];

/**
 * cantidad actual de nodos del arbol
 */
int total_nodos = 0;

/**
 * crea un nodo vacio
 *
 * return:
 * nodo inicializado
 */
Nodo crearNodo() {
    Nodo n;

    n.k = 0;

    return n;
}

/**
 * crea un punto a partir de coordenadas x,y
 *
 * x: coordenada x
 * y: coordenada y
 *
 * return:
 * hijo que representa el punto
 */
hijo crearPunto(float x, float y) {
    hijo h;

    h.clave.xmin = x;
    h.clave.xmax = x;
    h.clave.ymin = y;
    h.clave.ymax = y;

    h.valor = -1;

    return h;
}

/**
 * reinicia el arbol
 */
void inicializarArbol() {
    total_nodos = 1; // dejamos espacio para la raiz
}

/**
 * guarda el arbol en un archivo binario
 *
 * filename: nombre del archivo
 */
void guardarArbol(const char* filename) {
    FILE *f = fopen(filename, "wb");

    if (!f) {
        perror("Error abriendo archivo");
        exit(1);
    }

    for (int i = 0; i < total_nodos; i++) {
        fwrite(&arbol[i], sizeof(Nodo), 1, f);
    }

    fclose(f);
}