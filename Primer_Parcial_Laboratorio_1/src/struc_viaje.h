/*
 * struc_viaje.h
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#ifndef STRUC_VIAJE_H_
#define STRUC_VIAJE_H_

#include "struc_tipo.h"

typedef struct{
	int idViaje;
	char destino[20];
	int cantidadPasajeros;
	int tipoId;
	int isEmpty;
}viaje;

void inicializarViaje(viaje viajeX[], int len);
int altaViaje(viaje viajeX[], int lenViajeX, tipo tipoX[], int lenTipoX);
int buscarVacio(viaje viajeX[], int len);
void menuModificarViaje(viaje viajeX[], int len);
void menuDarDeBajaViaje(viaje viajeX[], int len);
void mostrarViajes(viaje viajeX[], int len);
int asignarId(viaje viajeX[], int len);

#endif /* STRUC_VIAJE_H_ */
