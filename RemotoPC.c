// LA IDEA DEL PROGRAMA ES RECIBIR ORDENES DESDE UN SEGUNDO PUERTO//

#include "kbhit.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
//#include <wiringSerial.h>
//#include <wiringPi.h>

#define FD_STDIN 0

void control(void);
int Remoto(void);

char getChar1(){
	char buff[2];
	int l = read(STDIN_FILENO, buff, 1);
	if(l>0)return buff[0];
		return(EOF);
}
int main(int argc, char **argv)
{
	char data[10]={0};
	char rasp;
// MENU PRINICIPAL MODO REMOTO FUNCIONA CORRECTAMENTE
	while(1)
	{
		rasp='0';
		printf("Este programa es el complemento del modo remoto del proyecto final de Tecnicas digitales 2, es necesario seleccionar el modo remoto en el programa de la raspberry para continuar, el programa se queda a la espera de la señal de la habilitación del modo remoto\n");
	//CONFIGURACION TERMINAL//
		struct termios t_old, t_new;
		tcgetattr( FD_STDIN, &t_old);
		t_new = t_old;
		t_new.c_lflag &= ~(ECHO | ICANON);
		t_new.c_cc[VMIN] = 0;
		t_new.c_cc[VTIME] = 0;
		tcsetattr(FD_STDIN,TCSANOW, &t_new);
		system("setterm -cursor off");
	//Apertura Puerto serie
		int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
		int repetir;
		do{ // SE MANTIENE EL BUCLE MIENTRAS NO SE PRESIONE Q, esto permite que el programa NO avance mientras no se presione Q
			read(fd, data, 10);
			rasp=data[0];
			if(rasp==50)
			{
				do {
					system("clear");
					printf("Usted accedio al MODO REMOTO\n");            
            		// Texto del menú
            		printf("\n\nMenu de Opciones\n");
           			printf("1. El auto fantastico\n");
            		printf("2. El choque\n");
            		printf("3. La apilada\n");
            		printf("4. La carrera\n");
					printf("5. Sirenas\n");
					printf("6. Dado\n");
					printf("7. Aleatorio\n");
					printf("8. Carga-Descarga\n");
					printf("Q. SALIR\n");
					printf("\t Ingrese la secuencia en cuestion\n");
					repetir=Remoto();
				}while(repetir!=2);
			}
			if(repetir==2)
			{
				close(fd);
				exit(1);
			}
		}while(rasp != 50);	
	} // En este momento se reinicia el programa
	return 0;
}
int Remoto(void){
	char input;
/*
//CONFIGURACION TERMINAL//
struct termios t_old, t_new;
tcgetattr( FD_STDIN, &t_old);
t_new = t_old;

t_new.c_lflag &= ~(ECHO | ICANON);
t_new.c_cc[VMIN] = 0;
t_new.c_cc[VTIME] = 0;

tcsetattr(FD_STDIN,TCSANOW, &t_new);

system("setterm -cursor off");
*/
	init_keyboard();
//Apertura Puerto serie
	do{
		input=getChar1();
	//system("echo 'q' >/dev/ttyUSB0");
		if(input==49)
		{
			printf("Se esta ejecutando el auto fantastico\n");
			system("echo '1' >/dev/ttyUSB0");
			control();
			return 1;
		}
		else if (input==50)
		{
			system("echo '2' >/dev/ttyUSB0");
			control();
			return 1;
		}
		else if (input==51)
		{
			system("echo '3' >/dev/ttyUSB0");
			control();
			return 1;	
		}
		else if (input==52)
		{
			system("echo '4' >/dev/ttyUSB0");
			control();
			return 1;	
		}
		else if (input==53)
		{
			system("echo '5' >/dev/ttyUSB0");
			control();
			return 1;
		}				
		else if (input==54)
		{
			system("echo '6' >/dev/ttyUSB0");
			control();
			return 1;	
		}				
		else if(input==55)
		{
			system("echo '7' >/dev/ttyUSB0");
			control();
			return 1;
		}				
		else if(input==56)
		{
			system("echo '8' >/dev/ttyUSB0");
			control();
			return 1;
		}
        else if(input == 113 || input ==81)
		{
			system("echo 'q' >/dev/ttyUSB0");
			close_keyboard();	
			return 2;
		}
	}while(input != 113 || input!=81);
	return 2;						
}
void control(void){
	char tecla;
	do{
		tecla = getChar1();
//EN ESTE CASO; AL PRESIONAR LA TECLA q EL PROGRAMA RETORNA AL MENU DE 
//SECUENCIAS			
		if(tecla==113||tecla==81)
		{
			system("echo 'q' >/dev/ttyUSB0");
			tecla=0;
			return;
		}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Abajo" EL PROGRAMA disminuye LA VELOCIDAD DE LAS 
//SECUENCIAS				
		if(tecla=='B')
		{
			printf("Bandera 2\n");
			system("echo '1' >/dev/ttyUSB0"); //Si se presiona la flecha de arriba aumenta la velocidad			
			tecla=0;
		}
//EN ESTE CASO; AL PRESIONAR LA TECLA "Arriba" EL PROGRAMA AUMENTA LA VELOCIDAD DE LAS
//SECUENCIAS					
		if(tecla=='A')
		{
			system("echo '2' >/dev/ttyUSB0");
			printf("Bandera 1\n");
			tecla=0;
		} //si se presiona la flecha de abajo la velocidad disminuye				
	}while(tecla!=113 && tecla!=81);
}
