
#include <string.h>
#include <stdio.h>

int contrasena(void) {
const char CONTRASENA[] ="mic";
const int numIntentos =3;
int i, retorno;
char contrasena[100];
printf("\t\tPara acceder al programa teclee la contraseña\n\n");
for (i=0; i<numIntentos; i++) 
{
	printf("\n\tContrasena: ");
	scanf("%s", contrasena);
	if (strcmp(CONTRASENA, contrasena) != 0) 
	{
		printf("\tcontrasena invalida\n");
		continue;
	} break;
}
if (i == numIntentos) 
	{
		retorno=1;
		return retorno;
	}
retorno =0;
return retorno;
}

