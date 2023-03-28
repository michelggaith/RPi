/*Este programa genera la secuencia de Aleatorio con inicio a traves de los puertos GPIO de la Raspberry*/
#include "kbhit.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "EasyPio.h"

/*Pulsadores: GPIO17 y GPIO27
*Dipswitch: GPIO 5,6,13 y 19
*LEDS = 23,24,25,12,16,20,21,26*/

int Aleatorio(int velocidad)
{
	int i=0;
	int leds[8] = {23,24,25,26,12,16,20,21};
	srand(time(NULL));
	int N = rand() % 9; /*Devuelve un n�mero random entre 0 y 6*/
	int velocidad2=velocidad;
	pioInit();
	char tecla;
	init_keyboard();
	for(i=0;i<8;i++)
	{
		pinMode(leds[i],OUTPUT);	
		if(kbhit())
		{ 
			tecla=readch();
//EN ESTE CASO; AL PRESIONAR LA TECLA q EL PROGRAMA RETORNA AL MENU DE 
//SECUENCIAS
			if(tecla=='q')
			{
				tecla=0;
				return velocidad2;
			}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Abajo" EL PROGRAMA disminuye LA VELOCIDAD DE LAS 
//SECUENCIAS					
			if(tecla=='B')
			{
				tecla=0;
				if(velocidad2<100){velocidad2=velocidad2 + 5;} 
				else{velocidad2=100;} 	
			}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Arriba" EL PROGRAMA AUMENTA LA VELOCIDAD DE LAS
//SECUENCIAS				
			if(tecla=='A')
			{
				tecla=0;
				if(velocidad2>1){velocidad2=velocidad2-5;}
				else{velocidad2=1;} 			
			}
		}
	}
	while(1)
	{
		for(i=0;i<8;i++)
		{
			digitalWrite(leds[N],1);
			usleep(30000*velocidad2);
			digitalWrite(leds[N],0);
			if(kbhit())
			{ 
				tecla=readch();

//EN ESTE CASO; AL PRESIONAR LA TECLA q EL PROGRAMA RETORNA AL MENU DE 
//SECUENCIAS
				if(tecla=='q')
				{
					tecla=0;
					return velocidad2;
				}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Abajo" EL PROGRAMA disminuye LA VELOCIDAD DE LAS 
//SECUENCIAS					
				if(tecla=='B')
				{
					tecla=0;
					if(velocidad2<100){velocidad2=velocidad2 + 5;} 
					else{velocidad2=100;} 	
				}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Arriba" EL PROGRAMA AUMENTA LA VELOCIDAD DE LAS
//SECUENCIAS				
				if(tecla=='A')
				{
					tecla=0;
					if(velocidad2>1){velocidad2=velocidad2-5;}
					else{velocidad2=1;} 			
				}
			 }
		}
	}
}
