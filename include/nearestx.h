//
// Created by fabia on 2/5/2026.
//

#include "Estructuras.h"


/**
 * calcula el centro x de un rectangulo
 *
 * r: mbr de entrada
 *
 * return:
 * centro en x
 */
float centroX(MBR r);

/**
 * compara dos hijos segun su centro x
 *
 * a: primer hijo
 * b: segundo hijo
 *
 * return:
 * -1, 0 o 1
 */
int cmpX(const void *a, const void *b);

/**
 * calcula el mbr de un nodo
 *
 * n: nodo de entrada
 *
 * return:
 * mbr calculado
 */
MBR calcularMBR(Nodo *n);

/**
 * construye un r-tree usando nearest-x
 *
 * entrada: arreglo de hijos
 * n: cantidad de elementos
 *
 * return:
 * 0 si termina correctamente
 */
int nearestX(hijo *entrada, int n);