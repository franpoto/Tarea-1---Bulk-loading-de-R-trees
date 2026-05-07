#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// cantidad maxima de hijos por nodo
#define B 204

/**
 * rectangulo minimo contenedor
 */
typedef struct {
    float xmin, xmax, ymin, ymax;
} MBR;

/**
 * representa un hijo dentro del arbol
 * clave: rectangulo asociado
 * valor: indice del nodo hijo
 */
typedef struct {
    MBR clave;
    int valor;
} hijo;

/**
 * representa un nodo del arbol
 * k: cantidad de hijos usados
 * hijos: arreglo de hijos
 * pad: relleno para ajustar tamaño
 */
typedef struct {
    int k;
    hijo hijos[B];
    int pad[12];
} Nodo;

#endif