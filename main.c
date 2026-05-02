#include <stdio.h>


#include <stdlib.h>
#include <time.h>
#include "Estructuras.h"
#include "leerArchivos.h"
#include "inits.h"
#include "nearestx.h"


int main(void) {
    printf("Hello, World!\n");



    //EXPERIMENTACION NEAREST X CON DATOS RANDOM
    for (int exp = 15; exp <= 24; exp++) {

        int N = 1 << exp;

        printf("Probando N = %d\n", N);

        hijo *puntos = leerDatos("random.bin", N);

        inicializarArbol();

        clock_t inicio = clock();

        nearestX(puntos, N);

        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("Tiempo: %.4f segundos\n\n", tiempo);

        free(puntos);
    }

}
