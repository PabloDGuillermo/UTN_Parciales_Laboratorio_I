/*
 * struc_tipo.c
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#include <stdio.h>
#include "struc_tipo.h"
#include "struc_viaje.h"
#include "inputs.h"
#include <string.h>

#define VACIO 0
#define LLENO 1

void inicializarTipo(tipo tipoX[], int len){
	if(tipoX!=NULL && len>0){
		for(int i=0;i<len;i++){
			tipoX[i].isEmpty=VACIO;
		}
	}
}

void descripcionTipoSegunId(tipo tipoX){
	if(tipoX.idTipo==1000){
		strcpy(tipoX.descripcion,"AEREO");
	}else if(tipoX.idTipo==1001){
		strcpy(tipoX.descripcion,"TERRESTRE");
	}else if(tipoX.idTipo==1002){
		strcpy(tipoX.descripcion,"MARITIMO");
	}
}

void asignarTipo(tipo tipoX[], int len, int index, int eleccion){

	if(eleccion == 1){
		tipoX[index].idTipo=1000;
		tipoX[index].isEmpty=LLENO;
	}else if(eleccion==2){
		tipoX[index].idTipo=1001;
		tipoX[index].isEmpty=LLENO;
	}else{
		tipoX[index].idTipo=1002;
		tipoX[index].isEmpty=LLENO;
	}

}

/*void mostrarTipos(tipo tipoX[], int len) {

	if (tipoX != NULL && len > 0) {
		printf("\n");
		printf("------------------------------------------------------");
		printf("\n\t-----LISTA DE TODOS LOS TIPOS-----\n");
		printf("------------------------------------------------------");
		printf("\n%-12s | %-15s \n", "ID del Tipo", "Descripcion");
		for (int i = 0; i < len; i++) {
			if (tipoX[i].isEmpty == LLENO) {
				printf("%-12d | %-15s", tipoX[i].idTipo,
						tipoX[i].descripcion);
			}
			printf("\n");
		}
	}
}
*/
