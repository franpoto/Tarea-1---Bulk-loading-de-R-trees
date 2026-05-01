//
// Created by fabia on 1/5/2026.
//



#include <stdio.h>

int B=204;

typedef struct {
    float xmin, xmax, ymin, ymax;
} MBR;

typedef struct {
    MBR clave;
    int valor;
} hijo;

typedef struct {
    hijo * hijos;
    int k;
    int pad[12];

} Nodo;







