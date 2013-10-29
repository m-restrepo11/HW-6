#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "runge_kutta4.h"
#include "IC1.h"

// este metodo permite crear arreglos que se grafican con una posicion X y Y y una velocidad Vx y VY para cada masa en diferentes tiempos.
int  main()
{
  int i,largoArchivo;
  largoArchivo= 120;

  // se llama al metodo runge kutta de cuarto orden llama el metodo de condiciones iniciales y los modifica con el runge kutta, despues de hacer este procedimiento el runge kutta arroja un arreglo de 5 columnas y 120*h filas.

  //ordenar el archivo de tal forma que se puede graficar 

  // se llama al metodo graficador de python para ver como cambia la posicion de la particula.

  //despues de esto se cree una nueva galaxia, llamando de nuevo el metodo condiciones iniciales 

  // se hace el metodo concatenar para tener en cuenta el efecto de ambos centros de masa en el espacio 


  //se vuelve a hacer le procedimiento anterior (runge kutta, ordenar y graficar )

    return 0;
   
}
