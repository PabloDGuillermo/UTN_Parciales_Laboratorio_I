/*
 * menues.c
 *
 *  Created on: 9 oct. 2022
 *      Author: pablo
 */

#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "struc_tipo.h"
#include "struc_viaje.h"
#include "struc_voucher.h"
#include "menues.h"

/// @fn void mostrarMenuPrincipal(viaje[], tipo[], voucher[], int, int, int)
/// @brief Imprime por pantalla el menú principal del programa
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param arrayTipos Recibe un array de la estructura tipo
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
/// @param longArrayTipos Recibe la longitud del array de la estructura tipo
/// @param longArrayVouchers Recibe la longitud del array de la estructura voucher
void mostrarMenuPrincipal(viaje arrayViajes[], tipo arrayTipos[],
		voucher arrayVouchers[], int longArrayViajes, int longArrayTipos,
		int longArrayVouchers) {

	int opcion;
	int error;
	int contadorViajesCargados;

	contadorViajesCargados = 0;

	do {
		printf("----------------------------------------\n");
		printf("\t-----MENU PRINCIPAL-----\n");
		printf("----------------------------------------\n");
		error = utn_getNumero(&opcion, "1. Alta viaje\n"
				"2. Modificar viaje\n"
				"3. Baja viaje\n"
				"4. Listar viajes\n"
				"5. Listar tipos\n"
				"6. Alta Voucher\n"
				"7. Listar Voucher\n"
				"8. Informes\n"
				"9. Salir\n"
				"¿Qué opción quiere elegir?: ", "No ingresó una opción válida",
				1, 9, 3);

		if (error == 0) {
			switch (opcion) {

			case 1:
				if (altaViaje(arrayViajes, longArrayViajes, arrayTipos) == 0) {
					contadorViajesCargados++;
				}
				break;

			case 2:
				if (contadorViajesCargados > 0) {
					listarViajes(arrayViajes, longArrayViajes);
					menuModificarViaje(arrayViajes, longArrayViajes);
				} else {
					printf("\nAún no se ingresó por lo menos un viaje\n");
				}
				break;

			case 3:
				if (contadorViajesCargados > 0) {
					listarViajes(arrayViajes, longArrayViajes);
					menuDarDeBajaViaje(arrayViajes, longArrayViajes);
					contadorViajesCargados--;
				} else {
					printf("\nAún no se ingresó por lo menos un viaje\n");
				}
				break;

			case 4:
				if (contadorViajesCargados > 0) {
					listarViajes(arrayViajes, longArrayViajes);
				} else {
					printf("\nAún no se ingresó por lo menos un viaje\n");
				}
				break;

			case 5:
				listarTipos(arrayTipos, longArrayTipos);
				break;

			case 6:
				if (contadorViajesCargados > 0) {
					altaVoucher(arrayVouchers, longArrayVouchers, arrayViajes,
							longArrayViajes, arrayTipos);
				} else {
					printf("\nAún no se ingresó por lo menos un viaje\n");
				}
				break;

			case 7:
				listarVoucher(arrayVouchers, longArrayVouchers);
				break;

			case 8:
				mostrarMenuInformes(arrayViajes, arrayTipos, arrayVouchers,
						longArrayViajes, longArrayTipos, longArrayVouchers);
				break;

			}
		}

		printf("\n");
	} while (opcion != 9);

	printf("-----PROGRAMA FINALIZADO-----");

}

/// @fn void mostrarMenuInformes(viaje[], tipo[], voucher[], int, int, int)
/// @brief Imprime por pantalla el menú de la sección informes
/// @param arrayViajes Recibe un array de la estructura viaje
/// @param arrayTipos Recibe un array de la estructura tipo
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
/// @param longArrayTipos Recibe la longitud del array de la estructura tipo
/// @param longArrayVouchers Recibe la longitud del array de la estructura voucher
void mostrarMenuInformes(viaje arrayViajes[], tipo arrayTipos[],
		voucher arrayVouchers[], int longArrayViajes, int longArrayTipos,
		int longArrayVouchers) {
	int opcion;
	int error;

	do {
		printf("-----------------------------------------\n");
		printf("\t-----MENU DE INFORMES-----\n");
		printf("-----------------------------------------\n");
		error =
				utn_getNumero(&opcion,
						"\n1 - Mostrar viajes de un tipo seleccionado"
								"\n2 - Mostrar todos los vouchers efectuados en una fecha seleccionada"
								"\n3 - Informar importe total de los vouchers realizados para un viaje seleccionado"
								"\n4 - Informar importe total de todos los vouchers de un tipo en una fecha seleccionada"
								"\n5 - Volver"
								"\nElija una opcion: ",
						"ERROR. No selecciono una opcion valida.", 1, 5, 3);
		if (error == 0) {
			switch (opcion) {

			case 1:
				listarViajesPorTipo(arrayViajes, longArrayViajes, arrayTipos,
						longArrayTipos);
				break;

			case 2:
				listarVoucherPorFecha(arrayVouchers, longArrayVouchers);
				break;

			case 3:
				importeTotalVoucherPorViaje(arrayVouchers, longArrayVouchers,
						arrayViajes, longArrayViajes);
				break;

			case 4:
				importeTotalVoucherPorTipoYFecha(arrayVouchers,
						longArrayVouchers, arrayTipos, longArrayTipos);
				break;
			}
		}
	} while (opcion != 5);

}
