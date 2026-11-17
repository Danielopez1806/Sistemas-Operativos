/****************************************************
# Pontificia Universidad Javeriana
# Autor: Daniel Plazas
# Fichero: concurrencia02_challenge10
# Objetivos:
#   - Crear multiples hilos con funciones independientes
#   - Sincronizacion de ejecucion mediante pthread_join
#   - Analizar salida concurrente en consola
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * f1(void * arg){ // funcion ejecutada por el primer hilo
    printf(" porque soy el mejor!!"); // imprimir el fragmento final de la frase
    return NULL; // fin de este hilo
}

void * f2(void * arg){ // funcion del segundo hilo
    printf(" de forma rapida y divertida "); // Imprimo el fragmento central de la frase
    return NULL; // fin de este hilo
}

void * f3(void * arg){ // funcion ejecutada por el tercer hilo
    printf(" Estoy aprendiendo "); // imprimo el fragmento inicial de la frase
    return NULL; // fin de este hilo
}

int main() { 
    pthread_t thread01, thread02, thread03; // Declaracion de los identificadores para los hilos POSIX



    //Lanzamos los hilos asociados a las funciones que creamos al inicio
    pthread_create(&thread02, NULL, f1, NULL); 
    pthread_create(&thread02, NULL, f2, NULL); 
    pthread_create(&thread03, NULL, f3, NULL); 

    // Espero a que los hilos terminen su ejecucion en orden
    pthread_join(thread01, NULL); 
    pthread_join(thread02, NULL); 
    pthread_join(thread03, NULL); 

    printf("\n"); 

    return 0; 
}
