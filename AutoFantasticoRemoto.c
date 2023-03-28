/*Este programa genera la secuencia del auto fantastico a traves de los puertos GPIO de la Raspberry*/

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

 /*Pulsadores: GPIO17 y GPIO27
 *Dipswitch: GPIO 5,6,13 y 19
 *LEDS = 23,24,25,12,16,20,21,26*/

int AutoFantasticoRemoto(int velocidad){
	int i=0;
	int leds[8] = {23,24,25,26,12,16,20,21};
	char tecla;
	int velocidad2=velocidad;
	int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	serialFlush(fd);
	pioInit();
	for(i=0;i<8;i++)
	{
		pinMode(leds[i],OUTPUT);
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
				printf("LLEGO EL DATO PERO NO HACE NADA");
				if(velocidad2>1){velocidad2=velocidad2-5;}
				else{velocidad2=1;} //si se presiona la flecha de abajo la velocidad disminuye				
			}
		}
	}
	do
	{
		serialFlush(fd);
		for(i=0;i<8;i++)
		{
			digitalWrite(leds[i],1);
			usleep(30000*velocidad2);
			digitalWrite(leds[i],0);
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
					printf("LLEGO EL DATO PERO NO HACE NADA");
					if(velocidad2>1){velocidad2=velocidad2-5;}
					else{velocidad2=1;} //si se presiona la flecha de abajo la velocidad disminuye				
				}
			
			}
			
		}
		for(i=8;i>0;i--)
		{
			digitalWrite(leds[i],1);
			usleep(30000*velocidad2);
			digitalWrite(leds[i],0);
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
					printf("LLEGO EL DATO PERO NO HACE NADA");
					if(velocidad2>1){velocidad2=velocidad2-5;}
					else{velocidad2=1;} //si se presiona la flecha de abajo la velocidad disminuye				
				}
			}
		}	
	}while(1);
	return velocidad2;
}
