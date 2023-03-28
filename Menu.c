// Plantilla de un Menú de Opciones

#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <math.h>
#include "kbhit.h"
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h> 
#include <termios.h>
#include "GRUPOFUNCIONES.h"
#include <wiringSerial.h> 
#include <wiringPi.h>
#define FD_STDIN 0       
// Prototipos de las funciones
void menuPrincipal(int velocidad);
void ModoLocal(int velocidad);
char seleccion;
extern int velocidad;
char getCharR()
{
	char buff[2];
	int l = read(STDIN_FILENO, buff, 1);
	if(l>0)return buff[0];
	return(EOF);
}
int main()
{   
    int ret;
    ret = contrasena();
    if (ret==0)
    {   
        system("clear");
        init_keyboard();
        velocidad=1;
        menuPrincipal(velocidad);
        close_keyboard();   
        return 0;
    }
    else {printf("Acceso Denegado");}
}
// Definiciones de las funciones
void menuPrincipal(int velocidad)
{   
    init_keyboard();
    char modo;
    do{
        MENU:
        system("clear");
        printf("\n\n\t\t\tBIENVENIDO\n");
        printf("\n\n\t\t\tMENU PRINCIPAL\n");
        printf("\t\t\t--------------\n");
        printf("\n\t1. Modo Local\n");
        printf("\t2. Modo Remoto\n");
        printf("\t3. Setear velocidad inicial\n");
        printf("\tQ. SALIR\n");
        printf("\n\tIngrese una opcion: \n ");
        modo = getCharR();
        system("clear");
        if(modo==51)
        {
            velocidad=ADCFuncional();
            system("clear");
            goto MENU;
        }
        if(modo==49)
        {
            ModoLocal(velocidad);
            modo=0;
        }
        if(modo==50)
        {
            printf("MODO REMOTO\n");
            Apagar();
            system("echo '2' >/dev/ttyS0");
            RemotoRP(velocidad);            
        }
    }while(modo != 81 && modo!=113 ); 
    return;
}
void ModoLocal(int velocidad)
{
    int op;
    char repetir = TRUE;
    init_keyboard();
//ES NECESARIO UTILIZAR GETCHAR 
    do
    {       //MENUSECUENCIA:
        system("clear");
        op=0;
        printf("MODO LOCAL\n");
        Apagar();
        // Texto del menú
        int velocidad2 =100-velocidad;
        printf("\n\nMenu de Opciones\n");
        printf("1. El auto fantastico\n");
        printf("2. El choque\n");
        printf("3. La apilada\n");
        printf("4. La carrera\n");
        printf("5. Sirenas\n");
        printf("6. Dado\n");
        printf("7. Aleatorio\n");
        printf("8. Carga-Descarga\n");
        printf("0. SALIR\n");
        printf("La velocidad actual es %d porciento\n", velocidad2);     
       do{
            printf("\n\tIngrese una opcion: ");  //CONDICIONAL DE OPCION
            scanf("%d", &op);
            if(op <0 || op> 8) 
            {
                printf("Opcion invalida, por favor seleccione entre 0 y 8 \n");
            }       
		}while(op <0 || op> 8);
        switch (op)
        {  
            case 0: //Salida del programa 
                close_keyboard();
                return;
            case 1:
                printf("Fue seleccionado el auto fantastico\n");
                printf("Pulse  Q para salir\n");
                velocidad = AutoFantastico(velocidad);   
                Apagar();
                break;
            case 2:
                printf("Se esta ejecutando el choque\n");
                printf("Pulse Q para salir\n");
                velocidad = Choque(velocidad);
                Apagar();
                break;
            case 3:
                printf("Se esta ejecutando la apilada \n");
                printf("Pulse Q para salir\n");
                velocidad = Apilada(velocidad);
                Apagar();          
                break;
            case 4:
                printf("Se esta ejecutando la carrera\n");
                printf("Pulse Q para salir\n");
                velocidad = Carrera(velocidad);  
                Apagar();   
            case 5:
                printf("Se esta ejecutando Sirenas\n");
                printf("Pulse Q para salir\n");
                velocidad = Sirenas(velocidad);
                Apagar();
                break;
            case 6:
                printf("Se esta ejecutando Dado\n");
                printf("Pulse Q para salir\n");
                velocidad = dado(velocidad);   
                Apagar();     
                break;
            case 7:
                printf("Se esta ejecutando una secuencia aleatoria\n");
                printf("Pulse Q para salir\n");
                velocidad = Aleatorio(velocidad);
                Apagar();
                break;
			case 8:
                printf("Se esta ejecutando Carga-Descarga\n");
                printf("Pulse Q para salir\n");
                velocidad = CargaDescarga(velocidad);   
                Apagar();
				break;
        }
    }while (repetir);
}



