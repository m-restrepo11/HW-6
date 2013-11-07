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
#define eps pow(10,-2) //Número epsilon para evitar infinitos. Evita que el denominador en el calculo de la fuerza gravitacional diverga cuando el denominador tiende a 0.
#define MASA pow(10,12)

//Devuelve la velocidad en x de la ecuación dx/dt=v_x
double x_punto(double t,double v_x/*velocidad en x de la n-ésima masa*/)
{
        return v_x;
}

//Devuelve la velocidad en y de la ecuación dy/dt=v_y
double y_punto(double t,double v_y/*velocidad en y de la n-ésima masa*/)
{
        return v_y;
}

//Devuelve la velocidad en x de las n-ésima estrella cuando solo hay interacción con un centro galáctico. dv_x/dt=-GM_1/r^(3/2).
double v_x_punto1(double t,double pos_x/*posición en x de la n-ésima masa*/, double pos_y/*posición en y de la n-ésima masa*/, double posM1_x, double posM1_y)
{
	double r, costheta;
	r = pow((pow((pos_x-posM1_x),2.0)+ pow((pos_y-posM1_y),2.0) + eps),1.0/2.0);
	costheta=(pos_x-posM1_x)/r;

	return ((-G_const()*MASA)/pow(r, 2.0)*costheta);
}

//Devuelve la velocidad en y de las n-ésima estrella cuando solo hay interacción con un centro galáctico. dv_y/dt=-GM_1/r^(3/2).
double v_y_punto1(double t,double pos_x/*posición en x de la n-ésima masa*/, double pos_y/*posición en y de la n-ésima masa*/, double posM1_x, double posM1_y)
{
	double r, sintheta;
		r = pow((pow((pos_x-posM1_x),2.0)+ pow((pos_y-posM1_y),2.0) + eps),1.0/2.0);
		sintheta=(pos_y-posM1_y)/r;

		return ((-G_const()*MASA)/pow(r , 2.0)*sintheta);
}

//Devuelve la velocidad en x de las n-ésima estrella cuando hay interacción con dos centros galácticos. dv_x/dt=-GM_1/r^(3/2)-GM_2/r^(3/2).
double v_x_punto2(double t,double pos_x/*posición en x de la n-ésima masa*/, double pos_y/*posición en y de la n-ésima masa*/, double posM1_x, double posM1_y, double posM2_x, double posM2_y)
{
	double r1, costheta1, r2, costheta2;
	r1 = pow((pow((pos_x-posM1_x),2.0)+ pow((pos_y-posM1_y),2.0) + eps),1.0/2.0);
	costheta1=(pos_x-posM1_x)/r1;

	r2 = pow((pow((pos_x-posM2_x),2.0)+ pow((pos_y-posM2_y),2.0) + eps),1.0/2.0);
	costheta2=(pos_x-posM2_x)/r2;


	return (((-G_const()*MASA)/pow(r1 , 2.0)*costheta1)+((-G_const()*MASA)/pow(r2 , 2.0)*costheta2));
}

//Devuelve la aceleración en y de las n-ésima estrella cuando hay interacción con dos centros galácticos. dv_x/dt=-GM_1/r^(3/2)-GM_2/r^(3/2).
double v_y_punto2(double t,double pos_x/*posición en x de la n-ésima masa*/, double pos_y/*posición en y de la n-ésima masa*/, double posM1_x, double posM1_y, double posM2_x, double posM2_y)
{
	double r1, sintheta1, r2, sintheta2;
		r1 = pow((pow((pos_x-posM1_x),2.0)+ pow((pos_y-posM1_y),2.0) + eps),1.0/2.0);
		sintheta1=(pos_y-posM1_y)/r1;

		r2 = pow((pow((pos_x-posM2_x),2.0)+ pow((pos_y-posM2_y),2.0) + eps),1.0/2.0);
		sintheta2=(pos_y-posM2_y)/r2;


		return (((-G_const()*MASA)/pow(r1, 2.0)*sintheta1)+((-G_const()*MASA)/pow(r2, 2.0)*sintheta2));
}

//Devuelve la aceleración en x el k-ésimo centro gálactico cuando interactua con en k+1-ésimo centro gálactico. dv_y/dt=-GM_1/r^(3/2).
double v_x_puntoMG1(double t,double posM1_x, double posM1_y, double posM2_x, double posM2_y)
{

		double r, costheta;
		r = pow((pow((posM1_x-posM2_x),2.0)+ pow((posM1_y-posM2_y),2.0) + eps ),1.0/2.0);
		costheta=(posM1_x-posM2_x)/r;
		return((-G_const()*MASA)/pow(r, 2.0)*costheta);

}

//Devuelve la aceleración en x el k-ésimo centro gálactico cuando interactua con en k+1-ésimo centro gálactico. dv_y/dt=-GM_1/r^(3/2).
double v_x_puntoMG2(double t,double posM1_x, double posM1_y, double posM2_x, double posM2_y)
{

		double r, costheta;
		r = pow((pow((posM2_x-posM1_x),2.0)+ pow((posM2_y-posM1_y),2.0) + eps),1.0/2.0);
		costheta=(posM2_x-posM1_x)/r;
		return((-G_const()*MASA)/pow(r, 2.0)*costheta);

}

//Devuelve la aceleración en y el k-ésimo centro gálactico cuando interactua con en k+1-ésimo centro gálactico. dv_y/dt=-GM_1/r^(3/2).
double v_y_puntoMG1(double t,double posM1_x, double posM1_y, double posM2_x, double posM2_y)
{

			double r, sintheta;
			r = pow((pow((posM1_x-posM2_x),2.0)+ pow((posM1_y-posM2_y),2.0) + eps),1.0/2.0);
			sintheta=(posM1_y-posM2_y)/r;
			return((-G_const()*MASA)/pow(r, 2.0)*sintheta);

}


//Devuelve la aceleración en y el k-ésimo centro gálactico cuando interactua con en k+1-ésimo centro gálactico. dv_y/dt=-GM_1/r^(3/2).
double v_y_puntoMG2(double t,double posM1_x, double posM1_y, double posM2_x, double posM2_y){
	double r, sintheta;
	r = pow((pow((posM2_x-posM1_x),2.0)+ pow((posM2_y-posM1_y),2.0) + eps),1.0/2.0);
	sintheta=(posM2_y-posM1_y)/r;

	return((-G_const()*MASA)/pow(r, 2.0)*sintheta);

}
