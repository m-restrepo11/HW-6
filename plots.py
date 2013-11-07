#!/usr/bin/python
#encoding: UTF-8

import numpy as np
import matplotlib.pyplot as plt
import glob
import os


"""
Carga el archivo con posiciones en un arreglo de numpy.
Input: archivo con posiciones iniciales.
Output: numpy array con todos los datos.
"""
def cargar_datos(archivo):
 
    #Carga los datos del archivo de entrada en dos arrays, uno con posición en X
    #y otro con posición en Y.
    pos_x= np.loadtxt(archivo, unpack=True, usecols=[1])
    pos_y = np.loadtxt(archivo, unpack=True, usecols=[2])
   
    return pos_x, pos_y

"""
Grafica los datos del arreglo cargado en el metodo cargar_datos.
Input: Vector de posiciones en X, Vector de posiciones Y.
Output: Gráficas.
"""

def graficar(x, y, nombre):
    

   	
    plt.plot(x[0:],y[0:], 'k*', color='b')  
    plt.xlabel('$Pos_X$', size=24)
    plt.ylabel('$Pos_Y$',size=24)
    plt.title(nombre, size=24)
    plt.axes().set_aspect('equal', 'datalim')
    plt.savefig(nombre+'.png')
    plt.clf()
    
#Defines the input file
directory = os.getcwd()
for filename in glob.glob(directory + "/*.dat"):
	x,y= cargar_datos(filename)
	cargar_datos(filename)
	nombre = os.path.splitext(os.path.basename(filename))[0]	
	graficar(x, y,nombre)

    


