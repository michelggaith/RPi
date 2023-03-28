
#include "kbhit.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

const char PCF8591 = 0x48; // direccion base
int fd, adcVal, velocidad,i;	//declaracion de variables para acceder al adc
int VelocidadInicial(void)  {
	if (wiringPiSetup () == -1) exit (1);	//
	fd = wiringPiI2CSetup(PCF8591);		// configuracion del bus I2C, inicializa el sistema I2C con el ID del dispositivo.
	for(i=0; i<5; i++)
	{
		wiringPiI2CReadReg8(fd, PCF8591 + 0) ; //primer lectura 
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 0) ;//segunda lectura valida
		velocidad = (adcVal*100/255);		  
		delay(1000);
	}
	system("clear");
	printf("Pot value = %d \n", adcVal);
	printf("La velocidad inicial es del %d porciento \n", velocidad);	  
	return velocidad;		  
}


