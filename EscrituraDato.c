#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define BAUDRATE 9600

struct termios ttyold, ttynew;
int termset(int fd, int baudrate, 
struct termios * ttyold, struct termios * ttynew);

int EscrituraDato(char dato)
{ 
  int fd;                                 /* File descriptor for the port */
  char c=dato;
  // Open device.
  fd = open("/dev/ttyAMA0", O_WRONLY | O_NOCTTY | O_SYNC);
  if(fd < -1)
  {
    printf("ERROR: opening serial port\n");
    return -1;
  }
  if(termset(fd, BAUDRATE, &ttyold, &ttynew) == -1)
  {
    printf("ERROR: setting tty\n");
    return -1;
  }
 write(fd, &c,1); //Mando un unico caracter
 close(fd);
 return 0;
}
