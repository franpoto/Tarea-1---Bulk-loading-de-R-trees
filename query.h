#ifndef QUERY_H
#define QUERY_H

#include <stdio.h>
#include "Estructuras.h"

/**
 * Verifica si dos MBR se intersectan
 */
int interseccion(MBR a, MBR b);

/**
 * Realiza una búsqueda por rango en el R-tree almacenado en disco
 *
 * @param f Archivo binario
 * @param nodeIndex Índice del nodo (0 = raíz)
 * @param query Rectángulo de búsqueda
 * @param io_count contador de accesos a disco
 *
 * @return cantidad de puntos encontrados
 */
int rangeQuery(FILE* f, int nodeIndex, MBR query, int* io_count);


MBR generarQuery(float s);

#endif