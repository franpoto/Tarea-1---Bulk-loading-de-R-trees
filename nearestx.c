//
// Created by fabia on 2/5/2026.
//


#include <stdio.h>
#include <stdlib.h>
#include "Estructuras.h"
#include "inits.h"

//calcula los centros en X
float centroX(MBR r) {
    return (r.xmin + r.xmax) / 2.0;
}

// devuelve -1 0 1 dependiendo de la comparacion entre a y b
int cmpX(const void *a, const void *b) {
    hijo *h1 = (hijo*)a;
    hijo *h2 = (hijo*)b;

    float c1 = centroX(h1->clave);
    float c2 = centroX(h2->clave);

    if (c1 < c2) return -1;
    if (c1 > c2) return 1;
    return 0;
}

//calcula MRB de un nodo

MBR calcularMBR(Nodo *n) {
    MBR r = n->hijos[0].clave;

    for (int i = 1; i < n->k; i++) {
        if (n->hijos[i].clave.xmin < r.xmin) r.xmin = n->hijos[i].clave.xmin;
        if (n->hijos[i].clave.xmax > r.xmax) r.xmax = n->hijos[i].clave.xmax;
        if (n->hijos[i].clave.ymin < r.ymin) r.ymin = n->hijos[i].clave.ymin;
        if (n->hijos[i].clave.ymax > r.ymax) r.ymax = n->hijos[i].clave.ymax;
    }

    return r;
}

// funcion completa

int nearestX(hijo *entrada, int n) {

    while (1) {

        //  ordenar por X
        qsort(entrada, n, sizeof(hijo), cmpX);

        int inicio_nivel = total_nodos;
        int nodos_creados = 0;

        //  agrupar en nodos
        for (int i = 0; i < n; i += B) {

            Nodo nodo;
            nodo.k = 0;
            nodo.hijos = (hijo*) malloc(sizeof(hijo) * B);

            int limite = (i + B < n) ? i + B : n;

            for (int j = i; j < limite; j++) {
                nodo.hijos[nodo.k++] = entrada[j];
            }

            arbol[total_nodos++] = nodo;
            nodos_creados++;
        }

        //  si cabe en un nodo -> raíz
        if (nodos_creados <= B) {

            Nodo raiz;
            raiz.k = nodos_creados;
            raiz.hijos = (hijo*) malloc(sizeof(hijo) * B);

            for (int i = 0; i < nodos_creados; i++) {
                raiz.hijos[i].clave = calcularMBR(&arbol[inicio_nivel + i]);
                raiz.hijos[i].valor = inicio_nivel + i;
            }

            arbol[0] = raiz; // raíz en posición 0
            return 0;
        }

        //   generar siguiente nivel
        hijo *nuevo = (hijo*) malloc(sizeof(hijo) * nodos_creados);

        for (int i = 0; i < nodos_creados; i++) {
            nuevo[i].clave = calcularMBR(&arbol[inicio_nivel + i]);
            nuevo[i].valor = inicio_nivel + i;
        }

        // preparar siguiente iteración
        entrada = nuevo;
        n = nodos_creados;
    }
}