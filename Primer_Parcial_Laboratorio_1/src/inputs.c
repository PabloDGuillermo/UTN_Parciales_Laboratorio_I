/*
 * inputs.c
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputs.h"

int utn_getNumero(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int reintentos) {
	int bufferInt;
	int retorno = -1;
	while (reintentos > 0) {
		reintentos--;
		printf("%s", mensaje);
		if (getInt(&bufferInt) == 0) {
			if (bufferInt >= minimo && bufferInt <= maximo) {
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
		}
		printf("%s\n", mensajeError);
	}
	return retorno;
}

int esNumerica(char *cadena) {
	int i = 0;
	int retorno = 1;
	if (cadena != NULL && strlen(cadena) > 0) {
		while (cadena[i] != '\0') {
			if(cadena[0]!='-'){
				if (cadena[i] < '0' || cadena[i] > '9') {
					retorno = 0;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}

int getInt(int *pResultado) {
	int retorno = -1;
	char buffer[64];
	if (pResultado != NULL) {
		if (myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer)) {
			*pResultado = atoi(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

int myGets(char *cadena, int longitud) {
	if (cadena != NULL && longitud > 0
			&& fgets(cadena, longitud, stdin) == cadena) {
		fflush(stdin);
		if (cadena[strlen(cadena) - 1] == '\n') {
			cadena[strlen(cadena) - 1] = '\0';
		}
		return 0;
	}
	return -1;
}

int utn_getNumeroFlotante(float *pResultado, char *mensaje, char *mensajeError,
		float minimo, float maximo, int reintentos) {
	float bufferFloat;
	int retorno = -1;
	while (reintentos > 0) {
		reintentos--;
		printf("%s", mensaje);
		if (getFloat(&bufferFloat) == 0) {
			if (bufferFloat >= minimo && bufferFloat <= maximo) {
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
		}
		printf("%s\n", mensajeError);
	}
	return retorno;
}

int esNumericaFlotante(char *cadena) {
	int i = 0;
	int retorno = 1;
	if (cadena != NULL && strlen(cadena) > 0) {
		while (cadena[i] != '\0') {
			if(cadena[0]!='-' && cadena[i]!='.'){
				if (cadena[i] < '0' || cadena[i] > '9') {
					retorno = 0;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}

int getFloat(float *pResultado) {
	int retorno = -1;
	char buffer[64];
	if (pResultado != NULL) {
		if (myGets(buffer, sizeof(buffer)) == 0 && esNumericaFlotante(buffer)) {
			*pResultado = atof(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

int utn_getTexto(char *pResultado, char *mensaje, char *mensajeError,
			int reintentos) {
	char bufferTexto[64];
	int retorno = -1;
	while (reintentos > 0) {
		reintentos--;
		printf("%s", mensaje);
		if (myGets(bufferTexto,sizeof(bufferTexto)) == 0) {
			strcpy(pResultado, bufferTexto);
			retorno = 0;
			break;
		}
		printf("%s\n", mensajeError);
	}
	return retorno;
}
