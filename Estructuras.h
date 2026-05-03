#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H


#define B 204
typedef struct {
    float xmin, xmax, ymin, ymax;
} MBR;

typedef struct {
    MBR clave;
    int valor;
} hijo;

typedef struct {
    int k;
    hijo hijos[B];
    int pad[12];
} Nodo;

#endif



