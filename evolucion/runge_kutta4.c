#include<stdio.h>
#include<math.h>
#include<stdlib.h>


//funcion de velocidad para runge -kutta 
double funcionVel(float t, float x,float v )
{
  float xi;
  
  xi= x+v*t;
  
  return xi;
}
//funcion de aceleracion para runge -kutta 
double funcionAce(float t,  float v,float g,float m,float r3)
{
  float vi;

  vi=v-(g*m/r3)*t;
  
  return vi;
}
//el metodo runge kutta :en donde se divide la ecuacion diferencial de segundo orden en dos de primer orden que son las funciones que se muestran arriba.
double  rungekutta(double *MatrizCondiciones)
{
  //entrada de parametros del metodo ic.c que nos manda un arreglo de posiciones para cada particula.
  
  int i,j,N;
  double t0, t,x0,y0,x,y,k[1000][1000],p,a,h,vx,vy,v0x,v0y,largoArchivo;
  double *Id,*X,*Y,*Vx,*Vy,F[1000][6];
  double g,m,r3;
  
  
  largoArchivo = 120.0;
  //en esta seccion se organizan los valores necesarios para el runge kutta, el metodo a continuacion solo sirve para una masa ya que es un esquema de lo que puede llegar a ser el metodo final
  
  Id =malloc(largoArchivo*sizeof(double));
  X =malloc(largoArchivo*sizeof(double));
  Y =malloc(largoArchivo*sizeof(double));
  Vx =malloc(largoArchivo*sizeof(double));
  Vy =malloc(largoArchivo*sizeof(double));

  //arreglo que guarda las posiciones finales y velocidades finales 

  for(i=0;i<largoArchivo;i++)
    {  
      MatrizCondiciones[1] = Id[i];
      MatrizCondiciones[2] = X[i];
      MatrizCondiciones[3] = Y[i];
      MatrizCondiciones[4] = Vx[i];
      MatrizCondiciones[5] = Vy[i];
    }
  h = 0.001 ; 
  N = 5 ;
  x0=X[0];
  y0=Y[0];
  v0x=Vx[0];
  v0y=Vy[0];
  t0=0;
    //metodo runge Kutta : ATENCION en este metodo se calcula las posiciones y con estas se calcullan las velocidades    
    for(i=0;i< N;i++)
    {
      for(j=1;j<largoArchivo;j++)
	{
	  //Este es el runge kutta para encontrar la posicion en X de la particula  
	  k[i][1]=h*funcionVel(t0,x0,v0x);
	  printf(" %lf ", k[i][1]);
	  k[i][2]=h*funcionVel(t0+0.5*h,x0+0.5*k[i][1],v0x);
	  k[i][3]=h*funcionVel(t0+0.5*h,x0+0.5*k[i][2],v0x);
	  k[i][4]=h*funcionVel(t0+h,x0+k[i][3],v0x);
	  k[i][5]=(1.0/6.0)*(k[i][1]+2*k[i][2]+2*k[i][3]+k[i][4]);
	  x=x0+k[i][5];
	  
	  //Este es el runge kutta para encontrar la posicion en Y de la particula  
	  k[i][1]=h*funcionVel(t0,y0,v0y);
	  printf(" %lf ", k[i][1]);
	  k[i][2]=h*funcionVel(t0+0.5*h,y0+0.5*k[i][1],v0y);
	  k[i][3]=h*funcionVel(t0+0.5*h,y0+0.5*k[i][2],v0y);
	  k[i][4]=h*funcionVel(t0+h,y0+k[i][3],v0y);
	  k[i][5]=(1.0/6.0)*(k[i][1]+2*k[i][2]+2*k[i][3]+k[i][4]);
	  y=y0+k[i][5];
	  
	  //Este es el runge kutta para encontrar la velocidad en X de la particula  
	  g = 10;
	  m = 5;
	  r3 = pow((pow((pow(y0,2)+pow(x0,2)),0.5)),3);
	  
	  k[i][1]=h*funcionAce(t0,v0x,g,m,r3);
	  printf(" %lf ", k[i][1]);
	  k[i][2]=h*funcionAce(t0+0.5*h,v0x+0.5*k[i][1],g,m,r3);
	  k[i][3]=h*funcionAce(t0+0.5*h,v0x+0.5*k[i][2],g,m,r3);
	  k[i][4]=h*funcionAce(t0+h,v0x+k[i][3],g,m,r3);
	  k[i][5]=(1.0/6.0)*(k[i][1]+2*k[i][2]+2*k[i][3]+k[i][4]);
	  vx=v0x+k[i][5];
	  
	  //Este es el runge kutta para encontrar la velocidad en X de la particula  
	  k[i][1]=h*funcionAce(t0,v0y,g,m,r3);
	  printf(" %lf ", k[i][1]);
	  k[i][2]=h*funcionAce(t0+0.5*h,v0y+0.5*k[i][1],g,m,r3);
	  k[i][3]=h*funcionAce(t0+0.5*h,v0y+0.5*k[i][2],g,m,r3);
	  k[i][4]=h*funcionAce(t0+h,v0y+k[i][3],g,m,r3);
	  k[i][5]=(1.0/6.0)*(k[i][1]+2*k[i][2]+2*k[i][3]+k[i][4]);
	  vy=v0y+k[i][5];
	  
	  //se organiza para la siguiente interacion
	  t=t0+h;
	  F[i+j][1]=x;
	  F[i+j][2]=y;
	  F[i+j][3]=vx;
	  F[i+j][4]=vy;
	  F[i+j][5]=t;
	  t0=t;
	  x0=x;
	  y0=t;
	  v0x=x;
	  v0y=t;
	}
    }
    // permite imprimir los resultados (este metodo a conitnuacion solo sirve para verficar los resultados del runge kutta.
    /* p=h;
    for(i=1;i< N;i++)
    {
        for(j=1;j<5;j++)
        {
	  printf("%f\t",k[i][j]);
        }
        a=x0+h;
        printf("Y(%f)=%f",a,Y[i]);
        printf("\n");
        h=h+p;
    }

    printf("\nThe final value of Xfinal:\t%f",y);
    */
    return 0;
   
}
