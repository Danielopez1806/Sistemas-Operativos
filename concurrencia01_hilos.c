/*************************************************** 
/* Pontificia Universidad Javeriana
* Autor: Daniel Plazas
* Fichero: Concurencia01_hilos
* Objetivos:
  - Creacion de la funcion para hilos
  - Semaforos
  - Llamadas en funcion
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *funcion(void *job){ // funcion que ejecuta cada hilo creado
    size_t IDh = *(size_t *)job; // convertir el puntero recibido al valor del identificador del hilo
    int cont = 5 * IDh; // inicialiar la variable entera basada en el ID del hilo
    printf("\n Hilo %zu ha iniciado\n", IDh); // muestra un mensaje indicando el inicio del hilo
    
    for (int i = 0; i < 230; i++){ // for para realizar un proceso iterativo de calculo
        cont *= (cont+1); // se actualiza la variable cont de forma que se vaya acomulando
    }
    printf("\n Hilo %zu ha finalizado\n", IDh); // muestra un mensaje indicando que el hilo ha terminado
    
    return NULL; 
}

int main(){ 
    size_t jobs[3]; // hacemos un vector para almacenar los trabajos o identificadores de los hilos
    pthread_t hilos[3]; // aqui el vector para almacenar los identificadores de los hilos POSIX
    int i = 0; // Variable iteradora para el bucle
    int error; // Variable para capturar codigos de error en caso de fallo

    while (i < 3) { // ciclo while para crear secuencialmente los hilos
        jobs[i] = i; 
        error = pthread_create(&hilos[i], NULL, &funcion, jobs+i); // Crea el hilo y evalua su creacion
        if (error != 0) // if para validar si hubo algun error al crear el hilo
            printf("\nError en la creacion de hilos: [%s]", strerror(error)); // mostrar el mensaje de error correspondiente
        i++; 
    }

    //Esperamos a q los hilos terminen su ejecucion
    pthread_join(hilos[0], NULL); 
    pthread_join(hilos[1], NULL); 
    pthread_join(hilos[2], NULL); 

    return 0; 
    
    }
