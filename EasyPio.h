#ifndef EASY_PIO_H
#define EASY_PIO_H


#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

//
#define INPUT 0
#define OUTPUT 1
#define ALT0 4            // LOS ALTS SON, ADEMAS DE ENTRADAS O SALIDAS DIGITALES PUEDEN SER UTILIZADOS POR OTRO DISPOSITIVO
#define ALT1 5			  // SON DE USO ESPECIAL
#define ALT2 6
#define ALT3 7
#define ALT4 3
#define ALT5 2



#define BCM2835_PERI_BASE 0x3F000000				// PARA REALIZAR EL MAPEO DE MEMORIA ES NECESARIO TENER NUESTRA DIRECCION BASE DE TODOS LOS PERIFERICOS DE LA RASPBERRY PI. EN NUESTRO CASO ES LA 3B+
#define GPIO_BASE (BCM2835_PERI_BASE + 0x200000)	//OBSERVAMOS LA DIRECCION BASE DE LA GPIO QUE ES LA DIRECCION BASE DE LOS PERIFERICOS MAS UN OFFSET DE 200000
#define BLOCK_SIZE (4*1024)                         // INDICA EL TAMAÑO DEL BLOQUE DE MEMORIA

volatile unsigned int *gpio; //Pointer to base of gpio

#define GPFSEL ((volatile unsigned int *) (gpio + 0))	//	DEFINICION DE LOS REGISTRO PARA ACCEDER A LA LECTURA, ESCRITURA, MODO DEL PIN)
#define GPSET ((volatile unsigned int *) (gpio + 7))	//TODAS LAS DIRECCIONES TIENEN COMO BASE LA DIRECCION DE LA GPIO
#define GPCLR ((volatile unsigned int *) (gpio + 10))
#define GPLEV ((volatile unsigned int *) (gpio + 13))
#define GPLEV0 (* (volatile unsigned int *) (gpio + 13))

/////////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES GENERALES DE LA GPIO
/////////////////////////////////////////////////////////////////////////////////////////


void pioInit(){         				 // PioInit realiza el mapeo virtual y fisico de la memoria
	int mem_fd;
	void *reg_map;
	mem_fd = open("/dev/mem", O_RDWR|O_SYNC); 	// abre el dispositivo /dev/mem
	reg_map = mmap(
	NULL, 										// dir. donde comienza el mapeo (null=no importa)
	BLOCK_SIZE, 								// 4KB bloque mapeado
	PROT_READ|PROT_WRITE, 						// permite lect.y escr.en la mem.
	MAP_SHARED, 								// acceso no exclusivo
	mem_fd, 									// puntero a /dev/mem
	GPIO_BASE); 								// offset a la GPIO
	gpio = (volatile unsigned *)reg_map;
	close(mem_fd);
}

/////////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES DE LA GPIO
/////////////////////////////////////////////////////////////////////////////////////////

void pinMode(int pin, int function) {						//Funcion destinada a configurar el modo del pin
	int reg = pin/10;										//recibe como parametro el numero del pin y la funcion (Entrada, salida o especial)
	int offset = (pin%10)*3;								//Calculo del offset
	GPFSEL[reg] &= ~((0b111 & ~function) << offset);		// Seteamos los 0
	GPFSEL[reg] |= ((0b111 & function) << offset);			//Seteamos los 1
}


void digitalWrite(int pin, int val) {						//Funcion destinada a realizar la escritura; toma como parametro el numero de pin y el valor asignar
	int reg = pin / 32;
	int offset = pin % 32;
	if (val) GPSET[reg] = 1 << offset;
	else GPCLR[reg] = 1 << offset;
}

int digitalRead(int pin) {									//Funcion destinada a realizar la lectura de una entrada digital, recibe como parametro el numero de pin
	int reg = pin / 32;
	int offset = pin % 32;
	return (GPLEV[reg] >> offset) & 0x00000001;
}

#endif
