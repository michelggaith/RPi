/*Este programa genera la secuencia de luces de La Carrera mediante el uso de tablas */
/*La carrera: Una luz arranca por la izquierda a una determinada velocidad, 
 * y cuando va por la mitad del recorrido arranca una nueva luz por la izquierda pero al doble de velocidad 
 * lo que produce que arriben al extremo derecho al mismo tiempo.
La técnica de tabla de datos consiste en simplemente un bucle de programa que saca por los puertos de salida el 
* contenido de una tabla preestablecida con valores que reproducen la secuencia deseada.*/
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


int CarreraRemoto(int velocidad){
	int i=0;
	int j=0;
	int tabla[8][8] = {												//TABLA CON SECUENCIA DE LUCES A SEGUIR
				{1,0,0,0,0,0,0,0},
				{0,1,0,0,0,0,0,0},
				{0,0,1,0,0,0,0,0},
				{1,0,0,1,0,0,0,0},
				{0,1,0,0,1,0,0,0},
				{0,0,0,1,0,1,0,0},
				{0,0,0,0,0,1,1,0},
				{0,0,0,0,0,0,0,1}	
	};
	int tabla2[8][8] = {												//TABLA CON SECUENCIA DE LUCES A SEGUIR (VUELTA)
				{0,0,0,0,0,0,0,1},
				{0,0,0,0,0,0,1,0},
				{0,0,0,0,0,1,0,0},
				{0,0,0,0,1,0,0,1},
				{0,0,0,1,0,0,1,0},
				{0,0,1,0,1,0,0,0},
				{0,1,1,0,0,0,0,0},
				{1,0,0,0,0,0,0,0}	
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
		for(i=0;i<8;i++)
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
			}usleep(30000*velocidad2);
		}
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				digitalWrite(LEDS[j],tabla2[i][j]);			
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
							
			}usleep(30000*velocidad2);
		}
	}
}
