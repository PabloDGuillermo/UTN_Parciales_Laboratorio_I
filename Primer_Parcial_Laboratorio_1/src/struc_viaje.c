/*
 * struc_viaje.c
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#include <stdio.h>
#include "struc_viaje.h"
#include "inputs.h"
#include <string.h>
#include "struc_tipo.h"

#define VACIO 0
#define LLENO 1

/// @fn void inicializarViaje(viaje[], int)
/// @brief Inicializa el campo isEmpty en 0 para todos los elementos del array
///
/// @param viajeX recibe el array de la estructura viaje
/// @param len longitud del array de la estructura viaje
void inicializarViaje(viaje viajeX[], int len) {
	if (viajeX != NULL && len > 0) {
		for (int i = 0; i < len; i++) {
			viajeX[i].isEmpty = VACIO;
		}
	}
}

/// @fn int altaViaje(viaje[], int, tipo, int)
/// @brief Es el menú para dar de alta un viaje
///
/// @param viajeX recibe el array de viajes
/// @param lenViajeX longitud del array de viajes
/// @param tipoX recibe el array de tipos para utlizarlo en la función asignar tipo
/// @param lenTipoX longitud del array de tipos
/// @return retorna 0 si pudo cargar el viaje y -1 si no pudo
int altaViaje(viaje viajeX[], int lenViajeX, tipo tipoX[], int lenTipoX) {
	int retorno;
	viaje buffer;
	int indice;
	int errores;

	retorno = -1;
	errores = 0;

	indice = buscarVacio(viajeX, lenViajeX);

	if (indice >= 0) {
		do {
			buffer.idViaje = asignarId(viajeX, lenViajeX);
			errores += utn_getTexto(buffer.destino,
					"\nIngrese el destino (maximo 20 caracteres): ",
					"ERROR. Destino inválido.", 3);
			errores +=
					utn_getNumero(&buffer.cantidadPasajeros,
							"\nIngrese la cantidad de pasajeros (maximo 100 pasajeros): ",
							"ERROR. Cantidad de pasajeros inválida.", 1, 100,
							3);
			errores +=
					utn_getNumero(&buffer.tipoId,
							"\n1-Aereo\n2-Terrestre\n3-Maritimo\nIngrese el tipo de viaje: ",
							"ERROR. Tipo de viaje invalido,", 1, 3, 3);
			if (errores == 0) {
				viajeX[indice].idViaje = buffer.idViaje;
				strcpy(viajeX[indice].destino, buffer.destino);
				viajeX[indice].cantidadPasajeros = buffer.cantidadPasajeros;
				viajeX[indice].tipoId = buffer.tipoId;
				asignarTipo(tipoX, lenTipoX, indice, buffer.tipoId);
			} else {
				printf(
						"\nAlguno de los datos fue erroneo. Ingrese nuevamente los datos\n");
			}
			retorno = 0;
		} while (errores != 0);
	} else {
		printf(
				"\nNo hay más lugar para cargar datos\nVOLVIENDO AL MENU PRINCIPAL...\n");
	}

	return retorno;
}

/// @fn int buscarVacio(viaje[], int)
/// @brief busca un índice con el campo isEmpty en VACIO dentro del array de viajes
///
/// @param viajeX recibe el array de viajes
/// @param len longitud del array de viajes
/// @return retorna el índice en donde el array tiene el campo isEmpty en VACIO
int buscarVacio(viaje viajeX[], int len) {

	int retorno = -1;

	if (viajeX != NULL && len > 0) {
		for (int i = 0; i < len; i++) {
			if (viajeX[i].isEmpty == VACIO) {
				viajeX[i].isEmpty = LLENO;
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/// @fn int buscarPorId(viaje[], int, int)
/// @brief Busca el índice donde se encuentra el id recibido por parámetro
///
/// @param viajeX recibe el array de viajes
/// @param len longitud del array de viajes
/// @param id recibe el id que se quiere buscar dentro del array
/// @return retorna el índice donde se encuentra el id
int buscarPorId(viaje viajeX[], int len, int id) {

	int retorno = -1;

	if (viajeX != NULL && len > 0 && id > 0) {
		for (int i = 0; i < len; i++) {
			if (viajeX[i].isEmpty == LLENO) {
				if (viajeX[i].idViaje == id) {
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}

/// @fn void menuModificarViaje(viaje[], int)
/// @brief Es el menú donde se modifica el viaje
///
/// @param viajeX recibe el array de viajes
/// @param len longitud del array de viajes
void menuModificarViaje(viaje viajeX[], int len) {

	int id;
	int opcion;
	int index;
	int bufferInt;
	char bufferChar[20];

	if (viajeX != NULL && len > 0) {
		utn_getNumero(&id, "\nIngrese el ID del viaje que desea modificar: ",
				"ERROR. ID invalido.", 100, 103, 3);
		index = buscarPorId(viajeX, len, id);
		if (index >= 0) {
			utn_getNumero(&opcion, "\n1. Destino"
					"\n2. Cantidad de pasajeros"
					"\nQue desea modificar?: ", "ERROR. Opcion invalida.", 1, 2,
					3);
			switch (opcion) {
			case 1:
				if (utn_getTexto(bufferChar, "\nIngrese el nuevo destino: ",
						"ERROR. Destino invalido", 3) == 0) {
					strcpy(viajeX[index].destino, bufferChar);
					printf("\nLa cantidad de pasajeros fue modificada con exito");
				} else {
					printf("\n\n-----VOLVIENDO AL MENU PRINCIPAL-----\n\n");
				}
				break;

			case 2:
				if (utn_getNumero(&bufferInt,
						"\nIngrese la nueva cantidad de pasajeros: ",
						"ERROR. Cantidad de pasajeros invalida.", 1, 100, 3)
						== 0) {
					viajeX[index].cantidadPasajeros = bufferInt;
					printf("\nEl destino fue modificado con exito");
				} else {
					printf("\n\n-----VOLVIENDO AL MENU PRINCIPAL-----\n\n");
				}
				break;
			}
		} else {
			printf("\nNo existe un viaje cargado con ese ID\n");
		}
	}
}

/// @fn void menuDarDeBajaViaje(viaje[], int)
/// @brief muestra el menú para dar de baja un viaje. Lo que hace es poner el campo isEmpty nuevamente en 0 luego de solicitar
/// el id del viaje que se quiere dar de baja
/// @param viajeX recibe el array de viajes
/// @param len longitud del array de viajes
void menuDarDeBajaViaje(viaje viajeX[], int len) {
	int id;
	int index;

	if (viajeX != NULL && len > 0) {
		utn_getNumero(&id, "\nIngrese el ID del viaje que desea dar de baja: ",
				"ERROR. ID invalido.", 100, 103, 3);
		index = buscarPorId(viajeX, len, id);
		if (index >= 0) {
			viajeX[index].isEmpty = VACIO;
			printf("El viaje con el ID %d fue dado de baja exitosamente\n",
					viajeX[index].idViaje);
		} else {
			printf("\nNo existe un viaje cargado con ese ID\n");
		}
	}

}

/// @fn void mostrarViajes(viaje[], int)
/// @brief Imprime por pantalla un listado de los viajes ingresados
///
/// @param viajeX recibe el array de viajes
/// @param len longitud del array de viajes
void mostrarViajes(viaje viajeX[], int len) {

	if (viajeX != NULL && len > 0) {
		printf("\n");
		printf("------------------------------------------------------");
		printf("\n\t-----LISTA DE TODOS LOS VIAJES-----\n");
		printf("------------------------------------------------------");
		printf("\n%-12s | %-15s | %-20s | %s\n", "ID del viaje", "Destino",
				"Cant de pasajeros", "Tipo");
		for (int i = 0; i < len; i++) {
			if (viajeX[i].isEmpty == LLENO) {
				printf("%-12d | %-15s | %-20d | %d", viajeX[i].idViaje,
						viajeX[i].destino, viajeX[i].cantidadPasajeros,
						viajeX[i].tipoId);
			}
			printf("\n");
		}
	}
}

/// @fn int asignarId(viaje[], int)
/// @brief asigna un id autoincremental a cada viaje dado de alta
///
/// @param viajeX recibe el array de viajes
/// @param len longitud del array de viajes
/// @return retorna el numero de id
int asignarId(viaje viajeX[], int len) {
	static int retorno = 100;

	if (viajeX != NULL && len > 0) {
		retorno += 1;
	}

	return retorno;
}
