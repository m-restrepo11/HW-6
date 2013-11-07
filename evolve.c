/*
 * RK4.c
 *
 *  Created on: 31/10/2013
 *      Author: systemmanager
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "conversion.h"
#include  "derivada.h"
#define eps pow(10,-2) //Número epsilon para evitar infinitos.


int contar(char *texto ){
	int c;
	FILE *in;
	int contador;

	in = fopen(texto, "r");

	contador = 0;
	do {
		c=fgetc(in);
		if(c=='\n'){
			contador++;
		}
	}while(c != EOF);

	fclose(in);
	return contador;
}


int main (int argc, char** argv)
{
	//Abrir el archivo
	FILE* file;
	file = fopen(argv[1], "r");

	//Si no hay argumentos salir del programa.
	if(argc<2){
		printf("No se recibe el archivo.\n");
		exit(496);
	}

	if(!(file=fopen(argv[1], "r"))){
		printf("Problema abriendo el archivo %s\n", argv[1]);
		exit(1);
	}

	//Declaración de arreglos de condiciones iniciales.
	double *id_array;
	double *x0_array;
	double *y0_array;
	double *vx0_array;
	double *vy0_array;
	double *masa_central1;
	double *masa_central2;

	//Declaración de números usados durante el programa.
	int i,j,k, N, np, nc, id;
	double h;

	h = 0.001;//Paso
	N = 5;//Límite de la iteracion.
	np = (int)(N+h)/h;
	nc=contar(argv[1]);//Número de lineas del archivo.

	//reserva de memoria para arreglos.
	id_array = malloc(nc * sizeof(double));
	x0_array = malloc(nc * sizeof(double));
	y0_array = malloc(nc * sizeof(double));
	vx0_array = malloc(nc * sizeof(double));
	vy0_array = malloc(nc * sizeof(double));
	masa_central1 = malloc(5 * sizeof(double));
	masa_central1 = malloc(5 * sizeof(double));


	double k1xM1 =0;
	double k1yM1 =0;
	double l1xM1 =0;
	double l1yM1 =0;

	double k2xM1 =0;
	double k2yM1 =0;
	double l2xM1 =0;
	double l2yM1 =0;

	double k3xM1 =0;
	double k3yM1 =0;
	double l3xM1 =0;
	double l3yM1 =0;

	double k4xM1 =0;
	double k4yM1 =0;
	double l4xM1 =0;
	double l4yM1 =0;

	double avgkxM1=0;
	double avgkyM1=0;
	double avglxM1=0;
	double avglyM1=0;

	double k1xM2 =0;
	double k1yM2 =0;
	double l1xM2 =0;
	double l1yM2 =0;

	double k2xM2 =0;
	double k2yM2 =0;
	double l2xM2 =0;
	double l2yM2 =0;

	double k3xM2 =0;
	double k3yM2 =0;
	double l3xM2 =0;
	double l3yM2 =0;

	double k4xM2 =0;
	double k4yM2 =0;
	double l4xM2 =0;
	double l4yM2 =0;

	double avgkxM2=0;
	double avgkyM2=0;
	double avglxM2=0;
	double avglyM2=0;

	double k1x =0;
	double k1y =0;
	double l1x =0;
	double l1y =0;

	double k2x =0;
	double k2y =0;
	double l2x =0;
	double l2y =0;

	double k3x =0;
	double k3y =0;
	double l3x =0;
	double l3y =0;

	double k4x =0;
	double k4y =0;
	double l4x =0;
	double l4y =0;

	double avgkx =0;
	double avgky =0;
	double avglx =0;
	double avgly =0;

	//Lectura del archivo de condiciones iniciales. Llenado de arreglos de posiciones y velocidades.
	for(i=0; i<nc; i++){

		fscanf(file, "%lf %lf %lf %lf %lf\n", &id_array[i], &x0_array[i], &y0_array[i], &vx0_array[i], &vy0_array[i]);
	}

	printf("LEYENDO EL ARCHIVO...\n");

	fclose(file);



	//Llenar arreglos con las condiciones de las masas centrales.
	for(i=0; i<nc; i++){

		if(id_array[i]<0){

			//Para las masa central 1.
			if(id_array[i]==-1){
				k=i;
				masa_central1[0]=id_array[k];
				masa_central1[1]=x0_array[k];
				masa_central1[2]=y0_array[k];
				masa_central1[3]=vx0_array[k];
				masa_central1[4]=vy0_array[k];
			}
		}
	}

	printf("ARCHIVO LEIDO CON EXITO...\n");

	//Arreglos usados durante el RK4.
	double *x;
	double *y;
	double *vx;
	double *vy;
	double *t;

	double *xsol1;
	double *ysol1;
	double *xsol2;
	double *ysol2;
	double *xsol3;
	double *ysol3;
	double *xsol4;
	double *ysol4;
	double *xsol5;
	double *ysol5;

	//Reserva de memoria para arreglos.
	x=(double *) malloc(nc*sizeof(double*));
	y=(double *) malloc(nc*sizeof(double*));
	vx=(double *) malloc(nc*sizeof(double*));
	vy=(double *) malloc(nc*sizeof(double*));

	xsol1=(double *) malloc(nc*sizeof(double*));
	ysol1=(double *) malloc(nc*sizeof(double*));
	xsol2=(double *) malloc(nc*sizeof(double*));
	ysol2=(double *) malloc(nc*sizeof(double*));
	xsol3=(double *) malloc(nc*sizeof(double*));
	ysol3=(double *) malloc(nc*sizeof(double*));
	xsol4=(double *) malloc(nc*sizeof(double*));
	ysol4=(double *) malloc(nc*sizeof(double*));
	xsol5=(double *) malloc(nc*sizeof(double*));
	ysol5=(double *) malloc(nc*sizeof(double*));


	//Reserva de memoria para el arreglo de tiempos.
	t = malloc(np * sizeof(double));

	//Condición inicial del tiempo.
	t[0]=0;
	id=0;

	//Llenar los arreglos con las condiciones iniciales de la i-ésima masa.
	for(i=0; i<nc;i++){
		x[i]=x0_array[i];
		y[i]=y0_array[i];
		vx[i]=vx0_array[i];
		vy[i]=vy0_array[i];
	}

	printf("INICIANDO LA RUTINA RK4...\n");
	//CHECKPOINT!


	if(nc==121){

		for(j=1; j<np; j++){
			for(i=0; i<nc; i++){

				id=1;

				//Primer paso.
				double k1x = x_punto(t[j-1],vx[i]);
				double k1y = y_punto(t[j-1],vy[i]);
				double l1x = v_x_punto1(t[j-1],x[i],y[i],masa_central1[1],masa_central1[2]);
				double l1y = v_y_punto1(t[j-1],x[i],y[i],masa_central1[1],masa_central1[2]);

				double t1 = t[j-1] + (h/2.0);
				double x1=x[i] + (h/2.0)*k1x;
				double y1=y[i] + (h/2.0)*k1y;
				double vx1=vx[i] + (h/2.0)*l1x;
				double vy1=vy[i] + (h/2.0)*l1y;

				//Segundo paso.
				double k2x = x_punto(t1,vx1);
				double k2y = y_punto(t1,vy1);
				double l2x = v_x_punto1(t1,x1,y1,masa_central1[1],masa_central1[2]);
				double l2y = v_y_punto1(t1,x1,y1,masa_central1[1],masa_central1[2]);

				double t2 = t[j-1] + (h/2.0);
				double x2=x[i] + (h/2.0)*k2x;
				double y2=y[i] + (h/2.0)*k2y;
				double vx2=vx[i] + (h/2.0)*l2x;
				double vy2=vy[i] + (h/2.0)*l2y;

				//Tercer paso.
				double k3x = x_punto(t2,vx2);
				double k3y = y_punto(t2,vy2);
				double l3x = v_x_punto1(t2,x2,y2,masa_central1[1],masa_central1[2]);
				double l3y = v_y_punto1(t2,x2,y2,masa_central1[1],masa_central1[2]);

				double t3 = t[j-1] + h;
				double x3=x[i] + h*k3x;
				double y3=y[i] + h*k3y;
				double vx3=vx[i] + h*l3x;
				double vy3=vy[i] + h*l3y;


				//Cuarto paso.
				double k4x = x_punto(t3,vx3);
				double k4y = y_punto(t3,vy3);
				double l4x = v_x_punto1(t3,x3,y3,masa_central1[1],masa_central1[2]);
				double l4y = v_y_punto1(t3,x3,y3,masa_central1[1],masa_central1[2]);

				double avgkx = (k1x + 2.0*k2x + 2*k3x + k4x)/6.0;
				double avgky = (k1y + 2.0*k2y + 2*k3y + k4y)/6.0;
				double avglx = (l1x + 2.0*l2x + 2*l3x + l4x)/6.0;
				double avgly = (l1y + 2.0*l2y + 2*l3y + l4y)/6.0;

				//Actualizar las i-ésima masa al j-ésimo intervalo de tiempo.
				t[j] = t[j-1] + h;
				x[i] = x[i] + h*avgkx;
				vx[i] = vx[i] + h*avglx;
				y[i] = y[i] + h*avgky;
				vy[i] = vy[i] + h*avgly;

				if (j==1000){
					xsol1[i]=x[i];
					ysol1[i]=y[i];

				}else if (j==2000) {
					xsol2[i]=x[i];
					ysol2[i]=y[i];
				}else if (j==3000) {
					xsol3[i]=x[i];
					ysol3[i]=y[i];
				}else if (j==4000) {
					xsol4[i]=x[i];
					ysol4[i]=y[i];
				}else if (j==4999) {
					xsol5[i]=x[i];
					ysol5[i]=y[i];
				}


			}

		}
	}

	else if(nc==242){
		for(j=1; j<np; j++){
			for(i=0; i<nc; i++){

				int pm1 = 0;
				int pm2 = 121;

				id=2;

				//EVOLUCIONA LA MASA CENTRAL DE LA PRIMERA GALAXIA.
				if(i==pm1)
				{
					//Primer paso.
					k1xM1 = x_punto(t[j-1],vx[pm1]);
					k1yM1 = y_punto(t[j-1],vy[pm1]);
					l1xM1 = v_x_puntoMG1(t[j-1],x[pm1],y[pm1],x[pm2],y[pm2]);
					l1yM1 = v_y_puntoMG1(t[j-1],x[pm1],y[pm1],x[pm2],y[pm2]);

					double t1M1 = t[j-1] + (h/2.0);
					double x1M1 = x[pm1] + (h/2.0)*k1xM1;
					double y1M1 = y[pm1] + (h/2.0)*k1yM1;
					double vx1M1 = vx[pm1] + (h/2.0)*l1xM1;
					double vy1M1 = vy[pm1] + (h/2.0)*l1yM1;

					//Segundo paso.
					k2xM1 = x_punto(t1M1,vx1M1);
					k2yM1 = y_punto(t1M1,vy1M1);
					l2xM1 = v_x_puntoMG1(t1M1,x1M1,y1M1,x[pm2],y[pm2]);
					l2yM1 = v_y_puntoMG1(t1M1,x1M1,y1M1,x[pm2],y[pm2]);

					double t2M1 = t[j-1] + (h/2.0);
					double x2M1 = x[pm1] + (h/2.0)*k2xM1;
					double y2M1 = y[pm1] + (h/2.0)*k2yM1;
					double vx2M1 = vx[pm1] + (h/2.0)*l2xM1;
					double vy2M1 = vy[pm1] + (h/2.0)*l2yM1;

					//Tercer paso.
					k3xM1 = x_punto(t2M1,vx2M1);
					k3yM1 = y_punto(t2M1,vy2M1);
					l3xM1 = v_x_puntoMG1(t2M1,x2M1,y2M1,x[pm2],y[pm2]);
					l3yM1 = v_y_puntoMG1(t2M1,x2M1,y2M1,x[pm2],y[pm2]);

					double t3M1 = t[j-1] + h;
					double x3M1 = x[pm1] + h*k3xM1;
					double y3M1 = y[pm1] + h*k3yM1;
					double vx3M1 = vx[pm1] + h*l3xM1;
					double vy3M1 = vy[pm1] + h*l3yM1;


					//Cuarto paso.
					k4xM1 = x_punto(t3M1,vx3M1);
					k4yM1 = y_punto(t3M1,vy3M1);
					l4xM1 = v_x_puntoMG1(t3M1,x3M1,y3M1,x[pm2],y[pm2]);
					l4yM1 = v_y_puntoMG1(t3M1,x3M1,y3M1,x[pm2],y[pm2]);

					avgkxM1 = (k1xM1 + 2.0*k2xM1 + 2*k3xM1 + k4xM1)/6.0;
					avgkyM1 = (k1yM1 + 2.0*k2yM1 + 2*k3yM1 + k4yM1)/6.0;
					avglxM1 = (l1xM1 + 2.0*l2xM1 + 2*l3xM1 + l4xM1)/6.0;
					avglyM1 = (l1yM1 + 2.0*l2yM1 + 2*l3yM1 + l4yM1)/6.0;
				}

					//EVOLUCIONA LA MASA CENTRAL DE LA SEGUNDA GALAXIA.
				else if(i==pm2)
				{
					//Primer paso.
					k1xM2 = x_punto(t[j-1],vx[pm2]);
					k1yM2 = y_punto(t[j-1],vy[pm2]);
					l1xM2 = v_x_puntoMG2(t[j-1],x[pm1],y[pm1],x[pm2],y[pm2]);
					l1yM2 = v_x_puntoMG2(t[j-1],x[pm1],y[pm1],x[pm2],y[pm2]);

					double t1M2 = t[j-1] + (h/2.0);
					double x1M2 = x[pm2] + (h/2.0)*k1xM2;
					double y1M2 = y[pm2] + (h/2.0)*k1yM2;
					double vx1M2 = vx[pm2] + (h/2.0)*l1xM2;
					double vy1M2 = vy[pm2]+ (h/2.0)*l1yM2;

					//Segundo paso.
					k2xM2 = x_punto(t1M2,vx1M2);
					k2yM2 = y_punto(t1M2,vy1M2);
					l2xM2 = v_x_puntoMG2(t1M2,x[pm1],y[pm1],x1M2,y1M2);
					l2yM2 = v_y_puntoMG2(t1M2,x[pm1],y[pm1],x1M2,y1M2);

					double t2M2 = t[j-1] + (h/2.0);
					double x2M2 = x[pm2] + (h/2.0)*k2xM2;
					double y2M2 = y[pm2] + (h/2.0)*k2yM2;
					double vx2M2 = vx[pm2] + (h/2.0)*l2xM2;
					double vy2M2 = vy[pm2] + (h/2.0)*l2yM2;

					//Tercer paso.
					k3xM2 = x_punto(t2M2,vx2M2);
					k3yM2 = y_punto(t2M2,vy2M2);
					l3xM2 = v_x_puntoMG2(t2M2,x[pm1],y[pm1],x2M2,y2M2);
					l3yM2 = v_y_puntoMG2(t2M2,x[pm1],y[pm1],x2M2,y2M2);

					double t3M2 = t[j-1] + h;
					double x3M2 = x[pm2] + h*k3xM2;
					double y3M2 = y[pm2] + h*k3yM2;
					double vx3M2 = vx[pm2] + h*l3xM2;
					double vy3M2 = vy[pm2] + h*l3yM2;


					//Cuarto paso.
					k4xM2 = x_punto(t3M2,vx3M2);
					k4yM2 = y_punto(t3M2,vy3M2);
					l4xM2 = v_x_puntoMG2(t3M2,x[pm1],y[pm1],x3M2,y3M2);
					l4yM2 = v_y_puntoMG2(t3M2,x[pm1],y[pm1],x3M2,y3M2);

					avgkxM2 = (k1xM2 + 2.0*k2xM2 + 2*k3xM2 + k4xM2)/6.0;
					avgkyM2 = (k1yM2 + 2.0*k2yM2 + 2*k3yM2 + k4yM2)/6.0;
					avglxM2 = (l1xM2 + 2.0*l2xM2 + 2*l3xM2 + l4xM2)/6.0;
					avglyM2 = (l1yM2 + 2.0*l2yM2 + 2*l3yM2 + l4yM2)/6.0;

				}

				//EVOLUCIONA LA I-ÉSIMA MASA.
				else
				{
					//Primer paso.
					k1x = x_punto(t[j-1],vx[i]);
					k1y = y_punto(t[j-1],vy[i]);
					l1x = v_x_punto2(t[j-1],x[i],y[i],x[pm1],y[pm1],x[pm2],y[pm2]);
					l1y = v_y_punto2(t[j-1],x[i],y[i],x[pm1],y[pm1],x[pm2],y[pm2]);

					double t1 = t[j-1] + (h/2.0);
					double x1=x[i] + (h/2.0)*k1x;
					double y1=y[i] + (h/2.0)*k1y;
					double vx1=vx[i] + (h/2.0)*l1x;
					double vy1=vy[i] + (h/2.0)*l1y;

					//Segundo paso.
					k2x = x_punto(t1,vx1);
					k2y = y_punto(t1,vy1);
					l2x = v_x_punto2(t[j-1],x[i],y[i],x[pm1],y[pm1],x[pm2],y[pm2]);
					l2y = v_y_punto2(t[j-1],x[i],y[i],x[pm1],y[pm1],x[pm2],y[pm2]);

					double t2 = t[j-1] + (h/2.0);
					double x2=x[i] + (h/2.0)*k2x;
					double y2=y[i] + (h/2.0)*k2y;
					double vx2=vx[i]+ (h/2.0)*l2x;
					double vy2=vy[i] + (h/2.0)*l2y;

					//Tercer paso.
					k3x = x_punto(t2,vx2);
					k3y = y_punto(t2,vy2);
					l3x = v_x_punto2(t[j-1],x[i],y[i],x[pm1],y[pm1],x[pm2],y[pm2]);
					l3y = v_y_punto2(t[j-1],x[i],y[i],x[pm1],y[pm1],x[pm2],y[pm2]);

					double t3 = t[j-1] + h;
					double x3=x[i] + h*k3x;
					double y3=y[i] + h*k3y;
					double vx3=vx[i] + h*l3x;
					double vy3=vy[i] + h*l3y;


					//Cuarto paso.
					k4x = x_punto(t3,vx3);
					k4y = y_punto(t3,vy3);
					l4x = v_x_punto2(t[j-1],x[i],y[i],x[pm1],y[pm1],x[pm2],y[pm2]);
					l4y = v_y_punto2(t[j-1],x[i],y[i],x[pm1],y[pm1],x[pm2],y[pm2]);

					avgkx = (k1x + 2.0*k2x + 2*k3x + k4x)/6.0;
					avgky = (k1y + 2.0*k2y + 2*k3y + k4y)/6.0;
					avglx = (l1x + 2.0*l2x + 2*l3x + l4x)/6.0;
					avgly = (l1y + 2.0*l2y + 2*l3y + l4y)/6.0;

				}

				if (i==pm1) {

					x[pm1] = x[pm1] + h*avgkxM1;
					vx[pm1] = vx[pm1] + h*avglxM1;
					y[pm1] = y[pm1] + h*avgkyM1;
					vy[pm1] = vy[pm1] + h*avglyM1;


				}else if (i==pm2) {

					x[pm2] = x[pm1] + h*avgkxM2;
					vx[pm2] = vx[pm1] + h*avglxM2;
					y[pm2] = y[pm1] + h*avgkyM2;
					vy[pm2] = vy[pm1] + h*avglyM2;
				}else if(i!=pm1 || i!=pm2) {

					//Actualizar las i-ésima masa al j-ésimo intervalo de tiempo.

					t[j] = t[j-1] + h;
					x[i] = x[i] + h*avgkx;
					vx[i] = vx[i] + h*avglx;
					y[i] = y[i] + h*avgky;
					vy[i] = vy[i] + h*avgly;

				}


				if (j==1000){
					xsol1[i]=x[i];
					ysol1[i]=y[i];

				}else if (j==2000) {
					xsol2[i]=x[i];
					ysol2[i]=y[i];
				}else if (j==3000) {
					xsol3[i]=x[i];
					ysol3[i]=y[i];
				}else if (j==4000) {
					xsol4[i]=x[i];
					ysol4[i]=y[i];
				}else if (j==4999) {
					xsol5[i]=x[i];
					ysol5[i]=y[i];
				}


			}
		}



	}





	printf("EXPORTANDO ARCHIVOS...\n");
	if(id==1){

		
		//Exportando archivos con datos de posiciones en X y Y para k*10^9 años | k={1,2,3,4,5}.
		//10^9
		FILE *datos;
		char *nombre1 = "1 Galaxia-10^9.dat";
		datos = fopen(nombre1, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol1[k], ysol1[k]);
		}
		fclose(datos);

		//2*10^9
		char *nombre2 = "1 Galaxia-2*10^9.dat";
		datos = fopen(nombre2, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol2[k], ysol2[k]);
		}

		//3*10^9
		fclose(datos);
		char *nombre3 = "1 Galaxia-3*10^9.dat";
		datos = fopen(nombre3, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol3[k], ysol3[k]);
		}
		fclose(datos);

		//4*10^9
		char *nombre4 = "1 Galaxia-4*10^9.dat";
		datos = fopen(nombre4, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol4[k], ysol4[k]);
		}
		fclose(datos);

		//5*10^9
		char *nombre5 = "1 Galaxia-5*10^9.dat";
		datos = fopen(nombre5, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol5[k], ysol5[k]);
		}
		fclose(datos);
	}else if (id==2) {

		//Exportando archivos con datos de posiciones en X y Y para k*10^9 años | k={1,2,3,4,5}.
		//10^9
		FILE *datos;
		char *nombre1 = "2 Galaxias-10^9.dat";
		datos = fopen(nombre1, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol1[k], ysol1[k]);
		}
		fclose(datos);

		//2*10^9
		char *nombre2 = "2 Galaxias-2*10^9.dat";
		datos = fopen(nombre2, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol2[k], ysol2[k]);
		}

		//3*10^9
		fclose(datos);
		char *nombre3 = "2 Galaxias-3*10^9.dat";
		datos = fopen(nombre3, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol3[k], ysol3[k]);
		}
		fclose(datos);

		//4*10^9
		char *nombre4 = "2 Galaxias-4*10^9.dat";
		datos = fopen(nombre4, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol4[k], ysol4[k]);
		}
		fclose(datos);

		//5*10^9
		char *nombre5 = "2 Galaxias-5*10^9.dat";
		datos = fopen(nombre5, "w");
		for(k=0; k<nc; k++){
			fprintf(datos, "%lf %lf %lf\n", id_array[k], xsol5[k], ysol5[k]);
		}
		fclose(datos);
	}

	printf("EJECUCIÓN EXITOSA!\n");

	return 9812;
}
