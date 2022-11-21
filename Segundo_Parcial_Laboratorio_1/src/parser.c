/*
 * parser.c
 *
 *  Created on: 13 nov. 2022
 *      Author: pablo
 */

#include <stdio.h>

#include "LinkedList.h"
#include "Venta.h"

/// @fn int parser_VentasFromText(FILE*, LinkedList*)
/// @brief Interpreta y guarda los datos de un archivo de texto en una LinkedList
/// @param pFile Puntero a archivo que se debe leer
/// @param pArrayListVentas Puntero a la LinkedList donde se guardaran los datos
/// @return Retorna 0 si pudo leer el archivo y guardar los datos y -1 si no pudo
int parser_VentasFromText(FILE *pFile, LinkedList *pArrayListVentas) {
	int retorno;
	char idVentaStr[10];
	char fechaDiaStr[10];
	char fechaMesStr[10];
	char fechaAnioStr[10];
	char modeloAutoStr[50];
	char cantidadStr[10];
	char precioUnitarioStr[50];
	char tarjetaDeCreditoStr[17];
	int retornoFunc;
	Venta *pElemento = NULL;

	retorno = -1;

	fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idVentaStr,
			fechaDiaStr, modeloAutoStr, cantidadStr, precioUnitarioStr,
			tarjetaDeCreditoStr);
	do {
		retornoFunc = fscanf(pFile,
				"%[^,],%[^/]/%[^/]/%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
				idVentaStr, fechaDiaStr, fechaMesStr, fechaAnioStr,
				modeloAutoStr, cantidadStr, precioUnitarioStr,
				tarjetaDeCreditoStr);

		if (retornoFunc == 8) {
			pElemento = venta_newParametros(idVentaStr, fechaDiaStr,
					fechaMesStr, fechaAnioStr, modeloAutoStr, cantidadStr,
					precioUnitarioStr, tarjetaDeCreditoStr);
			if (pElemento != NULL) {
				if (ll_add(pArrayListVentas, pElemento) == 0) {
					retorno = 0;
				}
			} else {
				printf("\nERROR EN EL PARSER.");
				retorno = -1;
				break;
			}
		}
	} while (!feof(pFile));

	return retorno;
}

/// @fn int parser_VentasFromBinary(FILE*, LinkedList*)
/// @brief Interpreta y guarda los datos de un archivo binario en una LinkedList
/// @param pFile Puntero al archivo que se debe leer
/// @param pArrayListVentas Puntero a la LinkedList donde se guardaran los datos
/// @return Retorna 0 si pudo leer el archivo y guardar los datos y -1 si no pudo
int parser_VentasFromBinary(FILE *pFile, LinkedList *pArrayListVentas) {
	int retorno;
	int retornoFunc;
	Venta *pVenta = NULL;

	retorno = -1;

	do {
		pVenta = venta_new();
		retornoFunc = fread(pVenta, sizeof(Venta), 1, pFile);
		if (retornoFunc == 1) {
			if (pVenta != NULL) {
				if (ll_add(pArrayListVentas, pVenta) == 0) {
					retorno = 0;
				}
			} else {
				printf("\nERROR EN EL PARSER.");
				retorno = -1;
				break;
			}
		}
	} while (!feof(pFile));

	return retorno;
}

/// @fn int parser_IdUnicoFromText(FILE*, int*)
/// @brief Interpreta un archivo de texto y guarda el dato en una variable
/// @param pFile Puntero al archivo de texto
/// @param id Puntero a la variable donde guardara el dato
/// @return Retorna 0 si pudo leer el archivo y guardar el dato y -1 si no pudo
int parser_IdUnicoFromText(FILE *pFile, int *id) {
	int retorno;
	int cantidadLeida;
	int auxId;

	retorno = -1;

	if (pFile != NULL && id != NULL) {
		cantidadLeida = fscanf(pFile, "%d", &auxId);
		if (cantidadLeida == 1) {
			*id = auxId;
			retorno = 0;
		}
	}
	return retorno;
}
