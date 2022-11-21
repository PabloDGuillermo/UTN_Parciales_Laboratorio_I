/*
 * inputs.h
 *
 *  Created on: 1 nov. 2022
 *      Author: pablo
 */

#ifndef INPUTS_H_
#define INPUTS_H_

int utn_pedirNumero(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int reintentos);
int esNumerica(char *cadena);
int getInt(int *pResultado);
int myGets(char *cadena, int longitud);
int utn_pedirNumeroFlotante(float *pResultado, char *mensaje,
		char *mensajeError, float minimo, float maximo, int reintentos);
int esNumericaFlotante(char *cadena);
int getFloat(float *pResultado);
int utn_pedirTexto(char *pResultado, char *mensaje, char *mensajeError,
		int maxCaracteres, int reintentos);
int utn_pedirChar(char *pResultado, char *mensaje, char *mensajeError,
		int reintentos);
int getChar(char *pResultado);
int esChar(char *cadena);
int utn_pedirTarjetaDeCredito(char *pResultado, int reintentos);
int utn_pedirFecha(int *pDia, int *pMes, int *pAnio, int reintentos);

#endif /* INPUTS_H_ */
