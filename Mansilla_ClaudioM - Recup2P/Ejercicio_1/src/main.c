#include <stdio.h>
#include <stdlib.h>
#include "Vehiculo.h"

// https://github.com/ClaudioMMansilla/MansillaClaudio.RSPProgI.1G.git
// Mansilla Claudio Matias - 1G

int main(void) {

	setbuf(stdout, NULL);

	int id;
	char marca[20];
	int tipo;
	float peso;

	eVehiculo* vehiculoAux = NULL;

	vehiculoAux->id = 100;
	strcpy(vehiculoAux->marca, "Toyota");
	vehiculoAux->peso = 500.0;
	vehiculoAux->tipo = 2;

	FILE* pFile = fopen("Ejercicio2.csv","w");
    if(pFile != NULL)
    {
    	if( (Vehiculo_getId(vehiculoAux, &id)) &&
    		(Vehiculo_getMarca(vehiculoAux, marca))&&
			(Vehiculo_getTipo(vehiculoAux, &tipo)) &&
			(Vehiculo_getPeso(vehiculoAux, &peso))
		   )
    	{
            fprintf(pFile,"%d,%s,%d,%f\n",
            		vehiculoAux->id,
					vehiculoAux->marca,
					vehiculoAux->tipo,
					vehiculoAux->peso
			);
    	}
    }



	return EXIT_SUCCESS;
}
