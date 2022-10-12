/*
 * struc_voucher.c
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#include <stdio.h>
#include "struc_voucher.h"
#include "inputs.h"
#include <string.h>

#define VACIO 0
#define LLENO 1

/// @fn void inicializarVoucher(voucher[], int)
/// @brief Inicializa el campo isEmpty en VACIO en un array de la estructura voucher
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array
void inicializarVoucher(voucher arrayVouchers[], int longArrayVouchers) {
	if (arrayVouchers != NULL && longArrayVouchers > 0) {
		for (int i = 0; i < longArrayVouchers; i++) {
			arrayVouchers[i].isEmpty = VACIO;
		}
	}
}

/// @fn int buscarVoucherVacio(voucher[], int)
/// @brief Recorre un array de la estructura voucher y busca el primer índice con el campo isEmpty en VACIO
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array
/// @return Retorna el índice que tenga el campo isEmpty en VACIO o -1 si no hay más lugar en el array
int buscarVoucherVacio(voucher arrayVouchers[], int longArrayVouchers) {

	int retorno = -1;

	if (arrayVouchers != NULL && longArrayVouchers > 0) {
		for (int i = 0; i < longArrayVouchers; i++) {
			if (arrayVouchers[i].isEmpty == VACIO) {
				arrayVouchers[i].isEmpty = LLENO;
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/// @fn int asignarId(voucher[], int)
/// @brief Incrementa de a uno el ID de un array de la estructura voucher
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array
/// @return Retorna el ID incrementado en uno cada vez que se llama a la función
int asignarId(voucher arrayVouchers[], int longArrayVouchers) {
	static int retorno = 20000;

	if (arrayVouchers != NULL && longArrayVouchers > 0) {
		retorno += 1;
	}

	return retorno;
}

/// @fn int altaVoucher(voucher[], int, viaje[], int, tipo[])
/// @brief Imprime por pantalla el menú para dar de alta un array de la estructura voucher y, si los datos
/// ingresados son correctos, escribe cada dato en los campos correspondientes
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array de la estructura voucher
/// @param arrayViajes Recibe un array de la estructura viaje para imprimir por pantalla sus datos
/// y así poder asignarle el ID de un viaje al array de la estructura voucher
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
/// @param arrayTipos Recibe un array de la estructura tipo para poder asirnar la descripción en el campo correspondiente
/// de la estructura voucher
/// @return Retorna 0 si se pudieron escribir los datos dentro del array de la estructura voucher y
/// -1 si no se pudo
int altaVoucher(voucher arrayVouchers[], int longArrayVouchers,
		viaje arrayViajes[], int longArrayViajes, tipo arrayTipos[]) {
	int retorno;
	voucher buffer;
	int indice;
	int error;
	char opcion;
	int id;

	retorno = -1;

	indice = buscarVoucherVacio(arrayVouchers, longArrayVouchers);

	if (indice >= 0) {
		do {
			buffer.idVoucher = asignarId(arrayVouchers, longArrayVouchers);
			listarViajes(arrayViajes, longArrayViajes);
			error = utn_getNumero(&id, "Ingrese el ID del viaje: ",
					"ERROR. ID Invalido", 100, 10000, 3);
			if (buscarViajePorId(arrayViajes, longArrayViajes, id) == -1) {
				printf("El viaje con ese ID no existe");
				error = -1;

			} else {
				buffer.viajeId = id;
				error = utn_getNumeroFlotante(&buffer.precioViaje,
						"Ingrese el precio del voucher: ",
						"ERROR. No ingreso un precio correcto.", 0, 1000000, 3);
				if (error == 0) {
					utn_getFecha(&buffer.fechaVoucher.dia,
							&buffer.fechaVoucher.mes, &buffer.fechaVoucher.anio,
							3);
				}
			}
			if (error == 0) {
				arrayVouchers[indice].idVoucher = buffer.idVoucher;
				asignarDescripcionVoucher(arrayVouchers, arrayViajes,
						arrayTipos, longArrayViajes, id, indice);
				arrayVouchers[indice].viajeId = buffer.viajeId;
				arrayVouchers[indice].precioViaje = buffer.precioViaje;
				arrayVouchers[indice].fechaVoucher.dia =
						buffer.fechaVoucher.dia;
				arrayVouchers[indice].fechaVoucher.mes =
						buffer.fechaVoucher.mes;
				arrayVouchers[indice].fechaVoucher.anio =
						buffer.fechaVoucher.anio;
				arrayVouchers[indice].isEmpty = LLENO;
				retorno = 0;

			} else {
				utn_getChar(&opcion,
						"\nAlguno de los datos fue erroneo. Quiere reintentar (s/n)",
						"ERROR. No ingresó una opcion valida", 3);
			}
		} while (opcion == 's');
	}
	return retorno;
}

/// @fn void asignarDescripcionVoucher(voucher[], viaje[], tipo[], int, int, int)
/// @brief Asigna, en el campo correspondiente dentro del array de la estructura viaje una descripción
///  del tipo de viaje según el ID del tipo que está guardado en un array de la estructura viaje
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param arrayViajes Recibe un array de la estructura viaje para saber qué ID de tipo tiene asignado
/// @param arrayTipos Recibe un array de la estructura tipo para saber cuál debe ser la descripción
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
/// @param id Recibe el ID de la estructura viaje para poder saber el índice en el cual buscar los datos necesarios
/// @param indice Recibe el índice del array de la estructura voucher
void asignarDescripcionVoucher(voucher arrayVouchers[], viaje arrayViajes[],
		tipo arrayTipos[], int longArrayViajes, int id, int indice) {
	int indiceViaje;

	indiceViaje = buscarViajePorId(arrayViajes, longArrayViajes, id);

	if (arrayViajes[indiceViaje].tipoId == 1000) {
		strcpy(arrayVouchers[indice].descripcion, arrayTipos[0].descripcion);
	} else if (arrayViajes[indiceViaje].tipoId == 1001) {
		strcpy(arrayVouchers[indice].descripcion, arrayTipos[1].descripcion);
	} else {
		strcpy(arrayVouchers[indice].descripcion, arrayTipos[2].descripcion);
	}
}

/// @fn void listarVoucher(voucher[], int)
/// @brief Imprime por pantalla una lista de los voucher con el campo isEmpty en LLENO hasta el momento
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array
void listarVoucher(voucher arrayVouchers[], int longArrayVouchers) {
	if (arrayVouchers != NULL && longArrayVouchers > 0) {
		printf("\n");
		printf("------------------------------------------------------");
		printf("\n\t-----LISTA DE TODOS LOS VOUCHER-----\n");
		printf("------------------------------------------------------");
		printf("\n%-15s | %-15s | %-30s | %-20s | %s\n", "ID del voucher",
				"ID del viaje", "Descripcion del voucher", "Precio del viaje",
				"fecha");
		for (int i = 0; i < longArrayVouchers; i++) {
			if (arrayVouchers[i].isEmpty == LLENO) {
				printf("%-15d | %-15d | %-30s | %-20.2f |%d/%d/%d\n",
						arrayVouchers[i].idVoucher, arrayVouchers[i].viajeId,
						arrayVouchers[i].descripcion,
						arrayVouchers[i].precioViaje,
						arrayVouchers[i].fechaVoucher.dia,
						arrayVouchers[i].fechaVoucher.mes,
						arrayVouchers[i].fechaVoucher.anio);
			}
		}
	}
}

/// @fn void listarVoucherPorFecha(voucher[], int)
/// @brief Imprime por pantalla una lista de los voucher dados de alta filtrando por una fecha determinada por el usuario
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array
void listarVoucherPorFecha(voucher arrayVouchers[], int longArrayVouchers) {
	int anio;
	int mes;
	int dia;
	int hayConEsaFecha;

	hayConEsaFecha = -1;

	if (arrayVouchers != NULL && longArrayVouchers > 0) {
		printf("\nIngrese la fecha: \n");
		utn_getFecha(&dia, &mes, &anio, 3);

		for (int i = 0; i < longArrayVouchers; i++) {
			if (arrayVouchers[i].fechaVoucher.anio == anio
					&& arrayVouchers[i].fechaVoucher.mes == mes
					&& arrayVouchers[i].fechaVoucher.dia == dia) {
				hayConEsaFecha = 0;
			}
		}
		if (hayConEsaFecha == 0) {
			printf("\n");
			printf("-------------------------------------------------------");
			printf("\n-----LISTA DE TODOS LOS VOUCHER DEL DIA %d/%d/%d-----\n",
					dia, mes, anio);
			printf("-------------------------------------------------------");
			printf("\n%-15s | %-15s | %-30s | %-20s\n", "ID del voucher",
					"ID del viaje", "Descripcion del voucher",
					"Precio del viaje");
			for (int i = 0; i < longArrayVouchers; i++) {
				if (arrayVouchers[i].fechaVoucher.anio == anio
						&& arrayVouchers[i].fechaVoucher.mes == mes
						&& arrayVouchers[i].fechaVoucher.dia == dia) {
					if (arrayVouchers[i].isEmpty == LLENO) {
						printf("%-15d | %-15d | %-30s | %-20.2f",
								arrayVouchers[i].idVoucher,
								arrayVouchers[i].viajeId,
								arrayVouchers[i].descripcion,
								arrayVouchers[i].precioViaje);
					}
					printf("\n");
				}
			}
		} else {
			printf("\nNo hay vouchers cargados con la fecha seleccionada\n");
		}
	}
}

/// @fn void importeTotalVoucherPorViaje(voucher[], int, viaje[], int)
/// @brief Realiza el cálculo del importe total de un array de la estructura voucher filtrado por
/// el ID de un viaje determinado por el usuario
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array de la estructura voucher
/// @param arrayViajes Recibe un array de la estructura viaje para poder listar los viajes dados de alta hasta el momento
/// @param longArrayViajes Recibe la longitud del array de la estructura viaje
void importeTotalVoucherPorViaje(voucher arrayVouchers[], int longArrayVouchers,
		viaje arrayViajes[], int longArrayViajes) {
	float importeTotal;
	int error;
	int idViajeSeleccionado;

	importeTotal = 0;

	if (arrayVouchers != NULL && longArrayVouchers > 0 && arrayViajes != NULL
			&& longArrayViajes > 0) {
		listarViajes(arrayViajes, longArrayViajes);
		error = utn_getNumero(&idViajeSeleccionado,
				"Ingrese el ID del viaje asociado a los voucher: ",
				"ERROR. ID invalido.", 100, 110, 3);
		if (error == 0
				&& buscarViajePorId(arrayViajes, longArrayViajes,
						idViajeSeleccionado) >= 0) {
			for (int i = 0; i < longArrayVouchers; i++) {
				if (arrayVouchers[i].isEmpty == LLENO
						&& arrayVouchers[i].viajeId == idViajeSeleccionado) {
					importeTotal += arrayVouchers[i].precioViaje;
				}
			}
			printf(
					"El importe total de los voucher asociados a ese viaje es: %.2f\n\n",
					importeTotal);
		} else {
			printf("El viaje con ese ID no existe\n");
		}
	}
}

/// @fn void importeTotalVoucherPorTipoYFecha(voucher[], int, tipo[], int)
/// @brief Calcula el importe total de un array de la estructura voucher filtrado por su descripción y una
/// fecha determinada por el usuario
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array de la estructura voucher
/// @param arrayTipos Recibe un array de la estructura tipo para imprimir por pantalla sus datos
/// @param longArrayTipos Recibe la longitud del array de la estructura tipo
void importeTotalVoucherPorTipoYFecha(voucher arrayVouchers[],
		int longArrayVouchers, tipo arrayTipos[], int longArrayTipos) {
	float importeTotal;
	int error;
	int tipoSeleccionado;
	int indice;
	int anio;
	int mes;
	int dia;
	int hayConEsaFecha;
	int hayConEseTipo;

	importeTotal = 0;

	hayConEsaFecha = -1;
	hayConEseTipo = -1;

	if (arrayVouchers != NULL && longArrayVouchers > 0 && arrayTipos != NULL
			&& longArrayTipos > 0) {
		listarTipos(arrayTipos, longArrayTipos);
		error = utn_getNumero(&tipoSeleccionado,
				"Ingrese el ID del tipo asociado a los voucher: ",
				"ERROR. Tipo invalido.", 1000, 1002, 3);
		if (error == 0) {
			for (int i = 0; i < longArrayVouchers; i++) {
				indice = buscarTipoSegunDescripcion(
						arrayVouchers[i].descripcion);
				if (arrayVouchers[i].isEmpty == LLENO
						&& arrayTipos[indice].idTipo == tipoSeleccionado) {
					hayConEseTipo = 0;
				}
			}
			if (hayConEseTipo == 0) {
				listarVoucherPorTipo(arrayVouchers, longArrayVouchers,
						tipoSeleccionado);
				printf("\nIngrese la fecha: \n");
				utn_getFecha(&dia, &mes, &anio, 3);

				for (int i = 0; i < longArrayVouchers; i++) {
					if (arrayVouchers[i].isEmpty == LLENO
							&& arrayVouchers[i].fechaVoucher.anio == anio
							&& arrayVouchers[i].fechaVoucher.mes == mes
							&& arrayVouchers[i].fechaVoucher.dia == dia) {
						hayConEsaFecha = 0;
					}
				}

				if (hayConEsaFecha == 0) {
					for (int i = 0; i < longArrayVouchers; i++) {
						indice = buscarTipoSegunDescripcion(
								arrayVouchers[i].descripcion);
						if (arrayVouchers[i].isEmpty == LLENO
								&& arrayTipos[indice].idTipo
										== tipoSeleccionado) {
							importeTotal += arrayVouchers[i].precioViaje;
						}
					}
					printf(
							"El importe total de los voucher asociados a ese tipo y fecha es: %.2f\n\n",
							importeTotal);
				} else {
					printf(
							"No hay vouchers asociados a ese tipo en esa fecha.\n\n");
				}

			} else {
				printf("No hay vouchers asociados a ese tipo.\n\n");
			}
		} else {
			printf("\nVOLVIENDO AL MENU DE INFORMES\n");
		}
	}
}

/// @fn void listarVoucherPorTipo(voucher[], int, int)
/// @brief Imprime por pantalla una lista de un array de la estructura voucher filtrado por un tipo seleccionado por el usuario
/// @param arrayVouchers Recibe un array de la estructura voucher
/// @param longArrayVouchers Recibe la longitud del array
/// @param tipoSeleccionado Recibe el ID de tipo seleccionado por el usuario
void listarVoucherPorTipo(voucher arrayVouchers[], int longArrayVouchers,
		int tipoSeleccionado) {
	char descripcionTipo[10];

	if (tipoSeleccionado == 1000) {
		strcpy(descripcionTipo, "AEREO");
	} else if (tipoSeleccionado == 1001) {
		strcpy(descripcionTipo, "TERRESTRE");
	} else {
		strcpy(descripcionTipo, "MARITIMO");
	}
	if (arrayVouchers != NULL && longArrayVouchers > 0) {
		printf("\n");
		printf("----------------------------------------------------");
		printf("\n-----LISTA DE TODOS LOS VOUCHER DEL TIPO %s-----\n",
				descripcionTipo);
		printf("----------------------------------------------------");
		printf("\n%-15s | %-15s | %-20s | %s\n", "ID del voucher",
				"ID del viaje", "Precio del viaje", "fecha");
		for (int i = 0; i < longArrayVouchers; i++) {
			if (arrayVouchers[i].isEmpty == LLENO
					&& strcmp(arrayVouchers[i].descripcion, descripcionTipo)
							== 0) {
				printf("%-15d | %-15d | %-20.2f |%d/%d/%d\n",
						arrayVouchers[i].idVoucher, arrayVouchers[i].viajeId,
						arrayVouchers[i].precioViaje,
						arrayVouchers[i].fechaVoucher.dia,
						arrayVouchers[i].fechaVoucher.mes,
						arrayVouchers[i].fechaVoucher.anio);
			}
		}
	}
}
