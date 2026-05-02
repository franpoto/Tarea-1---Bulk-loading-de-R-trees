#include <stdio.h>
#include "Estructuras.h"
#include "query.h"
#include "inits.h"

#define B 204

typedef struct{
    MBR clave;
    int valor;
}HijoDisk;

typedef struct {
    int k;
    HijoDisk hijos[B];
    char pad[12];
} NodoDisk;


/**
 * Verifica si dos rectángulos se intersectan
 *
 * @param a Primer rectángulo
 * @param b Segundo rectángulo
 * @return 1 si se intersectan, 0 si no
 *
 * Dos rectángulos NO se intersectan si:
 * - uno está completamente a la izquierda del otro
 * - uno está completamente a la derecha
 * - uno está completamente arriba
 * - uno está completamente abajo
 */
int interseccion(MBR a, MBR b){
    // a esta a la izq de b
    if (a.xmax < b.xmin)
        return 0;
    // a esta a la der de b
    if (a.xmin > b.xmax)
        return 0;
    // a esta abajo de b
    if (a.ymax < b.ymin)
        return 0;
    // a esta arriba de b
    if (a.ymin > b.ymax)
        return 0; 
    

    return 1;
}

/**
 * Realiza una búsqueda por rango en un R-tree almacenado en disco
 *
 * @param f Archivo binario que contiene el árbol
 * @param nodeIndex Índice del nodo actual dentro del archivo
 * @param query Rectángulo de consulta
 * @param io_count Contador de accesos a disco
 *
 * @details
 * El algoritmo funciona de manera recursiva:
 * 1. Lee el nodo desde el archivo
 * 2. Recorre sus hijos
 * 3. Para cada hijo:
 *    - Si su MBR NO intersecta con la consulta → se ignora
 *    - Si intersecta:
 *        - Si es hoja (valor == -1) → se reporta el punto
 *        - Si es nodo interno → se llama recursivamente
 */

void rangeQuery(FILE* f, int nodeIndex, MBR query, int* io_count) {

    NodoDisk nodo;

    // leer nodo desde archivo
    fseek(f, nodeIndex * sizeof(NodoDisk), SEEK_SET);
    fread(&nodo, sizeof(NodoDisk), 1, f);

    (*io_count)++;

    for (int i = 0; i < nodo.k; i++) {

        HijoDisk h = nodo.hijos[i];

        if (!intersecccion(h.clave, query)) continue;

        if (h.valor == -1) {
            printf("Punto: (%f, %f)\n",h.clave.xmin, h.clave.ymin);
        } else {
            rangeQuery(f, h.valor, query, io_count);
        }
    }
}