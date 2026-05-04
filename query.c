#include <stdio.h>
#include "Estructuras.h"
#include "query.h"
#include "inits.h"

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

int rangeQuery(FILE* f, int nodeIndex, MBR query, int* io_count) {

    Nodo nodo;
    int encontrados = 0;

    // leer nodo desde disco
    fseek(f, nodeIndex * sizeof(Nodo), SEEK_SET);
    fread(&nodo, sizeof(Nodo), 1, f);

    (*io_count)++;

    for (int i = 0; i < nodo.k; i++) {

        hijo h = nodo.hijos[i];

        
        if (!interseccion(h.clave, query)) continue;

        
        if (h.valor == -1) {
            encontrados++;
        }
        
        else {
            encontrados += rangeQuery(f, h.valor, query, io_count);
        }
    }

    return encontrados;
}

MBR generarQuery(float s) {
    MBR q;

    float x = (float)rand() / RAND_MAX;
    float y = (float)rand() / RAND_MAX;


    if (x > 1.0 - s) x = 1.0 - s;
    if (y > 1.0 - s) y = 1.0 - s;

    q.xmin = x;
    q.ymin = y;
    q.xmax = x + s;
    q.ymax = y + s;

    return q;
}

double stddev(double arr[], int n, double mean) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double d = arr[i] - mean;
        sum += d * d;
    }
    return sqrt(sum / n);
}