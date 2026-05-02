#include <stdio.h>
#include <stdlib.h>
#include "Estructuras.h"
#include "inits.h"
#include "nearestx"


/**
 * Calcula el centro en el eje Y de un MBR.
 * @param m Rectángulo MBR.
 *
 * @return float
 * Coordenada Y del centro.
 */
float centroY(MBR r) {
    return (r.ymin + r.ymax) / 2.0;
}


/**
 * Función de comparación para ordenar elementos por su centro en Y.
 * @param a Puntero a un elemento hijo.
 * @param b Puntero a otro elemento hijo.
 *
 * @return int
  * Valor negativo si a < b, positivo si a > b, 0 si son iguales.
 */
int cmpY(const void *a, const void *b) {
    hijo *h1 = (hijo*)a;
    hijo *h2 = (hijo*)b;

    float c1 = centroY(h1->clave);
    float c2 = centroY(h2->clave);

    if (c1 < c2) return -1;
    if (c1 > c2) return 1;
    return 0;
}

/**
 * Construye un R-tree utilizando el algoritmo STR (Sort-Tile-Recursive).
 * @param elementos Arreglo de elementos (hijos) a organizar.
 * @param n Cantidad de elementos en el arreglo.
 *
 * @return int
 * Índice del nodo raíz dentro del arreglo global `arbol`.
 *
 */
int buildSTR(hijo* elementos, int n) {
    
    //  Si los 𝑛/𝑏 pares llave-valor entran en un nodo (es decir, 𝑛𝑏 ≤ 𝑏), entonces 
    // creamos el nodo raíz con
    // todos los pares llave-valor y lo guardamos en la primera posición del vector de nodos.

    if (n <= B) {
        Nodo root = crearNodo();

        for (int i = 0; i < n; i++) {
            root.hijos[i] = elementos[i];
            root.k++;
        }

        int index = total_nodos++;
        arbol[index] = root;

        return index;
    }
    
    // Ordenar los rectángulos según la coordenada 𝑋 del centro del rectángulo.
    qsort(elementos, n, sizeof(hijo), cmpX);
    
    // Juntar en 𝑆 = √𝑛/𝑏 grupos de rectángulos consecutivos.
    int S = ceil(sqrt((double)n / B));
    int tamaño_grupos = ceil((double)n / S);
    
    // Para cada grupo:

    hijo* siguiente = malloc(sizeof(hijo) * (n / B + 1));
    int siguienteN = 0;

    for (int i = 0; i < n; i += tamaño_grupos) {

        int end;

        if (i + tamaño_grupos < n) {
            end = i + tamaño_grupos;
        } else {
            end = n;
        }

        // Ordenar los rectángulos según la coordenada 𝑌 del centro del rectángulo
        qsort(elementos + i, end - i, sizeof(hijo), cmpY);
        
        for (int j = i; j < end; j += B) {
            Nodo node = crearNodo();

        // Para cada uno de los 𝑛/𝑏 nodos creados, calcular su MBR y generar 𝑛/𝑏
        // pares llave-valor, donde nuevamente las llaves son rectángulos 
        // y los valores son los índices asociados a cada nodo 
        
            for (int k = j; k < j + B && k < end; k++) {
                node.hijos[node.k] = elementos[k];
                node.k++;
            }

            MBR m = calcularMBR(&node);

            int index = total_nodos++;
            arbol[index] = node;

            siguiente[siguienteN].clave = m;
            siguiente[siguienteN].valor = index;
            siguienteN++;
        }
    }
    
    // Recursión 
    int root = buildSTR(siguiente, siguienteN);

    free(siguiente);
    return root;
}

