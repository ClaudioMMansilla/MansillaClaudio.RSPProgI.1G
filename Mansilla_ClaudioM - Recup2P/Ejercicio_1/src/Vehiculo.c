#include <stdio.h>
#include <stdlib.h>
#include "Vehiculo.h"


eVehiculo* Vehiculo_new(){

	eVehiculo* aux = (eVehiculo*) malloc(sizeof(eVehiculo));
	if(aux != NULL )
	{
		//si el return es false libero memoria asignada y retorna null
		if( !(Vehiculo_setId(aux, 0)&&
				Vehiculo_setMarca(aux, "") &&
				Vehiculo_setTipo(aux, 0) &&
				Vehiculo_setPeso(aux, 0)
				))
		{
			free(aux);
			aux = NULL;
		}
	}
	return aux;
}


eVehiculo* Vehiculo_newParam(int id, char* marca, int tipo, float peso){

	eVehiculo* aux = Vehiculo_new();
	if(aux != NULL )
	{
		//si el return es false libero memoria asignada y retorna null
		if( !(Vehiculo_setId(aux, id)&&
				Vehiculo_setMarca(aux, marca) &&
				Vehiculo_setTipo(aux, tipo) &&
				Vehiculo_setPeso(aux, peso)
				))
		{
			free(aux);
			aux = NULL;
		}
	}
	return aux;
}





int Vehiculo_setId(eVehiculo* pElement, int id) {

	int retorno = 0;
	if(pElement != NULL && id >= 0)
	{
		pElement->id = id;
		retorno = 1;
	}
	return retorno;
}

int Vehiculo_getId(eVehiculo* pElement, int* id) {

	int retorno = 0;
	if(pElement != NULL && id != NULL)
	{
		 *id = pElement->id;
		retorno = 1;
	}
	return retorno;
}

int Vehiculo_setTipo(eVehiculo* pElement, int tipo) {

	int retorno = 0;
	if(pElement != NULL && tipo >= 0)
	{
		pElement->tipo = tipo;
		retorno = 1;
	}
	return retorno;
}

int Vehiculo_getTipo(eVehiculo* pElement, int* tipo) {

	int retorno = 0;
	if(pElement != NULL && tipo != NULL)
	{
		*tipo = pElement->tipo;
		retorno = 1;
	}
	return retorno;
}


int Vehiculo_setPeso(eVehiculo* pElement, float peso) {

	int retorno = 0;
	if(pElement != NULL && peso >= 0)
	{
		pElement->peso = peso;
		retorno = 1;
	}
	return retorno;
}

int Vehiculo_getPeso(eVehiculo* pElement, float* peso) {

	int retorno = 0;
	if(pElement != NULL && peso != NULL)
	{
		*peso = pElement->peso;
		retorno = 1;
	}
	return retorno;
}

int Vehiculo_setMarca(eVehiculo* pElement, char* marca){

	int retorno = 0;

	if(pElement != NULL && marca != NULL )
	{
		strcpy(pElement->marca, marca);
		retorno = 1;
	}
	return retorno;
}

int Vehiculo_getMarca(eVehiculo* pElement, char* marca){

	int retorno = 0;

	if(pElement != NULL && marca != NULL )
	{
		strcpy(marca,pElement->marca);
		retorno = 1;
	}
	return retorno;
}
