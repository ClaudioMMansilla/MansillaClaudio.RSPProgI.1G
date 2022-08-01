
#ifndef VEHICULO_H_
#define VEHICULO_H_

typedef struct{
	int id;
	char marca[20];
	int tipo;
	float peso;
}eVehiculo;

#endif /* VEHICULO_H_ */

eVehiculo* Vehiculo_new();
eVehiculo* Vehiculo_newParam(int id, char* marca, int tipo, float peso);


int Vehiculo_setPeso(eVehiculo* pElement, float peso);
int Vehiculo_getId(eVehiculo* pElement, int* id) ;
int Vehiculo_getTipo(eVehiculo* pElement, int* tipo) ;
int Vehiculo_getPeso(eVehiculo* pElement, float* peso);
int Vehiculo_getMarca(eVehiculo* pElement, char* marca);
