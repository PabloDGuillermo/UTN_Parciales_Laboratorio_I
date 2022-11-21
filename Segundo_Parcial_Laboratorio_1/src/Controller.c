/*
 * Controller.c
 *
 *  Created on: 13 nov. 2022
 *      Author: pablo
 */

#include <stdio.h>

#include "LinkedList.h"
#include "parser.h"
#include "Venta.h"
#include "Controller.h"
#include "inputs.h"

/// @fn int controller_cargarVentasDesdeTexto(char*, LinkedList*)
/// @brief Carga un archivo de texto y guarda los datos en una LinkedList
/// @param path Es el nombre del archivo
/// @param pArrayListVentas Es la LinkedList donde se guardaran los datos
/// @return Retorna 0 si pudo leer el archivo y -1 si no lo hizo
int controller_cargarVentasDesdeTexto(char *path, LinkedList *pArrayListVentas) {
	int retorno;
	FILE *pArchivo = NULL;

	retorno = -1;
	if (path != NULL && pArrayListVentas != NULL) {
		pArchivo = fopen(path, "r");
		if (pArchivo != NULL) {
			if (parser_VentasFromText(pArchivo, pArrayListVentas) == 0) {
				retorno = 0;
			}
		} else {
			pArchivo = fopen(path, "w");
			if (pArchivo != NULL) {
				printf(
						"\nEL ARCHIVO DE VENTAS NO EXISTIA Y SE CREO CORRECTAMENTE\n");
				retorno = 1;
			}
		}
		fclose(pArchivo);
	}

	return retorno;
}

/// @fn int controller_cargarVentasDesdeBinario(char*, LinkedList*)
/// @brief Carga un archivo binario y guarda los datos en una LinkedList
/// @param path Es el nombre del archivo
/// @param pArrayListVentas Es la LinkedList donde se guardaran los datos
/// @return Retorna 0 si pudo leerlo y -1 si no pudo
int controller_cargarVentasDesdeBinario(char *path,
		LinkedList *pArrayListVentas) {
	int retorno;
	FILE *pArchivo = NULL;

	retorno = -1;
	if (path != NULL && pArrayListVentas != NULL) {
		pArchivo = fopen(path, "rb");
		if (pArchivo != NULL) {
			if (parser_VentasFromBinary(pArchivo, pArrayListVentas) == 0) {
				printf(
						"\nEL ARCHIVO BINARIO DE VENTAS SE LEYO CORRECTAMENTE\n");
				retorno = 0;
			} else {
				printf(
						"\nHUBO UN ERROR AL LEER EL ARCHIVO BINARIO DE VENTAS\n");
			}
		} else {
			pArchivo = fopen(path, "wb");
			if (pArchivo != NULL) {
				printf(
						"\nEL ARCHIVO BINARIO DE VENTAS NO EXISTIA Y SE CREO CORRECTAMENTE\n");
				retorno = 1;
			}
		}
		fclose(pArchivo);
	}

	return retorno;
}

/// @fn Venta controller_agregarVenta*(LinkedList*)
/// @brief Agrega un elemento venta a la LinkedList
/// @param pArrayListVentas La LinkedList a la que quiero agregarle el elemento
/// @return Retorna el puntero de la estructura Venta que se acaba de crear
Venta* controller_agregarVenta(LinkedList *pArrayListVentas) {
	int auxId;
	int auxFechaDia;
	int auxFechaMes;
	int auxFechaAnio;
	char auxModelo[50];
	int auxCantidad;
	float auxPrecioUnitario;
	char auxTarjetaDeCredito[16];
	char idParametro[5];
	char fechaDiaParametro[3];
	char fechaMesParametro[3];
	char fechaAnioParametro[5];
	char cantidadParametro[3];
	char precioUnitarioParametro[10];
	Venta *pNuevaVenta;

	auxId = 1;
	sprintf(idParametro, "%d", auxId);

	pNuevaVenta = venta_new();

	if (pNuevaVenta != NULL) {

		printf("\n\n-------AGREGANDO VENTA-------\n");

		if (utn_pedirFecha(&auxFechaDia, &auxFechaMes, &auxFechaAnio, 3) == 0
				&& utn_pedirTexto(auxModelo, "Ingrese el modelo: ",
						"ERROR. Modelo invalido", 50, 3) == 0
				&& utn_pedirNumero(&auxCantidad,
						"Ingrese la cantidad (max 10): ",
						"ERROR. Cantidad invalida", 1, 10, 3) == 0
				&& utn_pedirNumeroFlotante(&auxPrecioUnitario,
						"Ingrese el precio unitario: ",
						"ERROR. Precio Invalido.", 1, 99999, 3) == 0
				&& utn_pedirTarjetaDeCredito(auxTarjetaDeCredito, 3) == 0) {
			sprintf(fechaDiaParametro, "%d", auxFechaDia);
			sprintf(fechaMesParametro, "%d", auxFechaMes);
			sprintf(fechaAnioParametro, "%d", auxFechaAnio);
			sprintf(precioUnitarioParametro, "%.2f", auxPrecioUnitario);
			sprintf(cantidadParametro, "%d", auxCantidad);
			pNuevaVenta = venta_newParametros(idParametro, fechaDiaParametro,
					fechaMesParametro, fechaAnioParametro, auxModelo,
					cantidadParametro, precioUnitarioParametro,
					auxTarjetaDeCredito);
			if (pNuevaVenta != NULL) {
				if (ll_add(pArrayListVentas, pNuevaVenta) != 0) {
					pNuevaVenta = NULL;
				}
			}
		}else{
			printf("\nUNO DE LOS DATOS INGRESADOS NO FUE CORRECTO\nEL ALTA NO FUE EXITOSA\n");
			pNuevaVenta=NULL;
		}
	} else {
		printf("\nNO HAY MAS LUGAR PARA NUEVAS VENTAS\n");
	}

	return pNuevaVenta;
}

/// @fn int controller_removerVenta(LinkedList*)
/// @brief Remueve una venta de la LinkedList
/// @param pArrayListVentas LinkedList a modificar
/// @return Retorna 0 si pudo borrar la venta y -1 si no pudo
int controller_removerVenta(LinkedList *pArrayListVentas) {
	int retorno;
	int idElegido;
	int indice;

	retorno = -1;
	indice = -1;

	if (pArrayListVentas != NULL) {
		printf("\n------DAR DE BAJA UNA VENTA------\n");
		if (controller_listarVentas(pArrayListVentas) == 0) {
			utn_pedirNumero(&idElegido,
					"Elija el ID de la venta que quiere dar de baja: ",
					"ERROR. ID invalido.", 1, 1000, 3);

			indice = venta_encontrarPorId(pArrayListVentas, idElegido);

			if (indice >= 0 && ll_remove(pArrayListVentas, indice) == 0) {
				retorno = 0;
			} else {
				printf("\nLA VENTA CON ESE ID NO EXISTE\n");
			}
		} else {
			printf("\nVOLVIENDO AL MENU PRINCIPAL...\n");
		}
	}

	return retorno;
}

/// @fn int controller_editarVenta(LinkedList*)
/// @brief Muestra el menu para modificar una venta dentro de la LinkedList
/// @param pArrayListVentas Es la LinkedList que tiene los datos a modificar
/// @return retorna 0 si ingreso bien al menu y -1 si no pudo
int controller_editarVenta(LinkedList *pArrayListVentas) {
	int retorno;
	int opcion;
	int idElegido;
	int indice;
	Venta *pVenta = NULL;

	retorno = -1;

	if (pArrayListVentas != NULL) {

		controller_listarVentas(pArrayListVentas);
		utn_pedirNumero(&idElegido,
				"Elija el ID de la venta que quiere editar: ",
				"ERROR. ID invalido", 1, 1000, 3);
		indice = venta_encontrarPorId(pArrayListVentas, idElegido);
		if (indice >= 0) {
			pVenta = (Venta*) ll_get(pArrayListVentas, indice);
		} else {
			printf("\nLA VENTA CON ESE ID NO EXISTE\n");
		}

		utn_pedirNumero(&opcion, "\n1 - Fecha"
				"\n2 - Modelo"
				"\n3 - Cantidad"
				"\n4 - Precio unitario"
				"\n5 - Tarjeta de credito"
				"\n6 - Volver"
				"\nQue desea editar?: ", "ERROR. Opcion invalida", 1, 6, 3);

		switch (opcion) {
		case 1:
			if (venta_editarFecha(pVenta) == 0) {
				printf("\nLA FECHA FUE EDITADA CORRECTAMENTE\n");
			}
			break;

		case 2:
			if (venta_editarModelo(pVenta) == 0) {
				printf("\nEL MODELO FUE EDITADO CORRECTAMENTE\n");
			}
			break;

		case 3:
			if (venta_editarCantidad(pVenta) == 0) {
				printf("\nLA CANTIDAD FUE EDITADA CORRECTAMENTE\n");
			}
			break;

		case 4:
			if (venta_editarPrecioUnitario(pVenta) == 0) {
				printf("\nEL PRECIO UNITARIO FUE EDITADO CORRECTAMENTE\n");
			}
			break;

		case 5:
			if (venta_editarTarjetaDeCredito(pVenta) == 0) {
				printf("\nLA TARJETA DE CREDITO FUE EDITADA CORRECTAMENTE\n");
			}
			break;

		case 6:
			printf("\nVOLVIENDO AL MENU PRINCIPAL...\n");
			break;
		}
		retorno = 0;
	}

	return retorno;
}

/// @fn int controller_listarVentas(LinkedList*)
/// @brief Imprime una lista de las ventas guardadas en la LinkedList
/// @param pArrayListVentas LinkedList que tiene los datos a imprimir
/// @return Retorna 0 si la LinkedList es valida y -1 si no lo es
int controller_listarVentas(LinkedList *pArrayListVentas) {
	int retorno;
	Venta *auxVenta = NULL;
	int auxId;
	int auxFechaDia;
	int auxFechaMes;
	int auxFechaAnio;
	char auxModelo[50];
	int auxCantidad;
	float auxPrecioUnitario;
	char auxTarjetaDeCredito[16];

	retorno = -1;

	if (pArrayListVentas != NULL) {
		printf(
				"|===========================================================================================|\n");
		printf(
				"|----------------------------------LISTA DE TODAS LAS VENTAS--------------------------------|\n");
		printf(
				"|-------------------------------------------------------------------------------------------|\n");
		printf("| %-3s | %-10s | %-20s | %s | %s | %s |\n", "ID", "Fecha",
				"Modelo", "Cantidad", "Precio unitario", "Tarjeta de Credito");
		printf(
				"|-------------------------------------------------------------------------------------------|\n");
		for (int i = 0; i < ll_len(pArrayListVentas); i++) {
			auxVenta = ll_get(pArrayListVentas, i);
			if (auxVenta != NULL && venta_getIdVenta(auxVenta, &auxId) == 0
					&& venta_getFechaDiaVenta(auxVenta, &auxFechaDia) == 0
					&& venta_getFechaMesVenta(auxVenta, &auxFechaMes) == 0
					&& venta_getFechaAnioVenta(auxVenta, &auxFechaAnio) == 0
					&& venta_getModeloAuto(auxVenta, auxModelo) == 0
					&& venta_getCantidad(auxVenta, &auxCantidad) == 0
					&& venta_getPrecioUnitario(auxVenta, &auxPrecioUnitario)
							== 0
					&& venta_getTarjetaDeCredito(auxVenta, auxTarjetaDeCredito)
							== 0) {

				printf(
						"| %-3d | %2d/%2d/%-4d | %-20s | %-8d | %-15.2f | %-18s |\n",
						auxId, auxFechaDia, auxFechaMes, auxFechaAnio,
						auxModelo, auxCantidad, auxPrecioUnitario,
						auxTarjetaDeCredito);
			}
		}
		retorno = 0;
	}

	return retorno;
}

/// @fn int controller_generarInformeDeVentas(LinkedList*)
/// @brief Genera los datos que se necesitan para el informe de ventas
/// @param pArrayListVentas LinkedList que tiene los datos a analizar
/// @return Retorna 0 si pudo generar el informe y -1 si no pudo
int controller_generarInformeDeVentas(LinkedList *pArrayListVentas) {
	int retorno;
	int unidadesVendidas;
	int mayorADiezMil;
	int mayorAVeinteMil;
	int contadorCorsa;

	retorno = -1;

	if (pArrayListVentas != NULL) {

		unidadesVendidas = ll_count(pArrayListVentas,
				venta_obtenerUnidadesVendidas);
		mayorADiezMil = ll_count(pArrayListVentas, venta_esMayorADiezMil);
		mayorAVeinteMil = ll_count(pArrayListVentas, venta_esMayorAVeinteMil);
		contadorCorsa = ll_count(pArrayListVentas, venta_esCorsa);
		if (controller_guardarInformeDeVentas(unidadesVendidas, mayorADiezMil,
				mayorAVeinteMil, contadorCorsa) == 0) {
			retorno = 0;
		}

	}
	return retorno;
}

/// @fn int controller_guardarInformeDeVentas(int, int, int, int)
/// @brief Genera el archivo informes.txt
/// @param acumuladorUnidades El total de las unidades vendidas
/// @param mayorADiezMil Cuantos autos salen mas de 10.000
/// @param mayorAVeinteMil Cuantos autos salen mas de 20.000
/// @param contadorModelo Cuantos modelos de Corsa hay
/// @return Retorna 0 si pudo generar el archivo y -1 si no pudo
int controller_guardarInformeDeVentas(int acumuladorUnidades, int mayorADiezMil,
		int mayorAVeinteMil, int contadorModelo) {
	int retorno;
	FILE *pArchivo = NULL;

	retorno = -1;

	if (acumuladorUnidades >= 0 && mayorADiezMil >= 0 && mayorAVeinteMil >= 0
			&& contadorModelo >= 0) {
		pArchivo = fopen("informes.txt", "w");
		if (pArchivo != NULL) {
			fprintf(pArchivo, "%s\n", "********************\n"
					"Informe de ventas\n"
					"********************\n");
			fprintf(pArchivo, "%s: %d\n",
					"- Cantidad de unidades vendidas totales",
					acumuladorUnidades);
			fprintf(pArchivo, "%s: %d\n",
					"- Cantidad de ventas por un monto mayor a $10000",
					mayorADiezMil);
			fprintf(pArchivo, "%s: %d\n",
					"- Cantidad de ventas por un monto mayor a $20000",
					mayorAVeinteMil);
			fprintf(pArchivo, "%s: %d\n", "- Cantidad de Corsa vendidos",
					contadorModelo);
			fprintf(pArchivo, "%s", "********************");
			retorno = 0;
		}
		fclose(pArchivo);
	}

	return retorno;
}

/// @fn int controller_guardarVentasModoTexto(char*, LinkedList*)
/// @brief Guarda los datos de la LinkedList que se pasa por parametro en un archivo de texto
/// @param path Nombre del archivo que queremos guardar
/// @param pArrayListVentas LinkedList que tiene los datos que queremos guardar
/// @return retorna 0 si pudo generar el archivo y -1 si no pudo
int controller_guardarVentasModoTexto(char *path, LinkedList *pArrayListVentas) {
	int retorno;
	FILE *pArchivo = NULL;
	Venta *auxVenta;
	int auxId;
	int auxFechaDia;
	int auxFechaMes;
	int auxFechaAnio;
	char auxModelo[50];
	int auxCantidad;
	float auxPrecioUnitario;
	char auxTarjetaDeCredito[16];

	retorno = -1;

	if (path != NULL && pArrayListVentas != NULL) {
		pArchivo = fopen(path, "w");
		if (pArchivo != NULL) {
			fprintf(pArchivo, "%s,%s,%s,%s,%s,%s\n", "ID_Venta", "Fecha_Venta",
					"Modelo_Auto", "Cantidad", "Precio_Unitario",
					"Tarjeta_De_Credito");
			for (int i = 0; i < ll_len(pArrayListVentas); i++) {
				auxVenta = (Venta*) ll_get(pArrayListVentas, i);
				if (auxVenta != NULL && venta_getIdVenta(auxVenta, &auxId) == 0
						&& venta_getFechaDiaVenta(auxVenta, &auxFechaDia) == 0
						&& venta_getFechaMesVenta(auxVenta, &auxFechaMes) == 0
						&& venta_getFechaAnioVenta(auxVenta, &auxFechaAnio) == 0
						&& venta_getModeloAuto(auxVenta, auxModelo) == 0
						&& venta_getCantidad(auxVenta, &auxCantidad) == 0
						&& venta_getPrecioUnitario(auxVenta, &auxPrecioUnitario)
								== 0
						&& venta_getTarjetaDeCredito(auxVenta,
								auxTarjetaDeCredito) == 0) {
					if (fprintf(pArchivo, "%d,%d/%d/%d,%s,%d,%.2f,%s\n", auxId,
							auxFechaDia, auxFechaMes, auxFechaAnio, auxModelo,
							auxCantidad, auxPrecioUnitario, auxTarjetaDeCredito)
							> 0) {
						retorno = 0;
					} else {
						printf("\nHUBO UN PROBLEMA AL GUARDAR EL ARCHIVO\n");
						break;
					}
				}
			}
		}
	}

	return retorno;
}

/// @fn int controller_guardarVentasModoBinario(char*, LinkedList*)
/// @brief Guarda en un archivo binario los datos de una LinkedList
/// @param path Nombre del archivo
/// @param pArrayListVentas LinkedList con los datos a guardar
/// @return retorna 0 si pudo guardar el archivo y -1 si no pudo
int controller_guardarVentasModoBinario(char *path,
		LinkedList *pArrayListVentas) {
	int retorno;
	FILE *pArchivo = NULL;
	Venta *auxVenta = NULL;
	int retornoFunc;

	retorno = -1;

	if (path != NULL && pArrayListVentas != NULL) {
		pArchivo = fopen(path, "wb");
		if (pArchivo != NULL) {
			for (int i = 0; i < ll_len(pArrayListVentas); i++) {
				auxVenta = ll_get(pArrayListVentas, i);
				if (auxVenta != NULL) {
					retornoFunc = fwrite(auxVenta, sizeof(Venta), 1, pArchivo);
					if (retornoFunc == 1) {
						retorno = 0;
					} else {
						printf("\nHUBO UN PROBLEMA AL ESCRIBIR EL ARCHIVO\n");
						break;
					}
				}
			}
		}
		fclose(pArchivo);
	}

	return retorno;
}

/// @fn int controller_asignarIdUnico(Venta*)
/// @brief Le asigna el ID Unico a una venta recien creada
/// @param pVenta Puntero a la venta
/// @return retorna 0 si pudo asignar el ID y -1 si no pudo
int controller_asignarIdUnico(Venta *pVenta) {
	int retorno;
	int auxId;

	retorno = -1;

	if (pVenta != NULL) {
		if (controller_cargarIdUnicoDesdeTexto("ID_Unico.csv", &auxId) == 0) {
			if (venta_setIdVenta(pVenta, auxId) == 0) {
				auxId++;
				controller_guardarIdUnicoModoTexto("ID_Unico.csv", auxId);
				retorno = 0;
			}
		}
	}

	return retorno;
}

/// @fn int controller_cargarIdUnicoDesdeTexto(char*, int*)
/// @brief Carga el ID Unico desde un archivo de texto
/// @param path Nombre del archivo
/// @param id Puntero a entero que guarda el ID que cargamos desde el archivo
/// @return Retorna 0 si pudo abrir el archivo y -1 si no pudo
int controller_cargarIdUnicoDesdeTexto(char *path, int *id) {
	int retorno;

	retorno = -1;

	FILE *pArchivo;
	int retornoParser;
	int auxId;

	retorno = -1;

	if (path != NULL && id != NULL) {
		pArchivo = fopen(path, "r");
		if (pArchivo != NULL) {
			retornoParser = parser_IdUnicoFromText(pArchivo, &auxId);
			if (retornoParser == 0) {
				*id = auxId;
				retorno = 0;
			}
		} else {
			pArchivo = fopen(path, "w");
			if (pArchivo != NULL) {
				*id = 0;
				printf("\nEL ARCHIVO NO EXISTIA Y FUE CREADO CORRECTAMENTE.");
			}
		}
		fclose(pArchivo);
	}

	return retorno;
}

/// @fn int controller_guardarIdUnicoModoTexto(char*, int)
/// @brief Guarda el ID unico en un archivo de texto
/// @param path Nombre del archivo
/// @param id ID unico a guardar
/// @return Retorna 0 si pudo guardarlo y -1 si no pudo
int controller_guardarIdUnicoModoTexto(char *path, int id) {
	int retorno;
	FILE *pArchivo;
	int retornoEscrito;

	retorno = -1;

	if (path != NULL && id >= 0) {
		pArchivo = fopen(path, "w");
		if (pArchivo != NULL) {
			retornoEscrito = fprintf(pArchivo, "%d", id);
			if (retornoEscrito == 1) {
				retorno = 0;
			}
		}
		fclose(pArchivo);
	}

	return retorno;
}
