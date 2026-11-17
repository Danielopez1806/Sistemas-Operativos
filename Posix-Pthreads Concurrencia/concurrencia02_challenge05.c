/****************************************************
# Pontificia Universidad Javeriana
# Autor: Daniel Plazas
# Fichero: concurrencia02_challenge05
# Objetivos:
#   - Creacion de multiples funciones para hilos
#   - Creacion de hilos independientes con POSIX
#   - Sincronizacion y espera con pthread_join
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * f1(void * arg){ // funcion que ejecuta el primer hilo 
    printf(" porque soy el mejor!!"); // imprime un mensaje en pantalla por parte del hilo 1
    return NULL; 
}

void * f2(void * arg){ // Funcion que ejecuta el segundo hilo
    printf(" de forma rapida y divertida "); // muestra un mensaje en pantalla por parte del hilo 2
    return NULL; 
}

void * f3(void * arg){ // funcion que ejecuta el tercer hilo 
    printf(" Estoy aprendiendo "); // muestra un mensaje en pantalla por parte del hilo 3
    return NULL; 
}

int main() { 
    pthread_t thread01, thread02, thread03; // declaramos las variables para identificar los hilos
    
    //Creamos los hilos, en el caso del hilo 2 se sobrescribe y la asocia a la funcion 2
    pthread_create(&thread02, NULL, f1, NULL); 
    pthread_create(&thread02, NULL, f2, NULL); 
    pthread_create(&thread03, NULL, f3, NULL); 


    //Esperamos a los hilos acaben su ejecucion
    pthread_join(thread01, NULL); 
    pthread_join(thread02, NULL);
    pthread_join(thread03, NULL); 

    printf("\n"); 

    return 0; 
}
