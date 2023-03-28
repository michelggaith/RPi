/*
	UART communication on Raspberry Pi using C (WiringPi Library)
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int serial_port ;
  char dat;
  if ((serial_port = serialOpen ("/dev/ttyS0", 115200)) < 0)			/* abrir el puerto serie */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }
  if (wiringPiSetup() == -1)							/* inicializa la configuracion de wiringPi */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
  printf (" -------Comunicacion serie----\n") ;
  while(1)
  { 
    if(serialDataAvail (serial_port)) 		/* retorna el numero de caracteres disponibles para leer o -1*/
    {
      dat = serialGetchar (serial_port);		/* retorna el siguiente caracter disponible en el dispositivo serial */	
	    printf ("%c", dat) ;
	    serialPutchar(serial_port, dat);		/* envia un unico byte por el puerto serie indicado*/
    }
  }
}
