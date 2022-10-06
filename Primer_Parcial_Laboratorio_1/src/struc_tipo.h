/*
 * struc_tipo.h
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#ifndef STRUC_TIPO_H_
#define STRUC_TIPO_H_

typedef struct{
	int idTipo;
	char descripcion[30];
	int isEmpty;
}tipo;

void inicializarTipo(tipo tipoX[], int len);
void asignarTipo(tipo tipoX[], int len, int index, int eleccion);

#endif /* STRUC_TIPO_H_ */
