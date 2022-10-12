/*
 * inputs.h
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#ifndef INPUTS_H_
#define INPUTS_H_

int utn_getNumero(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int reintentos);
int esNumerica(char *cadena);
int getInt(int *pResultado);
int myGets(char *cadena, int longitud);
int utn_getNumeroFlotante(float *pResultado, char *mensaje, char *mensajeError,
		float minimo, float maximo, int reintentos);
int esNumericaFlotante(char *cadena);
int getFloat(float *pResultado);
int utn_getTexto(char *pResultado, char *mensaje, char *mensajeError,
		int maxCaracteres, int reintentos);
int utn_getChar(char *pResultado, char *mensaje, char *mensajeError,
		int reintentos);
int utn_getFecha(int *dia, int *mes, int *anio, int reintentos);

#endif /* INPUTS_H_ */
