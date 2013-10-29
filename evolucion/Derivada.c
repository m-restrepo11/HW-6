/*
 * Derivada.c
 *
 *	Creado el: 28/10/2013
 *        Autores: Mateo Restrepo - Mateo Jimenez
 *
 *        Programa que calcula las derivadas de las ecuaciones diferenciales acopladas.
 *        Durante el código se trabaja con unidades de Kiloparsecs, Giga-años, Tera-masas solares.
 *        Devuelve las cuatro derivadas de las ecuaciones diferenciales acopladas.
 */

#include <stdio.h>
#include <math.h>
#include "conversion.h"

double x_punto(double t,double x, double v_x,  double y,double v_y);
double y_punto(double t,double x, double v_x,  double y,double v_y);
double v_x_punto(double t,double x, double v_x,  double y,double v_y);
double v_y_punto(double t,double x, double v_x,  double y,double v_y);

double x_punto(double t,double x, double v_x,  double y,double v_y)
{
        return v_x;
}

double y_punto(double t,double x, double v_x,  double y,double v_y)
{
        return v_y;
}

double v_x_punto(double t,double x, double v_x,  double y,double v_y)
{
        return (-G_const())/pow(((x*x)+(y*y)),3.0/2.0);
}

double v_y_punto(double t,double x, double v_x,  double y,double v_y)
{
        return (-G_const())/pow(((x*x)+(y*y)),3.0/2.0);
}
