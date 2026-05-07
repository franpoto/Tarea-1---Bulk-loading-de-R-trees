//
// Created by fabia on 2/5/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/Estructuras.h"
#include "../include/inits.h"



/**
 * lee puntos desde un archivo binario
 *
 * filename: nombre del archivo
 * N: cantidad de puntos a leer
 *
 * return:
 * arreglo de hijos
 */
hijo* leerDatos(const char* filename, int N) {
    FILE *f = fopen(filename, "rb");

    if (!f) {
        perror("Error abriendo archivo");
        exit(1);
    }

    hijo *arr = malloc(sizeof(hijo) * N);

    for (int i = 0; i < N; i++) {
        float x, y;

        fread(&x, sizeof(float), 1, f);
        fread(&y, sizeof(float), 1, f);

        arr[i] = crearPunto(x, y);
    }

    fclose(f);
    return arr;
}