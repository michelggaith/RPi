/*
 * ADCFuncional.c
 * 
 * Copyright 2022  <michel@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include "kbhit.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
const char PCF8591 = 0x48; // direccion base
int fd, adcVal, velocidad;	//declaracion de variables para acceder al adc
int ADCFuncional(void)
{
	if (wiringPiSetup () == -1) exit (1);	//
	fd = wiringPiI2CSetup(PCF8591);		// configuracion del bus I2C, inicializa el sistema I2C con el ID del dispositivo.
	init_keyboard();
	printf("Pulse cualquier tecla para salir\n");
	while (1)
	{
		wiringPiI2CReadReg8(fd, PCF8591 + 0) ; //primer lectura 
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 0) ;//segunda lectura valida
		printf("Pot value = %d \n", adcVal);
		delay(1000);
		velocidad = (adcVal*100/255);
		if(kbhit())
		{
			if(readch()=='q') return velocidad;
		}	  
     }
system("clear");
printf("La velocidad es del %d porciento \n", velocidad);	  
return velocidad;		  
}
