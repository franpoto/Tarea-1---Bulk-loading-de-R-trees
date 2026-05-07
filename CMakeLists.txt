cmake_minimum_required(VERSION 4.2)
project(TAREA1AL C)

set(CMAKE_C_STANDARD 11)

add_executable(TAREA1AL src/main.c
        include/Estructuras.h
        include/inits.h
        src/nearestx.c
        src/inits.c
        include/nearestx.h
        include/leerArchivos.h
        src/leerArchivos.c
        src/query.c
        src/str.c
        include/str.h
        src/main.c
        include/query.h

)
