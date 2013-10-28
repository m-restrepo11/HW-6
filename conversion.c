/*
 * unidades.c
 *
 *  Creado  el: 22/10/2013
 *      Autores: Mateo Restrepo - Mateo Jimenez
 */
#include <stdio.h>
#include <math.h>
#define PARSEC 30000000000000000.0
#define YEAR 31540000.0

double G_const();
double  PI();
double Kms_KpcGyr(double value);
double KpcGyr_Kms(double value);
double Gyr_s(double value);
double Kpc_m(double value);
double Kpc_m(double value);

// Retorna el valor de la constante de gravitación en Kpc, G-año, Tera-Masa solar.
double  G_const(){
	
	return(4.46391e-6);
}

//Retorna el valor de Pi.
double  PI(){

	return(3.14159265358979323846);
}

//Convierte km/s a Kpc/G-año.
double Kms_KpcGyr(double value){
	
	return(value*1.022);
}

//Convierte Kpc/G-año a km/s.
double KpcGyr_Kms(double value){
	
	return(value*0.9785);
}


//Convierte G-año a segundos.
double Gyr_s(double value){

	return((value)*(YEAR)*(pow(10,9)));

}


//Convierte Kpc a metros.
double Kpc_m(double value){

	return((value)*(PARSEC)*(pow(10,3)));

}

//Convierte metros a Kpc.
double m_Kpc(double value){

	return((value)*(3.241)*(pow(10,-20)));

}



