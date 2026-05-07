//
// Created by fabia on 1/5/2026.
//


#ifndef INITS_H
#define INITS_H

#include <stdio.h>
#include <stdlib.h>
#include "Estructuras.h"

#define MAX_NODOS 100000

/**
 * arreglo global que almacena los nodos
 */
extern Nodo arbol[MAX_NODOS];

/**
 * cantidad total de nodos usados
 */
extern int total_nodos;

/**
 * crea un nodo vacio
 *
 * return:
 * nodo inicializado
 */
Nodo crearNodo();

/**
 * crea un punto usando coordenadas x,y
 *
 * x: coordenada x
 * y: coordenada y
 *
 * return:
 * hijo creado
 */
hijo crearPunto(float x, float y);

/**
 * reinicia el arbol
 */
void inicializarArbol();

/**
 * guarda el arbol en disco
 *
 * filename: nombre del archivo
 */
void guardarArbol(const char* filename);

#endif