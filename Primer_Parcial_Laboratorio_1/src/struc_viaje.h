/*
 * struc_viaje.h
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#ifndef STRUC_VIAJE_H_
#define STRUC_VIAJE_H_

#include "struc_tipo.h"

typedef struct {
	int idViaje;
	char destino[20];
	int cantidadPasajeros;
	int tipoId;
	int isEmpty;
} viaje;

void inicializarViaje(viaje arrayViajes[], int longArrayViajes);
int altaViaje(viaje arrayViajes[], int longArrayViajes, tipo tipoX[]);
int buscarViajeVacio(viaje arrayViajes[], int longArrayViajes);
int buscarViajePorId(viaje arrayViajes[], int longArrayViajes, int id);
void menuModificarViaje(viaje arrayViajes[], int longArrayViajes);
void menuDarDeBajaViaje(viaje arrayViajes[], int longArrayViajes);
void listarViajes(viaje arrayViajes[], int longArrayViajes);
int asignarIdViaje(viaje arrayViajes[], int longArrayViajes);
void modificarViaje(int indice, viaje arrayViajes[]);
void ordenarPorId(viaje arrayViajes[], int longArrayViajes);
void listarViajesPorTipo(viaje arrayViajes[], int longArrayViajes,
		tipo arrayTipos[], int longArrayTipos);

#endif /* STRUC_VIAJE_H_ */
