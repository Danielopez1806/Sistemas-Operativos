/****************************************************
# Pontificia Universidad Javeriana
# Autor: Daniel Plazas
# Fichero: concurrencia02_challenge09
# Objetivos:
#   - Sincronizacion de hilos con semaforos POSIX
#   - Proteccion de secciones criticas con sem_wait y sem_post
#   - Control de condiciones en operaciones de incremento y decremento
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

long balance = 0; // variable global que almacena el balance
sem_t mutex; // baqui va un semaforoo para controlar la exclusion mutua de los hilos

void * increment(void * arg){ // funcion del hilo para ibncrementar de forma masiva al balance
    for(long i = 0; i < 10000000; i++){ // for con demasiadas iteraciones
        sem_wait(&mutex); // bloqueaos el semaforo para entrar a la seccion critica
        balance++; // incrementar la variable global 
        sem_post(&mutex); // liberar el semaforo saliendo de la seccion critica
    }
    pthread_exit(NULL); // finalizr la ejecucion de este hilo
}

void * decrement(void * arg){ // funcion del hilo para decremebntar
    for(long j = 0; j < 10000000; j++){ // for con muchas iteraciones
        sem_wait(&mutex); // bloqueamos el semaforo antes de modificar la variable
        balance--; // decrementar la variable global
        sem_post(&mutex); // desbloquear el semaforo para permitir el paso
    }
    pthread_exit(NULL); // Termino la ejecucion de este hilo
}

int main(){ 
    pthread_t thread1, thread2; // declarar los hilos
    sem_init(&mutex, 0, 1); // inicializar el semaforo en 1 para exclusion mutua


    //lanzamos los hilos de incremento y decremento
    pthread_create(&thread1, NULL, increment, NULL); 
    pthread_create(&thread2, NULL, decrement, NULL); 

    // Espero a que ambos hilos terminen todo su trabajo
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Value of balance is :%ld\n", balance); // muestro el resultado final despues de sincronizar

    sem_destroy(&mutex); // destruir el semaforo y libero recursos

    return 0; 
}
