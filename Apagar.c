#include <stdlib.h>
#include <stdio.h>
#include "EasyPio.h"

 /*Pulsadores: GPIO17 y GPIO27
 *Dipswitch: GPIO 5,6,13 y 19
 *LEDS = 23,24,25,12,16,20,21,26*/

void Apagar(void)
{
	int i=0;
	int leds[8] = {23,24,25,26,12,16,20,21};
	pioInit();
	for(i=0;i<8;i++)
	{
		pinMode(leds[i],OUTPUT);
	}
	digitalWrite(leds[0],0);
	digitalWrite(leds[1],0);
	digitalWrite(leds[2],0);
	digitalWrite(leds[3],0);
	digitalWrite(leds[4],0);
	digitalWrite(leds[5],0);
	digitalWrite(leds[6],0);
	digitalWrite(leds[7],0);
}

