/*
 * struc_tipo.c
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#include <stdio.h>
#include "struc_tipo.h"
#include "inputs.h"
#include <string.h>

#define VACIO 0
#define LLENO 1

/// @fn void inicializarTipo(tipo[], int)
/// @brief Inicializa un array de la estructura tipo poniéndo el campo isEmpty como lleno, el ID incremental
/// y la descripción según el ID
/// @param arrayTipos Recibe un array de la estructura tipo
/// @param longArrayTipos Recibe la longitud del array de la estructura tipo
void inicializarTipo(tipo arrayTipos[], int longArrayTipos) {
	int id;

	id = 1000;

	if (arrayTipos != NULL && longArrayTipos > 0) {
		for (int i = 0; i < longArrayTipos; i++) {
			arrayTipos[i].isEmpty = LLENO;
			arrayTipos[i].idTipo = id;
			descripcionTipoSegunId(arrayTipos, i);
			id += 1;
		}
	}
}

/// @fn void descripcionTipoSegunId(tipo[], int)
/// @brief Le asigna una cadena de caracteres al campo descripción según el id del tipo
/// @param arrayTipos Recibe un array de la estructura tipo
/// @param indice recibe el índice en del array en donde debe escribir el campo descripción
void descripcionTipoSegunId(tipo arrayTipos[], int indice) {
	if (arrayTipos[indice].idTipo == 1000) {
		strcpy(arrayTipos[indice].descripcion, "AEREO");
	} else if (arrayTipos[indice].idTipo == 1001) {
		strcpy(arrayTipos[indice].descripcion, "TERRESTRE");
	} else if (arrayTipos[indice].idTipo == 1002) {
		strcpy(arrayTipos[indice].descripcion, "MARITIMO");
	}
}

/// @fn int buscarTipoSegunDescripcion(char[])
/// @brief Retorna el índice donde el array de la estructura tipo tiene la descripción solicitada
/// @param descripcion Recibe una cadena de caracteres que refiere a la descripción
/// @return Retorna 0 si pudo encontrar el índice y -1 si no pudo hacerlo
int buscarTipoSegunDescripcion(char descripcion[]) {
	int indice;

	indice = -1;

	if (strcmp(descripcion, "AEREO") == 0) {
		indice = 0;
	} else if (strcmp(descripcion, "TERRESTRE") == 0) {
		indice = 1;
	} else if (strcmp(descripcion, "MARITIMO") == 0) {
		indice = 2;
	}

	return indice;
}

/// @fn void listarTipos(tipo[], int)
/// @brief Imprime por pantalla una lista de los tipos disponibles hasta el momento
/// @param arrayTipos Recibe un array de la estructura tipo
/// @param longArrayTipos Recibe la longitud del array de la estructura tipo
void listarTipos(tipo arrayTipos[], int longArrayTipos) {

	if (arrayTipos != NULL && longArrayTipos > 0) {
		printf("\n");
		printf("------------------------------------------------------");
		printf("\n\t-----LISTA DE TODOS LOS TIPOS-----\n");
		printf("------------------------------------------------------");
		printf("\n%-12s | %-15s\n", "ID del Tipo", "Descripcion");
		for (int i = 0; i < longArrayTipos; i++) {
			if (arrayTipos[i].isEmpty == LLENO) {
				printf("%-12d | %-15s", arrayTipos[i].idTipo,
						arrayTipos[i].descripcion);
			}
			printf("\n");
		}
	}
}

