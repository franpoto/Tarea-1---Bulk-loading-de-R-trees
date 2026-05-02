cmake_minimum_required(VERSION 4.2)
project(untitled2 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled2 main.c
        Estructuras.h
        inits.h
        nearestx.c
        inits.c
        nearestx.h
        leerArchivos.h
        leerArchivos.c)
