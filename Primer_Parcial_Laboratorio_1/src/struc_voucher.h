/*
 * struc_voucher.h
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#ifndef STRUC_VOUCHER_H_
#define STRUC_VOUCHER_H_

#include "struc_viaje.h"
#include "struc_tipo.h"

typedef struct {
	int dia;
	int mes;
	int anio;
} fecha;

typedef struct {
	int idVoucher;
	int viajeId;
	char descripcion[64];
	float precioViaje;
	fecha fechaVoucher;
	int isEmpty;
} voucher;

void inicializarVoucher(voucher arrayVouchers[], int longArrayVouchers);
int buscarVoucherVacio(voucher arrayVouchers[], int longArrayVouchers);
int asignarId(voucher arrayVouchers[], int longArrayVouchers);
int altaVoucher(voucher arrayVouchers[], int longArrayVouchers,
		viaje arrayViajes[], int longArrayViajes, tipo arrayTipos[]);
void asignarDescripcionVoucher(voucher arrayVouchers[], viaje arrayViajes[],
		tipo arrayTipos[], int longArrayViajes, int id, int indice);
void listarVoucher(voucher arrayVouchers[], int longArrayVouchers);
void listarVoucherPorFecha(voucher arrayVouchers[], int longArrayVouchers);
void importeTotalVoucherPorViaje(voucher arrayVouchers[], int longArrayVouchers,
		viaje arrayViajes[], int longArrayViajes);
void importeTotalVoucherPorTipoYFecha(voucher arrayVouchers[],
		int longArrayVouchers, tipo arrayTipos[], int longArrayTipos);
void listarVoucherPorTipo(voucher arrayVouchers[], int longArrayVouchers,
		int tipoSeleccionado);

#endif /* STRUC_VOUCHER_H_ */
