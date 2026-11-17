/****************************************************
# Pontificia Universidad Javeriana
# Autor: Daniel Plazas
# Fichero: concurrencia02_challenge06
# Objetivos:
#   - Analisis de concurrencia en memoria compartida
#   - Modificacion concurrente de variables globales
#   - Analisis de consistencia en memoria compartida
****************************************************/

#include <stdio.h>
#include <stdlib.h>

#define NUM_LOOPS 900000000 

long long sum = 0; // Variable global que acomula y inicia en 0 

void function(int valor) { // funcion para las iteraciones sumando un valor recibido
    for (int i = 0; i < NUM_LOOPS; i++){ // for hasta NUM_LOOPS veces
        sum += valor; // acumulamos sobre la variable global compartida
    }
}

int main(void) { 
    function(1); // llamada a la funcion sumando 1 de forma consecutiva
    function(-1); // llamada a la funcion restando 1 de forma consecutiva 

    printf("Sum = %lld\n", sum); // muestra el resultado final acumulado en la variable global

    return 0; 
}
