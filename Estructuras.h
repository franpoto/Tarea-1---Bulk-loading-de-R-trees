#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H



typedef struct {
    float xmin, xmax, ymin, ymax;
} MBR;

typedef struct {
    MBR clave;
    int valor;
} hijo;

typedef struct {
    hijo *hijos;
    int k;
    int pad[12];
} Nodo;

#endif



