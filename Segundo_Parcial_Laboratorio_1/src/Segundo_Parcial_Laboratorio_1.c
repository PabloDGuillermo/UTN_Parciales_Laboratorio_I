/*
 ============================================================================
 Name        : Segundo_Parcial_Laboratorio_1.c
 Author      : Pablo Guillermo
 Version     :
 Copyright   : 1ra Div E
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "inputs.h"
#include "LinkedList.h"
#include "Controller.h"
#include "Venta.h"

int main(void) {
	setbuf(stdout, NULL);

	int opcion;
	char confirmacion;
	LinkedList *listaVentas = NULL;
	LinkedList *listaVentasBinario = NULL;
	Venta *pVenta = NULL;
	int flagCargaArchivos;
	int flagGuardado;
	int contadorVentasAgregadas;
	int idUnico;
	int longitudLista;

	flagCargaArchivos = 0;
	flagGuardado = 0;
	contadorVentasAgregadas = 0;

	listaVentas = ll_newLinkedList();
	listaVentasBinario = ll_newLinkedList();

	if (listaVentas != NULL && listaVentasBinario != NULL) {

		do {
			opcion = -1;
			confirmacion = 'z';
			longitudLista = ll_len(listaVentas);

			printf("==========================\n");
			printf("|-----MENU PRINCIPAL-----|\n");
			printf("--------------------------\n");

			utn_pedirNumero(&opcion, "\n1 - Carga de archivos"
					"\n2 - Alta de venta"
					"\n3 - Baja de venta"
					"\n4 - Modificacion de venta"
					"\n5 - Generar informe de ventas"
					"\n6 - Cargar archivo binario"
					"\n7 - Guardar archivo de texto"
					"\n8 - Guardar archivo binario"
					"\n9 - Salir"
					"\nElija una opcion: ", "ERROR. Opcion invalida.", 1, 9, 3);

			switch (opcion) {

			case 1:
				if (flagCargaArchivos == 0) {
					if (controller_cargarVentasDesdeTexto("Archivo_Ventas.csv",
							listaVentas) == 0) {
						printf(
								"\nEL ARCHIVO DE VENTAS SE LEYO CORRECTAMENTE\n");
						flagCargaArchivos = 1;
					} else {
						printf(
								"\nHUBO UN ERROR AL LEER EL ARCHIVO DE VENTAS\n");
					}
				} else {
					printf(
							"\nLOS ARCHIVOS YA FUERON CARGADOS.\nVOLVER A CARGARLOS RESULTARIA EN ERRRORES EN EL PROGRAMA Y PERDIDA DE DATOS.\n");
				}
				break;

			case 2:
				if (flagCargaArchivos == 1) {
					pVenta = controller_agregarVenta(listaVentas);
					if (pVenta != NULL) {
						if (controller_asignarIdUnico(pVenta) == 0) {
							printf("\nLA VENTA FUE AGREGADA CORRECTAMENTE\n");
							contadorVentasAgregadas++;
						}
					}
				} else {
					printf("\nAUN NO HAY VENTAS CARGADAS\n");
				}
				break;

			case 3:
				if (flagCargaArchivos == 1 && longitudLista > 0) {
					if (controller_removerVenta(listaVentas) == 0) {
						printf("\nLA VENTA FUE DADA DE BAJA CORRECTAMENTE\n");
					}
				} else {
					printf("\nAUN NO HAY VENTAS CARGADAS\n");
				}
				break;

			case 4:
				if (flagCargaArchivos == 1 && longitudLista > 0) {
					if (controller_editarVenta(listaVentas) == 0) {
						printf("\nLA VENTA FUE EDITADA CORRECTAMENTE\n");
					}
				} else {
					printf("\nAUN NO HAY VENTAS CARGADAS\n");
				}
				break;

			case 5:
				if (flagCargaArchivos == 1 && longitudLista > 0) {
					if (controller_generarInformeDeVentas(listaVentas) == 0) {
						printf(
								"\nEL INFORME DE VENTAS SE GENERO CORRECTAMENTE\n");
					}
				} else {
					printf("\nAUN NO HAY VENTAS CARGADAS\n");
				}
				break;

			case 6:
				if (controller_cargarVentasDesdeBinario(
						"Archivo_Ventas_Binario.bin", listaVentasBinario)
						== 0) {
					printf("\nEL ARCHIVO BINARIO SE CARGO CORRECTAMENTE\n");
				}
				break;

			case 7:
				if (flagCargaArchivos == 1
						&& controller_guardarVentasModoTexto(
								"Archivo_Ventas.csv", listaVentas) == 0) {
					printf("\nEL ARCHIVO DE TEXTO SE GUARDO EXITOSAMENTE\n");
					flagGuardado = 1;
				} else {
					printf("\nAUN NO HAY VENTAS CARGADAS\n");
				}
				break;

			case 8:
				if (controller_guardarVentasModoBinario(
						"Archivo_Ventas_Binario.bin", listaVentas) == 0) {
					printf(
							"\nEL ARCHIVO BINARIO DE VENTAS SE GUARDO CORRECTAMENTE\n");
				}
				break;

			case 9:
				utn_pedirChar(&confirmacion,
						"Todos los datos que no se hayan guardado se perderan\n"
								"seguro que desea salir? (s/n): ",
						"ERROR. opcion invalida", 3);
				break;
			}

			if (opcion == 9 && confirmacion == 's' && flagGuardado != 1) {
				controller_cargarIdUnicoDesdeTexto("ID_Unico.csv", &idUnico);
				idUnico = idUnico - contadorVentasAgregadas;
				controller_guardarIdUnicoModoTexto("ID_Unico.csv", idUnico);
			}
		} while (opcion != 9 && confirmacion != 's');
	} else {
		printf("\nERROR AL CREAR LA LINKEDLIST\n");
	}

	printf("\n----------PROGRAMA FINALIZADO----------");

	return EXIT_SUCCESS;
}
