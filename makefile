all:a.out

a.out:evolve.o Derivada.o conversion.o condiciones_iniciales.dat
	
	cc Derivada.o conversion.o evolve.o -lm
	./a.out condiciones_iniciales.dat

conversion.o:conversion.c  
	cc -c conversion.c -lm 

Derivada.o: Derivada.c  
	cc -c Derivada.c -lm 

condiciones_iniciales.dat:ic.c
	cc ic.c conversion.c -lm -o ic.exe 
	./ic.exe 0 0 0 0 1
	mv condiciones_iniciales.dat 1_galaxia.dat
	./ic.exe 150 200 0 -150 2 
	mv condiciones_iniciales.dat 2_galaxia.dat


evolve.o:evolve.c 
	cc -c evolve.c  -lm 

clean: 
	rm -f *.o


