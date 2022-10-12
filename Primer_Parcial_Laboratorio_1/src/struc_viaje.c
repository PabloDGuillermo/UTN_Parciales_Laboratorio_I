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
/// @brief Inicializa el campo isEmpty en 0 para todos los elementos del array de la estructura viaje
/// @param arrayViajes Recibe el array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
void inicializarViaje(viaje arrayViajes[], int longArrayViajes) {
	if (arrayViajes != NULL && longArrayViajes > 0) {
		for (int i = 0; i < longArrayViajes; i++) {
			arrayViajes[i].isEmpty = VACIO;
		}
	}
}

/// @fn int altaViaje(viaje[], int, tipo, int)
/// @brief Imprime por pantalla el menú para dar de alta un viaje
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud de un array de la estructura viaje
/// @param arrayTipos Recibe un array de la estructura tipo para utlizarlo en la función para asignar tipo
/// @param losArrayTipos Recibe la longitud del array de la estructura tipo
/// @return retorna 0 si pudo cargar el viaje con éxito y -1 si no pudo hacerlo
int altaViaje(viaje arrayViajes[], int longArrayViajes, tipo arrayTipos[]) {
	int retorno;
	viaje buffer;
	int indice;
	int error;
	char opcion;

	retorno = -1;

	indice = buscarViajeVacio(arrayViajes, longArrayViajes);

	if (indice >= 0) {
		do {
			buffer.idViaje = asignarIdViaje(arrayViajes, longArrayViajes);
			printf("---------------------------------------\n");
			printf("------INGRESE LOS DATOS DEL VIAJE------\n");
			printf("---------------------------------------\n");
			error = utn_getTexto(buffer.destino,
					"\nIngrese el destino (maximo 20 caracteres): ",
					"ERROR. Destino inválido.", 20, 3);
			if (error == 0) {
				error =
						utn_getNumero(&buffer.cantidadPasajeros,
								"\nIngrese la cantidad de pasajeros (maximo 100 pasajeros): ",
								"ERROR. Cantidad de pasajeros inválida.", 1,
								100, 3);
				if (error == 0) {
					error =
							utn_getNumero(&buffer.tipoId,
									"\n1-Aereo\n2-Terrestre\n3-Maritimo\nIngrese el tipo de viaje: ",
									"ERROR. Tipo de viaje invalido,", 1, 3, 3);
				}
			}
			if (error == 0) {
				arrayViajes[indice].idViaje = buffer.idViaje;
				strcpy(arrayViajes[indice].destino, buffer.destino);
				arrayViajes[indice].cantidadPasajeros =
						buffer.cantidadPasajeros;
				if (buffer.tipoId == 1) {
					arrayViajes[indice].tipoId = arrayTipos[0].idTipo;
				} else if (buffer.tipoId == 2) {
					arrayViajes[indice].tipoId = arrayTipos[1].idTipo;
				} else {
					arrayViajes[indice].tipoId = arrayTipos[2].idTipo;
				}
				retorno = 0;

			} else {
				utn_getChar(&opcion,
						"Alguno de los datos fue erroneo. Quiere reintentar (s/n)",
						"ERROR. No ingresó una opcion valida", 3);
			}
		} while (opcion == 's');
	} else {
		printf(
				"\nNo hay más lugar para cargar datos\nVOLVIENDO AL MENU PRINCIPAL...\n");
	}

	return retorno;
}

/// @fn int buscarViajeVacio(viaje[], int)
/// @brief Busca un índice con el campo isEmpty en VACIO dentro de un array de la estructura viaje
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
/// @return retorna el índice en donde el array tiene el campo isEmpty en VACIO
int buscarViajeVacio(viaje arrayViajes[], int longArrayViajes) {

	int retorno = -1;

	if (arrayViajes != NULL && longArrayViajes > 0) {
		for (int i = 0; i < longArrayViajes; i++) {
			if (arrayViajes[i].isEmpty == VACIO) {
				arrayViajes[i].isEmpty = LLENO;
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/// @fn int buscarViajePorId(viaje[], int, int)
/// @brief Busca el índice dentro de un aray de la estructura viaje donde se encuentra el ID recibido por parámetro
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
/// @param id Recibe el ID que se quiere buscar dentro del array
/// @return Retorna el índice donde se encuentra el id dentro de un array de la estructura viaje
int buscarViajePorId(viaje arrayViajes[], int longArrayViajes, int id) {

	int retorno = -1;

	if (arrayViajes != NULL && longArrayViajes > 0 && id > 0) {
		for (int i = 0; i < longArrayViajes; i++) {
			if (arrayViajes[i].isEmpty == LLENO) {
				if (arrayViajes[i].idViaje == id) {
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}

/// @fn void menuModificarViaje(viaje[], int)
/// @brief Imprime por pantalla el menú donde se puede modificar uno de los campos dentro
/// de un índice de un array de la estructura viaje
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
void menuModificarViaje(viaje arrayViajes[], int longArrayViajes) {

	int id;
	int indice;

	if (arrayViajes != NULL && longArrayViajes > 0) {
		utn_getNumero(&id, "\nIngrese el ID del viaje que desea modificar: ",
				"ERROR. ID invalido.", 100, 100000, 3);
		indice = buscarViajePorId(arrayViajes, longArrayViajes, id);
		if (indice >= 0) {
			modificarViaje(indice, arrayViajes);
		} else {
			printf("\nNo existe un viaje cargado con ese ID\n");
		}
	}
}

/// @fn void modificarViaje(int, viaje)
/// @brief Función para modificar el destino o la cantidad de pasajeros dentro de un array de la estructura viaje
/// @param indice Índice del array viaje que se quiere modificar. Está previamente
/// validado que exista un viaje cargado con este ID
/// @param arrayViajes Recibe un array de la estructura viaje
void modificarViaje(int indice, viaje arrayViajes[]) {
	int opcion;
	char bufferChar[20];
	int bufferInt;

	utn_getNumero(&opcion, "\n1. Destino"
			"\n2. Cantidad de pasajeros"
			"\nQue desea modificar?: ", "ERROR. Opcion invalida.", 1, 2, 3);
	switch (opcion) {
	case 1:
		if (utn_getTexto(bufferChar, "\nIngrese el nuevo destino: ",
				"ERROR. Destino invalido", 20, 3) == 0) {
			strcpy(arrayViajes[indice].destino, bufferChar);
			printf("\nEl destino fue modificado con exito");
		} else {
			printf("\n\n-----VOLVIENDO AL MENU PRINCIPAL-----\n\n");
		}
		break;

	case 2:
		if (utn_getNumero(&bufferInt,
				"\nIngrese la nueva cantidad de pasajeros: ",
				"ERROR. Cantidad de pasajeros invalida.", 1, 100, 3) == 0) {
			arrayViajes[indice].cantidadPasajeros = bufferInt;
			printf("\nLa cantidad de pasajeros fue modificada con exito");
		} else {
			printf("\n\n-----VOLVIENDO AL MENU PRINCIPAL-----\n\n");
		}
		break;
	}
}

/// @fn void menuDarDeBajaViaje(viaje[], int)
/// @brief Imprime por pantalla el menú para dar de baja un viaje.
/// Lo que hace es poner el campo isEmpty nuevamente en 0 luego de solicitar
/// el id del viaje que se quiere dar de baja
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
void menuDarDeBajaViaje(viaje arrayViajes[], int longArrayViajes) {
	int id;
	int indice;

	if (arrayViajes != NULL && longArrayViajes > 0) {
		utn_getNumero(&id, "\nIngrese el ID del viaje que desea dar de baja: ",
				"ERROR. ID invalido.", 100, 100000, 3);
		indice = buscarViajePorId(arrayViajes, longArrayViajes, id);
		if (indice >= 0) {
			arrayViajes[indice].isEmpty = VACIO;
			printf("El viaje con el ID %d fue dado de baja exitosamente\n",
					arrayViajes[indice].idViaje);
		} else {
			printf("\nNo existe un viaje cargado con ese ID\n");
		}
	}

}

/// @fn void listarViajes(viaje[], int)
/// @brief Imprime por pantalla un listado de los viajes ingresados
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
void listarViajes(viaje arrayViajes[], int longArrayViajes) {

	if (arrayViajes != NULL && longArrayViajes > 0) {
		ordenarPorId(arrayViajes, longArrayViajes);
		printf("\n");
		printf("------------------------------------------------------");
		printf("\n\t-----LISTA DE TODOS LOS VIAJES-----\n");
		printf("------------------------------------------------------");
		printf("\n%-12s | %-15s | %-20s | %s\n", "ID del viaje", "Destino",
				"Cant de pasajeros", "Tipo");
		for (int i = 0; i < longArrayViajes; i++) {
			if (arrayViajes[i].isEmpty == LLENO) {
				printf("%-12d | %-15s | %-20d | %d\n", arrayViajes[i].idViaje,
						arrayViajes[i].destino,
						arrayViajes[i].cantidadPasajeros,
						arrayViajes[i].tipoId);
			}
		}
	}
}

/// @fn int asignarId(viaje[], int)
/// @brief asigna un id autoincremental para cada viaje dado de alta dentro de un array de la estructura viaje
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
/// @return Retorna el numero de id
int asignarIdViaje(viaje arrayViajes[], int longArrayViajes) {
	static int retorno = 100;

	if (arrayViajes != NULL && longArrayViajes > 0) {
		retorno += 1;
	}

	return retorno;
}

/// @fn int ordenarPorId(viaje[], int)
/// @brief Ordena un array de la estructura viaje por ID de menor a mayor.
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
void ordenarPorId(viaje arrayViajes[], int longArrayViajes) {
	viaje bufferViaje;
	int flagSwap;

	if (arrayViajes != NULL && longArrayViajes > 0) {
		do {
			flagSwap = 0;
			longArrayViajes = longArrayViajes - 1;
			for (int i = 0; i < longArrayViajes; i++) {
				if (arrayViajes[i].idViaje > arrayViajes[i + 1].idViaje) {
					bufferViaje = arrayViajes[i];
					arrayViajes[i] = arrayViajes[i + 1];
					arrayViajes[i + 1] = bufferViaje;
					flagSwap = -1;
				}
			}
		} while (flagSwap == -1);
	}
}

/// @fn void listarViajesPorTipo(viaje[], int, tipo[], int)
/// @brief Imprime por pantalla una lista de los viajes cargados dentro de un array de la estructura
/// de un tipo determinado por el usuario
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
/// @param arrayTipos Recibe un array de la estructura tipo
/// @param longArrayTipos Recibe la longitud del array de la estructura tipo
void listarViajesPorTipo(viaje arrayViajes[], int longArrayViajes,
		tipo arrayTipos[], int longArrayTipos) {
	int tipo;
	int error;

	if (arrayViajes != NULL && longArrayViajes > 0) {
		listarTipos(arrayTipos, longArrayTipos);
		error = utn_getNumero(&tipo, "Seleccione el tipo: ",
				"ERROR. Ese tipo no existe.", 1000, 1002, 3);
		if (error == 0) {
			ordenarPorId(arrayViajes, longArrayViajes);
			printf("\n");
			printf("--------------------------------------------------");
			printf("\n-----LISTA DE TODOS LOS VIAJES DEL TIPO %d-----\n", tipo);
			printf("--------------------------------------------------");
			printf("\n%-12s | %-15s | %-20s | %s\n", "ID del viaje", "Destino",
					"Cant de pasajeros", "Descripcion");

			switch (tipo) {

			case 1000:
				for (int i = 0; i < longArrayViajes; i++) {
					if (arrayViajes[i].isEmpty == LLENO
							&& arrayViajes[i].tipoId == 1000) {
						printf("%-12d | %-15s | %-20d | %s\n",
								arrayViajes[i].idViaje, arrayViajes[i].destino,
								arrayViajes[i].cantidadPasajeros,
								arrayTipos[0].descripcion);
					}
				}
				break;
			case 1001:
				for (int i = 0; i < longArrayViajes; i++) {
					if (arrayViajes[i].isEmpty == LLENO
							&& arrayViajes[i].tipoId == 1001) {
						printf("%-12d | %-15s | %-20d | %s\n",
								arrayViajes[i].idViaje, arrayViajes[i].destino,
								arrayViajes[i].cantidadPasajeros,
								arrayTipos[1].descripcion);
					}
				}
				break;

			case 1002:
				for (int i = 0; i < longArrayViajes; i++) {
					if (arrayViajes[i].isEmpty == LLENO
							&& arrayViajes[i].tipoId == 1002) {
						printf("%-12d | %-15s | %-20d | %s\n",
								arrayViajes[i].idViaje, arrayViajes[i].destino,
								arrayViajes[i].cantidadPasajeros,
								arrayTipos[2].descripcion);
					}
				}
				break;
			}
		} else {
			printf("\nVOLVIENDO AL MENU DE INFORMES...\n");
		}
	}
}
