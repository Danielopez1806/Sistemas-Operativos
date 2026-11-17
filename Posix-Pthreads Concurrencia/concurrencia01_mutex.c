/****************************************************

/* Pontificia Universidad Javeriana
* Autor: Daniel Plazas
* Fichero: Concurencia01_hilos
# Objetivos:
#   - Creacion de funciones para hilos
#   - Exclusion mutua con pthread_mutex
#   - Sincronizacion de secciones 
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t BLOQUEO; 

void *funcion(void *job){ // Funcion que ejecuta cada hilo creado
    pthread_mutex_lock(&BLOQUEO); // bloqueamos el mutex para entrar de forma exclusiva a la seccion critica
    size_t IDh = *(size_t *)job; // convertir el puntero recibido al valor del identificador del hilo
    int cont = 5 * IDh; // inicialiar la variable entera basada en el ID del hilo
    printf("\n Hilo %zu ha iniciado\n", IDh); // mostramos un mensaje indicando el inicio del hilo actual
    
    for (int i = 0; i < 230; i++){ // for para realizar un proceso iterativo de calculo
        cont *= (cont+1); // // se actualiza la variable cont de forma que se vaya acomulando
    }
      printf("\n Hilo %zu ha finalizado\n", IDh); // muestra un mensaje indicando que el hilo ha terminado
    pthread_mutex_unlock(&BLOQUEO); //  se desbloquea el mutex con unlock permitiendo que otro hilo pueda ingresar
    return NULL; 
}

int main(){ 
    size_t jobs[3]; // hacemos un vector para almacenar los trabajos o identificadores de los hilos
    pthread_t hilos[3]; // aqui el vector para almacenar los identificadores de los hilos POSIX
    int i = 0; // Variable iteradora para el bucle
    int error; // Variable para capturar codigos de error en caso de fallo

    if (pthread_mutex_init(&BLOQUEO, NULL) != 0) { // iniciamos el mutex y con if valida si ocurre un error
        printf("\n Fallo de inicializacion de MUTEX\n"); // Muestra mensaje en caso de fallo al inicializar
        return 1; //retorna 1 error si falla en la inicializacion
    }

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
    // Destruye y libera los recursos asignados al mutex
    pthread_mutex_destroy(&BLOQUEO); 

    return 0; // Finaliza la ejecucion del programa principal sin errores
}
