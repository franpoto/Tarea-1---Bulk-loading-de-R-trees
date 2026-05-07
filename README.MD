# R-Tree Bulk Loading

Implementación de un R-Tree utilizando los algoritmos de bulk-loading:
- Nearest-X
- Sort-Tile-Recursive (STR)

Además, se implementaron consultas por rango sobre el árbol almacenado en disco.

# Compilación y ejecución

El proyecto fue desarrollado utilizando CLion y C.

Para ejecutar el programa:
1 Abrir el proyecto en CLion. 
2 Compilar normalmente.
3 Ejecutar `main.c`.

El proyecto debe ejecutarse usando el target de CMake (TAREA1AL) y no ejecutando `main.c` directamente.

En CLion:
- Ir a `Run > Edit Configurations`
- Seleccionar el target del proyecto generado por CMake
- No usar "Run main.c"

De lo contrario pueden aparecer errores del tipo:
`undefined reference to ...`
# Archivos necesarios

Los archivos `.bin` utilizados para las pruebas deben ubicarse en archivosBIN:
- `random.bin`
- `europa.bin`

