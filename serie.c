/*
	UART communication on Raspberry Pi using C (WiringPi Library)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EasyPio.h"
#define MAX_STR_LEN 80

void getStrSerial(char *str){
	int i = 0;
	do{
		str[i] = getStrSerial();
	}while((str[i++] != '\r') && (i < MAX_STR_LEN));
	str[i-1] = 0;
}
void putStrSerial(char *str){
	int i = 0;
	while(str[i] != 0)
	{
		putStrSerial(str[i++]);
	}
}
int main(void){
	char str[MAX_STR_LEN];
	pioInit();
	printf("Inicilizando UART...\n"); 
	uartInit(115200);
	printf("Done\n"); 
	printf("recibiendo dato...\n"); 
	getStrSerial(str);
	printf("Enviando dato... %s\n", str); 
	putStrSerial("Escribir algo:\r\n");
}
