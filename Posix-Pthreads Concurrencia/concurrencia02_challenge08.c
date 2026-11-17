/****************************************************
# Pontificia Universidad Javeriana
# Autor: Daniel Plazas
# Fichero: concurrencia02_challenge08
# Objetivos:
#   - Sincronizacion de hilos mediante semaforos POSIX
#   - Exclusion mutua en secciones criticas con sem_wait y sem_post
#   - Inicializacion y destruccion de semaforos
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex; // Semaforo global para controlar la exclusion mutua

void* operation(void* arg) { // funcion para e0jecutar los hilos concurrentes
    sem_wait(&mutex); // blopquemaos el semaforo antes la seccion critica   
    printf("\nEntered race..\n"); // muestra mensaje al entrar a la zona protegida
    sleep(4); //duerme 4 segundos
    printf("\nJust Exiting race...\n"); // imprimir mensaje al salir de la zona protegida
    sem_post(&mutex); // liberar el semaforo para abrir paso a otro hilo
    return NULL; // finde  la ejecucion del hilo
}

int main() { // 
    pthread_t thread01, thread02; // Ddeclarar los idenbtificadores de hilobc
    sem_init(&mutex, 0, 1); // inicializar el semaforo con valor 1 para exclusion mutua
    pthread_create(&thread01, NULL, operation, NULL); // lanza el primer hilo
    sleep(2); // duerme el hilo principal durante dos segundos
    pthread_create(&thread02, NULL, operation, NULL); // lanzo el segundo hilo
    // Espero a que ambos hilos terminen su ejecucion completamente
    pthread_join(thread01, NULL); 
    pthread_join(thread02, NULL); 

    sem_destroy(&mutex); // desstruir y libero los recursos del semaforo

    return 0; 
}
