/*
 ============================================================================
 Name        : Primer_Parcial_Laboratorio_1.c
 Author      : Pablo Guillermo
 Version     :
 Copyright   : 1ra Div E
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "struc_tipo.h"
#include "struc_viaje.h"
#include "struc_voucher.h"

#define LONG_ARRAYS 3

int main(void) {
	setbuf(stdout,NULL);

	tipo tipos[LONG_ARRAYS];
	viaje viajes[LONG_ARRAYS];
	voucher vouchers[LONG_ARRAYS];

	inicializarTipo(tipos,LONG_ARRAYS);
	inicializarViaje(viajes, LONG_ARRAYS);
	inicializarVoucher(vouchers,LONG_ARRAYS);


	int opcion;
	int error;
	int contadorViajesCargados;

	contadorViajesCargados=0;

	do{
		printf("----------------------------------------\n");
		printf("\t-----MENU PRINCIPAL-----\n");
		printf("----------------------------------------\n");
		error=utn_getNumero(&opcion, "1. Alta viaje\n"
				"2. Modificar viaje\n"
				"3. Baja viaje\n"
				"4. Listar viajes\n"
				"5. Listar tipos\n"
				"6. Alta Voucher\n"
				"7. Listar Voucher\n"
				"8. Informes\n"
				"9. Salir\n"
				"¿Qué opción quiere elegir?: ", "No ingresó una opción válida", 1,9,3);

		if(error==0){
			switch(opcion){

			case 1:
				if(altaViaje(viajes,LONG_ARRAYS,tipos,LONG_ARRAYS)==0){
					contadorViajesCargados++;
				}
				break;

			case 2:
				if(contadorViajesCargados>0){
					mostrarViajes(viajes,LONG_ARRAYS);
					menuModificarViaje(viajes,LONG_ARRAYS);
				}else{
					printf("\nAún no se ingresó por lo menos un viaje\n");
				}
				break;

			case 3:
				if(contadorViajesCargados>0){
					mostrarViajes(viajes,LONG_ARRAYS);
					menuDarDeBajaViaje(viajes,LONG_ARRAYS);
					contadorViajesCargados--;
				}else{
					printf("\nAún no se ingresó por lo menos un viaje\n");
				}
				break;

			case 4:
				if(contadorViajesCargados>0){
					mostrarViajes(viajes, LONG_ARRAYS);
				}else{
					printf("\nAún no se ingresó por lo menos un viaje\n");
				}
				break;

			case 5:
				printf("Entre 5");
				break;

			case 6:
				printf("Entre 6");
				break;

			case 7:
				printf("Entre 7");
				break;

			case 8:
				printf("Entre 8");
				break;

			}
		}

		printf("\n");
	}while(opcion!=9);

	printf("-----PROGRAMA FINALIZADO-----");

	return EXIT_SUCCESS;
}
