#include <stdio.h>


#include <stdlib.h>
#include <time.h>
#include "Estructuras.h"
#include "leerArchivos.h"
#include "inits.h"
#include "nearestx.h"
#include "query.h"
#include "str.h"

int num_queries = 100;
float tamaños[] = {0.0025, 0.005, 0.01, 0.025, 0.05};

int main(void) {
    printf("Hello, World!\n");


    FILE *out = fopen("resultados.csv", "w");
    if (!out) {
        printf("Error creando resultados.csv\n");
        return 1;
    }

    fprintf(out, "N,estructura,dataset,s,puntos,IO,std_puntos,tiempo\n");

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
        for (int t = 0; t < 5; t++) {

            float s = tamaños[t];

            double io_vals[100];
            double pts_vals[100];


            for (int q = 0; q < num_queries; q++) {

                MBR query = generarQuery(s);
                int io = 0;

                int encontrados = rangeQuery(f, 0, query, &io);

                io_vals[q] = io;
                pts_vals[q] = encontrados;
            }

            double sum_io = 0, sum_pts = 0;

            for (int i = 0; i < num_queries; i++) {
                sum_io += io_vals[i];
                sum_pts += pts_vals[i];
            }

            double avg_io = sum_io / num_queries;
            double avg_pts = sum_pts / num_queries;
            double sd_pts = stddev(pts_vals, num_queries, avg_pts);

            printf("s=%.4f -> pts=%.2f (std=%.2f), IO=%.2f\n",
                   s, avg_pts, sd_pts, avg_io);

            fprintf(out, "%d,nearestX,random,%.4f,%.2f,%.2f,%.2f,%.6f\n",
                    N, s, avg_pts, avg_io, sd_pts, tiempo);
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
        if (!f) return 1;

        for (int t = 0; t < 5; t++) {

            float s = tamaños[t];

            double io_vals[100];
            double pts_vals[100];

            for (int q = 0; q < num_queries; q++) {

                MBR query = generarQuery(s);
                int io = 0;

                int encontrados = rangeQuery(f, 0, query, &io);

                io_vals[q] = io;
                pts_vals[q] = encontrados;
            }

            double sum_io = 0, sum_pts = 0;

            for (int i = 0; i < num_queries; i++) {
                sum_io += io_vals[i];
                sum_pts += pts_vals[i];
            }

            double avg_io = sum_io / num_queries;
            double avg_pts = sum_pts / num_queries;
            double sd_pts = stddev(pts_vals, num_queries, avg_pts);

            printf("s=%.4f -> pts=%.2f (std=%.2f), IO=%.2f\n",
                   s, avg_pts, sd_pts, avg_io);

            fprintf(out, "%d,nearestX,europa,%.4f,%.2f,%.2f,%.2f,%.6f\n",
                    N, s, avg_pts, avg_io, sd_pts, tiempo);
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

        int root = buildSTR(puntos, N);
        guardarArbol("str.bin");


        FILE *f = fopen("str.bin", "rb");
        if (!f) return 1;

        for (int t = 0; t < 5; t++) {

            float s = tamaños[t];

            double io_vals[100];
            double pts_vals[100];

            for (int q = 0; q < num_queries; q++) {

                MBR query = generarQuery(s);
                int io = 0;

                int encontrados = rangeQuery(f, root, query, &io);

                io_vals[q] = io;
                pts_vals[q] = encontrados;
            }

            double sum_io = 0, sum_pts = 0;

            for (int i = 0; i < num_queries; i++) {
                sum_io += io_vals[i];
                sum_pts += pts_vals[i];
            }

            double avg_io = sum_io / num_queries;
            double avg_pts = sum_pts / num_queries;
            double sd_pts = stddev(pts_vals, num_queries, avg_pts);

            printf("s=%.4f -> pts=%.2f (std=%.2f), IO=%.2f\n",
                   s, avg_pts, sd_pts, avg_io);

            fprintf(out, "%d,STR,random,%.4f,%.2f,%.2f,%.2f,%.6f\n",
                    N, s, avg_pts, avg_io, sd_pts, tiempo);
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

        int root = buildSTR(puntos, N);
        guardarArbol("str.bin");

        FILE *f = fopen("str.bin", "rb");
        if (!f) return 1;

        for (int t = 0; t < 5; t++) {

            float s = tamaños[t];

            double io_vals[100];
            double pts_vals[100];

            for (int q = 0; q < num_queries; q++) {

                MBR query = generarQuery(s);
                int io = 0;

                int encontrados = rangeQuery(f, root, query, &io);

                io_vals[q] = io;
                pts_vals[q] = encontrados;
            }

            double sum_io = 0, sum_pts = 0;

            for (int i = 0; i < num_queries; i++) {
                sum_io += io_vals[i];
                sum_pts += pts_vals[i];
            }

            double avg_io = sum_io / num_queries;
            double avg_pts = sum_pts / num_queries;
            double sd_pts = stddev(pts_vals, num_queries, avg_pts);

            printf("s=%.4f -> pts=%.2f (std=%.2f), IO=%.2f\n",
                   s, avg_pts, sd_pts, avg_io);

            fprintf(out, "%d,STR,europa,%.4f,%.2f,%.2f,%.2f,%.6f\n",
                    N, s, avg_pts, avg_io, sd_pts, tiempo);
        }

        fclose(f);
        free(puntos);
    }

    fclose(out);

}