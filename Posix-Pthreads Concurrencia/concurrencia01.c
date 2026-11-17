
/* Pontificia Universidad Javeriana
* Autor: Daniel Plazas
* Tema: Creacion de Hilos con el API de POSIX
* Objetivos:
	- Creacion de la funcion
	- Instancia de vectores de hilos posix
	- Llamadas en funcion
********************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


static void *funcionHilo(void *arg){ // Se crea la funcion que ejecutara cada hilo
    size_t job = *(size_t*)arg; // size_t castea a tipos de datos numericos sin signo
    printf("Trabajo %zu \n", job); // Imprime el identificador del trabajo actual
    return NULL; // Retorna NULL al finalizar la ejecucion
}

int main(int argc, char *argv[]){ // Funcion principal con argumentos de consola

    if (argc != 2){ // Valida que se ingrese exactamente un argumento ademas del ejecutable
        printf("Argumentos: \n\n ./ejecutable N \n"); // Muestra el mensaje de ayuda sobre el uso correcto
        exit(0); // Sale del programa si no se cumple la condicion
    }

    int N = (int)atoi(argv[1]); // Ingreso por consola del tamano de hilos
    size_t trabajos[N]; // Vector de trabajos de tamanio dinamico N
    pthread_t hilos[N]; // Instancia del vector de hilos de tamanio N

    for (int i = 0; i < N; i++) { // for  para inicializar y crear cada uno de los hilos
        trabajos[i] = i; // ponemos  un indice numerico al trabajo
        pthread_create(&hilos[i], NULL, funcionHilo, &trabajos[i]); // creamos el hilo enviando su referencia, funcion y argumentos
    }

    for (int i = 0; i < N; i++) { // for para esperar la finalizacion de cada hilo
        pthread_join(hilos[i], NULL); // Espera a que el hilo termine su ejecucion
    }

    return 0;
}
