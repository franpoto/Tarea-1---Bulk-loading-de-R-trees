#include <stdio.h>
#include "Estructuras.h"
#include "query.h"
#include "inits.h"
#include <math.h>

/**
 * Verifica si dos rectángulos (MBR) se intersectan.
 *
 * @param a Rectángulo A
 * @param b Rectángulo B
 * @return 1 si intersectan, 0 si no
 *
 * Lógica:
 * Dos rectángulos NO se intersectan si uno está completamente:
 * - a la izquierda
 * - a la derecha
 * - arriba
 * - abajo
 */
int interseccion(MBR a, MBR b){

    // A está completamente a la izquierda de B
    if (a.xmax < b.xmin)
        return 0;

    // A está completamente a la derecha de B
    if (a.xmin > b.xmax)
        return 0;

    // A está completamente abajo de B
    if (a.ymax < b.ymin)
        return 0;

    // A está completamente arriba de B
    if (a.ymin > b.ymax)
        return 0;

    return 1;
}

/**
 * Realiza una búsqueda por rango sobre un R-tree almacenado en disco.
 *
 * @param f Archivo binario del árbol
 * @param nodeIndex Índice del nodo actual en el archivo
 * @param query Rectángulo de consulta
 * @param io_count Contador de accesos a disco (IO)
 * @return cantidad de puntos encontrados
 *
 * Funcionamiento:
 * - Lee el nodo desde disco
 * - Recorre sus hijos
 * - Si no intersecta → se descarta
 * - Si es hoja → cuenta punto
 * - Si es interno → recursión
 */
int rangeQuery(FILE* f, int nodeIndex, MBR query, int* io_count) {

    if (nodeIndex < 0) {
        printf("Indice invalido: %d\n", nodeIndex);
        return 0;
    }

    Nodo nodo;
    int encontrados = 0;

    fseek(f, nodeIndex * sizeof(Nodo), SEEK_SET);

    if (fread(&nodo, sizeof(Nodo), 1, f) != 1) {
        printf("Error leyendo nodo en índice %d\n", nodeIndex);
        return 0;
    }

    (*io_count)++;

    if (nodo.k < 0 || nodo.k > 204) {
        printf("Nodo corrupto en índice %d (k=%d)\n", nodeIndex, nodo.k);
        return 0;
    }

    for (int i = 0; i < nodo.k; i++) {

        hijo h = nodo.hijos[i];

        if (!interseccion(h.clave, query)) continue;

        if (h.valor == -1) {
            encontrados++;
        } else if (h.valor >= 0) {
            encontrados += rangeQuery(f, h.valor, query, io_count);
        }
    }

    return encontrados;
}

/**
 * Genera un cuadrado aleatorio dentro del espacio [0,1]².
 *
 * @param s lado del cuadrado
 * @return MBR con la query generada
 */
MBR generarQuery(float s) {
    MBR q;

    float x = (float)rand() / RAND_MAX;
    float y = (float)rand() / RAND_MAX;

    // asegurar que el cuadrado no salga del rango [0,1]
    if (x > 1.0 - s) x = 1.0 - s;
    if (y > 1.0 - s) y = 1.0 - s;

    q.xmin = x;
    q.ymin = y;
    q.xmax = x + s;
    q.ymax = y + s;

    return q;
}

/**
 * Calcula la desviación estándar de un conjunto de datos.
 *
 * @param arr arreglo de valores
 * @param n tamaño del arreglo
 * @param mean media de los datos
 * @return desviación estándar
 */
double stddev(double arr[], int n, double mean) {

    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double d = arr[i] - mean;
        sum += d * d;
    }

    return sqrt(sum / n);
}