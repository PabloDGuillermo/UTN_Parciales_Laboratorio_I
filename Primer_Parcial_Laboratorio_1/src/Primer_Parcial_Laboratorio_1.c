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
#include "menues.h"

#define LONGITUD_ARRAY_VIAJE 50
#define LONGITUD_ARRAY_TIPO 3
#define LONGITUD_ARRAY_VOUCHER 1000

int main(void) {
	setbuf(stdout, NULL);

	tipo tipos[LONGITUD_ARRAY_TIPO];
	viaje viajes[LONGITUD_ARRAY_VIAJE];
	voucher vouchers[LONGITUD_ARRAY_VOUCHER];

	inicializarTipo(tipos, LONGITUD_ARRAY_TIPO);
	inicializarViaje(viajes, LONGITUD_ARRAY_VIAJE);
	inicializarVoucher(vouchers, LONGITUD_ARRAY_VOUCHER);

	mostrarMenuPrincipal(viajes, tipos, vouchers, LONGITUD_ARRAY_VIAJE,
			LONGITUD_ARRAY_TIPO, LONGITUD_ARRAY_VOUCHER);

	return EXIT_SUCCESS;
}
