/*
 * evolve.c
 *
 *	Creado el: 28/10/2013
 *        Autores: Mateo Restrepo - Mateo Jimenez
 *
 *        Programa que evoluciona el estado dinámico de las galaxias usando la rutina Runge-Kutta de cuarto orden.
 *        Durante el código se trabaja con unidades de Kiloparsecs, Giga-años, Tera-masas solares.
 *        Recibe el arreglo de condiciones iniciales condiciones_iniciales.dat
 *        Devuelve 5 archivos con posiciones y velocidades de las estrellas cada 10^9 años.
 */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "runge_kutta4.h"


//Este método permite crear arreglos que se graficarán con una posicion X y Y y una velocidad Vx y VY para cada estrella en diferentes tiempos.
int  main()
{
  int i,largoArchivo;
  largoArchivo= 120;

  //Se llama al metodo Runge-Kutta de cuarto orden llama y con las condiciones iniciales se inicia la rutina modificando las posiciones de las estrellas.

  //Dividir y Ordenar el array que arroja el Runge-Kutta con las posiciones y velocidades cada 10^9 años en un 5 archivos de tal forma que se puede graficar.


    return 28;
   
}
