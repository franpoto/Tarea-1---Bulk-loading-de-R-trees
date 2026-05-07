//
// Created by fabia on 3/5/2026.
//

#ifndef ALGORITMOSTAREA_STR_H
#define ALGORITMOSTAREA_STR_H

/**
 * Calcula el centro en el eje Y de un MBR.
 * @param m Rectángulo MBR.
 *
 * @return float
 * Coordenada Y del centro.
 */
float centroY(MBR r);
/**
 * Función de comparación para ordenar elementos por su centro en Y.
 * @param a Puntero a un elemento hijo.
 * @param b Puntero a otro elemento hijo.
 *
 * @return int
  * Valor negativo si a < b, positivo si a > b, 0 si son iguales.
 */
int cmpY(const void *a, const void *b);
/**
 * Construye un R-tree utilizando el algoritmo STR (Sort-Tile-Recursive).
 * @param elementos Arreglo de elementos (hijos) a organizar.
 * @param n Cantidad de elementos en el arreglo.
 *
 * @return int
 * Índice del nodo raíz dentro del arreglo global `arbol`.
 *
 */
int buildSTR(hijo* elementos, int n);

#endif //ALGORITMOSTAREA_STR_H