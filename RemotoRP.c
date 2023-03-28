// LA IDEA DEL PROGRAMA ES RECIBIR ORDENES DESDE UN SEGUNDO PUERTO//

//#include "GRUPOFUNCIONES.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <wiringSerial.h>
#include <wiringPi.h>


#define FD_STDIN 0

extern int velocidad;
int AutoFantasticoRemoto(int velocidad);
int CarreraRemoto(int velocidad);
int ApiladaRemoto(int velocidad);
int SirenasRemoto(int velocidad);
int AleatorioRemoto(int velocidad);
int dadoRemoto(int velocidad);
int ChoqueRemoto(int velocidad);
int CargaDescargaRemoto(int velocidad);
void Apagar(void);

char getChar1(){
	char buff[2];
	int l = read(STDIN_FILENO, buff, 1);
	if(l>0)return buff[0];
	return(EOF);
}
void RemotoRP(int velocidad){
	char input =0;
//CONFIGURACION TERMINAL//
	struct termios t_old, t_new;
	tcgetattr( FD_STDIN, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ECHO | ICANON);
	t_new.c_cc[VMIN] = 0;
	t_new.c_cc[VTIME] = 0;
	tcsetattr( FD_STDIN,TCSANOW, &t_new);
	system("setterm -cursor off");
//Apertura Puerto serie
	int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	serialFlush(fd);
	INICIO:
		//MENUSECUENCIAS:
		system("clear");
		printf("Usted ingreso al modo remoto, por favor dirigase al dispositivo en cuestion\n");
		printf("\n\nMenu de Opciones\n");
        printf("1. El auto fantastico\n");
        printf("2. El choque\n");
        printf("3. La apilada\n");
        printf("4. La carrera\n");
        printf("5. Sirenas\n");
        printf("6. Dado\n");
        printf("7. Aleatorio\n");
        printf("8. Carga-Descarga\n");
		printf("Presione Q para salir\n");
//system("echo '2' >/dev/ttyS0");
	do{ // MANTENGO MIENTRAS Q SEA DISTINTO DE Q
		if(serialDataAvail(fd))
		{
			input=serialGetchar(fd);
			if(input==49)
			{
				printf("Se esta ejecutando el auto fantastico\n");
				velocidad=AutoFantasticoRemoto(velocidad);
				Apagar();
				goto INICIO;
				break;			
			}    
			else if (input==50)
			{
				printf("Se esta ejecutando el choque\n");
				velocidad=ChoqueRemoto(velocidad);
				Apagar();
				goto INICIO;
				break;
			}    
			else if (input==51)
			{
				printf("Se esta ejecutando la apilada\n");
				velocidad=ApiladaRemoto(velocidad);
				Apagar();
				goto INICIO;
				break;
			}			
			else if (input==52)
			{
				printf("Se esta ejecutando la carrera\n");
				velocidad=CarreraRemoto(velocidad);
				Apagar();
				goto INICIO;
				break;
			}			
            else if (input==53)
			{
				printf("Se esta ejecutando Sirenas\n");
				velocidad=SirenasRemoto(velocidad);
				Apagar();
				goto INICIO;
				break;
			}			
			else if (input==54)
			{
				printf("Se esta ejecutando el Dado\n");
				velocidad=dadoRemoto(velocidad);
				Apagar();
				goto INICIO;
				break;
			}
			else if(input==55)
			{
				printf("Se esta ejecutando el Aleatorio\n");
				velocidad=AleatorioRemoto(velocidad);
				Apagar();
				goto INICIO;
				break;
			}
        	else if(input==56) 
			{
				printf("Se esta ejecutando el Carga-Descarga\n");
				velocidad=CargaDescargaRemoto(velocidad);
				Apagar();
				goto INICIO;
				break;
			}	
			else if(input==81 || input==113)
			{
				goto SALIDA;
			}
		}		
	}while(input !=81 && input != 113);
	SALIDA:
	close(fd);
//NORMALIZAR TERMINAL//
	system("setterm -cursor on");
	system("clear");
 	tcsetattr( FD_STDIN,TCSANOW, &t_old);
	return;
}

