/*
 * Controller.h
 *
 *  Created on: 13 nov. 2022
 *      Author: pablo
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Venta.h"

int controller_cargarVentasDesdeTexto(char* path , LinkedList* pArrayListVentas);
int controller_cargarVentasDesdeBinario(char* path , LinkedList* pArrayListVentas);
Venta* controller_agregarVenta(LinkedList* pArrayListVentas);
int controller_editarVenta(LinkedList* pArrayListVentas);
int controller_removerVenta(LinkedList* pArrayListVentas);
int controller_listarVentas(LinkedList* pArrayListVentas);
int controller_generarInformeDeVentas(LinkedList* pArrayListVentas);
int controller_guardarInformeDeVentas(int acumuladorUnidades, int mayorADiezMil,
		int mayorAVeinteMil, int contadorModelo) ;
int controller_guardarVentasModoTexto(char* path , LinkedList* pArrayListVentas);
int controller_guardarVentasModoBinario(char* path , LinkedList* pArrayListVentas);

int controller_asignarIdUnico(Venta *pVenta);
int controller_cargarIdUnicoDesdeTexto(char* path, int* id);
int controller_guardarIdUnicoModoTexto(char* path, int id);

#endif /* CONTROLLER_H_ */
