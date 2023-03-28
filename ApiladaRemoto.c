/*Este programa genera la secuencia de luces de La Apilada mediante el uso de tablas
La apilada: Una luz arranca de izquierda a derecha y cuando alcanza el extremo derecho, 
parpadea y se queda encendida en la �ltima posici�n; a partir de all� una nueva luz 
comienza su recorrido desde la izquierda y se desplaza hacia la derecha hasta llegar a 
la posici�n anterior a la que est� fija, parpadea y tambi�n se queda quieta como la anterior. 
Ahora son dos las luces quietas y se repite el mismo proceso para una nueva luz arrancando 
por la izquierda y llegando a la posici�n anterior a las dos quietas. La secuencia termina 
cuando los ocho lugares han sido ocupados de la forma descripta.
La t�cnica de tabla de datos consiste en simplemente un bucle de programa que saca por los 
puertos de salida el   contenido de una tabla preestablecida con valores que reproducen la secuencia deseada.*/
//#include "kbhit.h"
#include <stdlib.h>
#include <stdio.h>
#include "EasyPio.h"
#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <wiringPi.h>
#include <wiringSerial.h>


int ApiladaRemoto(int velocidad){
	int i=0;
	int j=0;
	int tabla[52][8] = {												//TABLA CON SECUENCIA DE LUCES A SEGUIR
		{1,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1},	/*Primero*/
		{1,0,0,0,0,0,0,1},
		{0,1,0,0,0,0,0,1},
		{0,0,1,0,0,0,0,1},
		{0,0,0,1,0,0,0,1},
		{0,0,0,0,1,0,0,1},
		{0,0,0,0,0,1,0,1},
		{0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,1,1},	/*Segundo*/
		{1,0,0,0,0,0,1,1},
		{0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,1,1},
		{0,0,0,1,0,0,1,1},
		{0,0,0,0,1,0,1,1},
		{0,0,0,0,0,1,1,1},
		{0,0,0,0,0,0,1,1},
		{0,0,0,0,0,1,1,1},	/*Tercero*/
		{1,0,0,0,0,1,1,1},
		{0,1,0,0,0,1,1,1},
		{0,0,1,0,0,1,1,1},
		{0,0,0,1,0,1,1,1},
		{0,0,0,0,1,1,1,1},
		{0,0,0,0,0,1,1,1},
		{0,0,0,0,1,1,1,1},	/*Cuarto*/
		{1,0,0,0,1,1,1,1},
		{0,1,0,0,1,1,1,1},
		{0,0,1,0,1,1,1,1},
		{0,0,0,1,1,1,1,1},
		{0,0,0,0,1,1,1,1},
		{0,0,0,1,1,1,1,1},	/*Quinto*/
		{1,0,0,1,1,1,1,1},
		{0,1,0,1,1,1,1,1},
		{0,0,1,1,1,1,1,1},
		{0,0,0,1,1,1,1,1},
		{0,0,1,1,1,1,1,1},	/*Sexto*/
		{1,0,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,1},
		{0,0,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,1},	/*Septimo*/
		{1,1,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1}	/*Octavo*/
			
	};
	int LEDS[8] = {23,24,25,26,12,16,20,21};            //SALIDAS A UTILIZAR DE LA GPIO
	int velocidad2=velocidad;
	pioInit();
	char tecla;
	int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	serialFlush(fd);
	for(i=0;i<8;i++)
	{
		pinMode(LEDS[i],OUTPUT);						// MODO DEL PIN SALIDA
		if(serialDataAvail(fd))
		{
			tecla=serialGetchar(fd);
				
//EN ESTE CASO; AL PRESIONAR LA TECLA q EL PROGRAMA RETORNA AL MENU DE 
//SECUENCIAS			
			if(tecla==113 || tecla==81)
			{
					tecla=0;
					serialFlush(fd);
					serialClose(fd);
					return velocidad2;
			}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Abajo" EL PROGRAMA disminuye LA VELOCIDAD DE LAS 
//SECUENCIAS				
			if(tecla==49)
			{
				tecla=0;
				serialFlush(fd);
				if(velocidad2<100){velocidad2=velocidad2 + 5;} 
				else{velocidad2=100;} //Si se presiona la flecha de arriba aumenta la velocidad			
			}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Arriba" EL PROGRAMA AUMENTA LA VELOCIDAD DE LAS
//SECUENCIAS					
			if(tecla==50)
			{
				tecla=0;
				serialFlush(fd);
				if(velocidad2>1){velocidad2=velocidad2-5;}
				else{velocidad2=1;} //si se presiona la flecha de abajo la velocidad disminuye				
			}
		}	
	}
	while(1)
	{
		for(i=0;i<52;i++)
		{
			for(j=0;j<8;j++)
			{
				digitalWrite(LEDS[j],tabla[i][j]);
				if(serialDataAvail(fd))
				{
					tecla=serialGetchar(fd);
				
//EN ESTE CASO; AL PRESIONAR LA TECLA q EL PROGRAMA RETORNA AL MENU DE 
//SECUENCIAS			
					if(tecla==113 || tecla==81)
					{
						tecla=0;
						serialFlush(fd);
						serialClose(fd);
						return velocidad2;
					}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Abajo" EL PROGRAMA disminuye LA VELOCIDAD DE LAS 
//SECUENCIAS				
					if(tecla==49)
					{
						tecla=0;
						serialFlush(fd);
						if(velocidad2<100){velocidad2=velocidad2 + 5;} 
						else{velocidad2=100;} //Si se presiona la flecha de arriba aumenta la velocidad	
					}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Arriba" EL PROGRAMA AUMENTA LA VELOCIDAD DE LAS
//SECUENCIAS					
					if(tecla==50)
					{
						tecla=0;
						serialFlush(fd);
						if(velocidad2>1){velocidad2=velocidad2-5;}
						else{velocidad2=1;} //si se presiona la flecha de abajo la velocidad disminuye				
					}			
				}	 			
			}
			usleep(30000*velocidad2);
		}
	}
}
	
