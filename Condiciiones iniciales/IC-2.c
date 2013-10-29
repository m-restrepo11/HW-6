/*
 * IC-2.c
 *
 *  Creado  el: 28/10/2013
 *      Autores: Mateo Restrepo - Mateo Jimenez
 *
 *      Este programa genera las condiciones iniciales (posiciones y velocidades) para que las 120 partículas
 *      de la segunda galaxia de disco orbiten de manera estable en círculos alrededor de la masa central.
 *      Durante el código se trabaja con unidades de Kiloparsecs, Giga-años, Tera-masas solares.
 *
 *     Se receiben 4 datos ingresados por el usuario al momento de la ejecución del programa: posición inicial en X y en Y;
 *     y velocidad inicial en X y en Y de la masa central.
 *     Devuelve un archivo .dat que contiene las posiciones y velocidades de 120 estrellas en orbita circular estable.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "conversion.h"

int main(int argc, char **argv) {

	//Revisar la cantidad de argumentos que entran por consola. Si es menor a 5 mostrar mensaje de error y abortar la ejecución.
	if (argc!=5){
		printf("Se necesitan 4 parámetros para iniciar el simulador");
		exit(1);
	}

	//Iniciar condiciones de la masa central de acuerdo a los datos ingresados por consola.
	double x0=atof(argv[1]);
	double y0=atof(argv[2]);
	//Convirtiendo las velocidades de entrada de Km/s a Kpc/Gyr.
	double v_x0=Kms_KpcGyr(atof(argv[3]));
	double v_y0=Kms_KpcGyr(atof(argv[4]));


	//Variables tontas para ciclos y demas.
	int i,j;

	//Incilizar el valor de G*M en unidades de Kpc, Gyr, T-masa solar.
	double mu = G_const()*1;

	//Inicializar variables para el radio y el angulo de las masa.
	int radio;
	double angulo;
	double v_tan;

	//Inicializar el Archivo donde se guardaran los datos de las posiciones y velocidades de las partículas.
	FILE *datos;
	char *nombre = "Condiciones_Iniciales2.dat";

	//Inicializacion de areglos de posiciones y velocidades con reserva de memoria.
	float *x_array;
	float *y_array;
	float *vx_array;
	float *vy_array;

	x_array = malloc(120 * sizeof(double));
	y_array = malloc(120 * sizeof(double));
	vx_array = malloc(120 * sizeof(double));
	vy_array = malloc(120 * sizeof(double));

	//Escribir condiciones iniciales de la masa central en el archivo.
	datos = fopen(nombre, "w");
	fprintf(datos,"%d %f %f %f %f \n", -2, x0, y0, v_x0, v_y0);
	fclose(datos);

	//Calcular y Escribir condiciones iniciales de las masas en la primera orbita en el archivo.
	radio = 10.0;
	angulo = (2*PI())/12.0;
	v_tan = sqrt(mu/radio);
	j = 0;
	//Abre el archivo con el flag a para agregar los datos despues de la última linea escrita.
	datos = fopen(nombre, "a");

	for(i=0; i<12; i++){
		x_array[i] = x0 + radio*cos(angulo*j);
		y_array[i] = y0 + radio*sin(angulo*j);
		vx_array[i] = v_x0 + v_tan*sin(angulo*j);
		vy_array[i] = v_y0 + v_tan*cos(angulo*j);
		fprintf(datos, "%d %f %f %f %f \n", i+100, x_array[i], y_array[i], vx_array[i], vy_array[i]);
		j++;
	}
	fclose(datos);

	//Calcular y Escribir condiciones iniciales de las masas en la segunda orbita en el archivo.
	radio = 20.0;
	angulo = (2*PI())/18.0;
	v_tan = sqrt(mu/radio);
	j = 0;
	//Abre el archivo con el flag a para agregar los datos despues de la última línea escrita.
	datos = fopen(nombre, "a");

	for(i=12; i<30; i++){
		x_array[i] = x0 + radio*cos(angulo*j);
		y_array[i] = y0 + radio*sin(angulo*j);
		vx_array[i] = v_x0 + v_tan*sin(angulo*j);
		vy_array[i] = v_y0 + v_tan*cos(angulo*j);
		fprintf(datos, "%d %f %f %f %f \n", i+100, x_array[i], y_array[i], vx_array[i], vy_array[i]);
		j++;
	}
	fclose(datos);

	//Calcular y Escribir condiciones iniciales de las masas en la tercera orbita en el archivo.
	radio = 30.0;
	angulo = (2*PI())/24.0;
	v_tan = sqrt(mu/radio);
	j = 0;
	//Abre el archivo con el flag a para agregar los datos despues de la última línea escrita.
	datos = fopen(nombre, "a");

	for(i=30; i<54; i++){
		x_array[i] = x0 + radio*cos(angulo*j);
		y_array[i] = y0 + radio*sin(angulo*j);
		vx_array[i] = v_x0 + v_tan*sin(angulo*j);
		vy_array[i] = v_y0 + v_tan*cos(angulo*j);
		fprintf(datos, "%d %f %f %f %f \n", i+100, x_array[i], y_array[i], vx_array[i], vy_array[i]);
		j++;
	}
	fclose(datos);

	//Calcular y Escribir condiciones iniciales de las masas en la cuarta orbita en el archivo.
	radio = 40.0;
	angulo = (2*PI())/30.0;
	v_tan = sqrt(mu/radio);
	j = 0;
	//Abre el archivo con el flag a para agregar los datos despues de la última línea escrita.
	datos = fopen(nombre, "a");

	for(i=54; i<84; i++){
		x_array[i] = x0 + radio*cos(angulo*j);
		y_array[i] = y0 + radio*sin(angulo*j);
		vx_array[i] = v_x0 + v_tan*sin(angulo*j);
		vy_array[i] = v_y0 + v_tan*cos(angulo*j);
		fprintf(datos, "%d %f %f %f %f \n", i+100, x_array[i], y_array[i], vx_array[i], vy_array[i]);
		j++;
	}
	fclose(datos);

	//Calcular y Escribir condiciones iniciales de las masas en la Quinta orbita en el archivo.
	radio = 50.0;
	angulo = (2*PI())/36.0;
	v_tan = sqrt(mu/radio);
	j = 0;
	//Abre el archivo con el flag a para agregar los datos despues de la última línea escrita.
	datos = fopen(nombre, "a");

	for(i=84; i<120; i++){
		x_array[i] = x0 + radio*cos(angulo*i);
		y_array[i] = y0 + radio*sin(angulo*i);
		vx_array[i] = v_x0 + v_tan*sin(angulo*i);
		vy_array[i] = v_y0 + v_tan*cos(angulo*i);
		fprintf(datos, "%d %f %f %f %f \n", i+100, x_array[i], y_array[i], vx_array[i], vy_array[i]);
		j++;
	}
	fclose(datos);

return 8848;
}


