#include <stdio.h>


#include <stdlib.h>
#include <time.h>
#include "Estructuras.h"
#include "leerArchivos.h"
#include "inits.h"
#include "nearestx.h"
#include "query.h"
#include "str.h"


int main(void) {
    printf("Hello, World!\n");
    int num_queries = 10;
    float tamaños[] = {0.01, 0.02, 0.05};



    //EXPERIMENTACION NEAREST X CON DATOS RANDOM
    for (int exp = 15; exp <= 24; exp++) {

        int N = 1 << exp;

        printf("Probando (random) N = %d\n", N);

        hijo *puntos = leerDatos("random.bin", N);

        inicializarArbol();

        clock_t inicio = clock();

        nearestX(puntos, N);

        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("Tiempo: %.4f segundos\n\n", tiempo);
        // guardar en disco
        guardarArbol("rtree.bin");

        FILE *f = fopen("rtree.bin", "rb");

        if (!f) {
            printf("Error abriendo archivo\n");
            return 1;
        }

        // probar queries
        for (int t = 0; t < 3; t++) {

            float s = tamaños[t];

            int total_io = 0;
            int total_puntos = 0;

            for (int q = 0; q < num_queries; q++) {

                MBR query = generarQuery(s);
                int io = 0;

                int encontrados = rangeQuery(f, 0, query, &io);

                total_io += io;
                total_puntos += encontrados;
            }

            printf("s=%.3f -> avg puntos=%.2f, avg IO=%.2f\n",
                   s,
                   (double)total_puntos / num_queries,
                   (double)total_io / num_queries);
        }

        fclose(f);

        free(puntos);
    }

    //EXPERIMENTACION NEAREST X CON EUROPA
    for (int exp = 15; exp <= 24; exp++) {

        int N = 1 << exp;

        printf("Probando (europa) N = %d\n", N);

        hijo *puntos = leerDatos("europa.bin", N);

        inicializarArbol();

        clock_t inicio = clock();

        nearestX(puntos, N);

        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("Tiempo: %.4f segundos\n\n", tiempo);

        guardarArbol("rtree.bin");

        FILE *f = fopen("rtree.bin", "rb");

        if (!f) {
            printf("Error abriendo archivo\n");
            return 1;
        }

        for (int t = 0; t < 3; t++) {

            float s = tamaños[t];

            int total_io = 0;
            int total_puntos = 0;

            for (int q = 0; q < num_queries; q++) {

                MBR query = generarQuery(s);
                int io = 0;

                int encontrados = rangeQuery(f, 0, query, &io);

                total_io += io;
                total_puntos += encontrados;
            }

            printf("s=%.3f -> avg puntos=%.2f, avg IO=%.2f\n",
                   s,
                   (double)total_puntos / num_queries,
                   (double)total_io / num_queries);
        }

        fclose(f);

        free(puntos);
    }

    // STR RANDOM
    for (int exp = 15; exp <= 24; exp++) {

        int N = 1 << exp;

        printf("Probando STR (random) N = %d\n", N);

        hijo *puntos = leerDatos("random.bin", N);

        inicializarArbol();

        clock_t inicio = clock();

        buildSTR(puntos, N);

        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("Tiempo: %.4f segundos\n\n", tiempo);

        guardarArbol("str.bin");

        FILE *f = fopen("str.bin", "rb");
        if (!f) {
            printf("Error abriendo STR\n");
            return 1;
        }

        // 🔥 queries igual que nearestX
        for (int t = 0; t < 3; t++) {

            float s = tamaños[t];

            int total_io = 0;
            int total_puntos = 0;

            for (int q = 0; q < num_queries; q++) {

                MBR query = generarQuery(s);
                int io = 0;

                int encontrados = rangeQuery(f, 0, query, &io);

                total_io += io;
                total_puntos += encontrados;
            }

            printf("s=%.3f -> avg puntos=%.2f, avg IO=%.2f\n",
                   s,
                   (double)total_puntos / num_queries,
                   (double)total_io / num_queries);
        }

        fclose(f);

        free(puntos);
    }

    // STR EUROPA
    for (int exp = 15; exp <= 24; exp++) {

        int N = 1 << exp;

        printf("Probando STR (europa) N = %d\n", N);

        hijo *puntos = leerDatos("europa.bin", N);

        inicializarArbol();

        clock_t inicio = clock();

        buildSTR(puntos, N);

        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("Tiempo: %.4f segundos\n\n", tiempo);

        guardarArbol("str.bin");

        FILE *f = fopen("str.bin", "rb");
        if (!f) {
            printf("Error abriendo STR\n");
            return 1;
        }


        for (int t = 0; t < 3; t++) {

            float s = tamaños[t];

            int total_io = 0;
            int total_puntos = 0;

            for (int q = 0; q < num_queries; q++) {

                MBR query = generarQuery(s);
                int io = 0;

                int encontrados = rangeQuery(f, 0, query, &io);

                total_io += io;
                total_puntos += encontrados;
            }

            printf("s=%.3f -> avg puntos=%.2f, avg IO=%.2f\n",
                   s,
                   (double)total_puntos / num_queries,
                   (double)total_io / num_queries);
        }

        fclose(f);
        free(puntos);
    }

}
