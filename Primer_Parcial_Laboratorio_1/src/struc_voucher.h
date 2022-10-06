/*
 * struc_voucher.h
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#ifndef STRUC_VOUCHER_H_
#define STRUC_VOUCHER_H_

typedef struct{
	int dia;
	int mes;
	int anio;
}fecha;

typedef struct{
	int idVoucher;
	int viajeId;
	char descripcion[64];
	float precioViaje;
	fecha;
	int isEmpty;
}voucher;

void inicializarVoucher(voucher voucherX[], int len);

#endif /* STRUC_VOUCHER_H_ */
