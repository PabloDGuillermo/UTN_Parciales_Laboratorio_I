/*
 * Venta.h
 *
 *  Created on: 13 nov. 2022
 *      Author: pablo
 */

#ifndef VENTA_H_
#define VENTA_H_

#include "LinkedList.h"

typedef struct {
	int dia;
	int mes;
	int anio;
} Fecha;

typedef struct {
	int idVenta;
	Fecha fechaVenta;
	char modeloAuto[50];
	int cantidad;
	float precioUnitario;
	char tarjetaDeCredito[16];
} Venta;

Venta* venta_new();
Venta* venta_newParametros(char *idStr, char *fechaDiaStr, char *fechaMesStr,
		char *fechaAnioStr, char *modeloAutoStr, char *cantidadStr,
		char *precioUnitarioStr, char *tarjetaDeCreditoStr);

void venta_delete(Venta *this);

int venta_setIdVenta(Venta *this, int id);
int venta_getIdVenta(Venta *this, int *id);

int venta_setFechaDiaVenta(Venta *this, int fechaDia);
int venta_getFechaDiaVenta(Venta *this, int *fechaDia);

int venta_setFechaMesVenta(Venta *this, int fechaMes);
int venta_getFechaMesVenta(Venta *this, int *fechaMes);

int venta_setFechaAnioVenta(Venta *this, int fechaAnio);
int venta_getFechaAnioVenta(Venta *this, int *fechaAnio);

int venta_setModeloAuto(Venta *this, char *modeloAuto);
int venta_getModeloAuto(Venta *this, char *modeloAuto);

int venta_setCantidad(Venta *this, int cantidad);
int venta_getCantidad(Venta *this, int *cantidad);

int venta_setPrecioUnitario(Venta *this, float precioUnitario);
int venta_getPrecioUnitario(Venta *this, float *precioUnitario);

int venta_setTarjetaDeCredito(Venta *this, char *tarjetaDeCredito);
int venta_getTarjetaDeCredito(Venta *this, char *tarjetaDeCredito);

int venta_encontrarPorId(LinkedList *pArrayListVenta, int id);
int venta_editarFecha(Venta *pVenta);
int venta_editarModelo(Venta *pVenta);
int venta_editarCantidad(Venta *pVenta);
int venta_editarPrecioUnitario(Venta *pVenta);
int venta_editarTarjetaDeCredito(Venta *pVenta);
int venta_obtenerUnidadesVendidas(void *this);
int venta_esMayorADiezMil(void *this);
int venta_esMayorAVeinteMil(void *this);
int venta_esCorsa(void *this);

#endif /* VENTA_H_ */
