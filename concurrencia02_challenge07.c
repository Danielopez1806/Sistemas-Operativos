/****************************************************
# Pontificia Universidad Javeriana
# Autor: Daniel Plazas
# Fichero: concurrencia02_challenge07
# Objetivos:
#   - Paso de argumentos a hilos mediante punteros void
#   - Creacion de hilos POSIX con pthread_create
#   - Sincronizacion basica con pthread_join
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_LOOPS 900000000 

long long sum = 0; // Variable global inicializada en cero

void* function(void *arg) { // Funcion que ejecuta el hilo recibiendo un argumento generico
    int valor = *(int *)arg; // Convierte el puntero void recibido a un puntero entero y extrae su valor
    
    for (int i = 0; i < NUM_LOOPS; i++){ // ciclo for que se ejecuta NUM_LOOPS veces de manera iterativa
        sum += valor; // acumulacar sobre la variable 
    }
    
    return NULL; // Retorna NULL al finalizar la ejecucion de la funcion del hilo
}

int main(void) { // Funcion principal del programa
    pthread_t id01; // variable para almacenar el identificador del hilo 
    int val = 1; // Variable local que se va a pasar como argumento al hilo
    printf("Sum inicial = %lld\n", sum); // muestraa el valor inicial de la suma global antes de crear el hilo
    
    // creamos el hilo pasando la direccion de la variable val como argumento hacia la funcion
    if (pthread_create(&id01, NULL, function, &val) != 0) {
        printf("Error al crear el hilo\n"); // mostrar error en la creacion 
        return 1; 
    }

    // Espera a que el hilo termine su ejecucion 
    pthread_join(id01, NULL);

    printf("Sum final = %lld\n", sum); // mostrar el resultado acumulado despues de la ejecucion del hilo

    return 0; 
}
