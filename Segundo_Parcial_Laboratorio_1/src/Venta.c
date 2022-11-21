/*
 * Venta.c
 *
 *  Created on: 13 nov. 2022
 *      Author: pablo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Venta.h"
#include "LinkedList.h"
#include "inputs.h"

/// @fn Venta venta_new*()
/// @brief Reserva espacio en memoria para un elemento del tipo Venta y setea sus campos en valores default
/// @return Retorna el puntero al elemento Venta creado o NULL si no hay mas espacio en memoria
Venta* venta_new() {
	Venta *pRetorno = NULL;

	pRetorno = (Venta*) malloc(sizeof(Venta));

	if (pRetorno != NULL) {
		venta_setIdVenta(pRetorno, 0);
		venta_setFechaDiaVenta(pRetorno, 1);
		venta_setFechaMesVenta(pRetorno, 1);
		venta_setFechaAnioVenta(pRetorno, 1990);
		venta_setModeloAuto(pRetorno, " ");
		venta_setCantidad(pRetorno, 1);
		venta_setPrecioUnitario(pRetorno, 1);
		venta_setTarjetaDeCredito(pRetorno, "0000000000000000");
	}
	return pRetorno;
}

/// @fn Venta venta_newParametros*(char*, char*, char*, char*, char*, char*, char*, char*)
/// @brief Crea un nuevo elemento de la entidad Venta y setea sus campos con las variables que llegan por parametro
/// @param idStr Cadena de caracteres para setear el campo ID
/// @param fechaDiaStr Cadena de caracteres para setear el campo dia
/// @param fechaMesStr Cadena de caracteres para setear el campo mes
/// @param fechaAnioStr Cadena de caracteres para setear el campo anio
/// @param modeloAutoStr Cadena de caracteres para setear el campo modeloAuto
/// @param cantidadStr Cadena de caracteres para setear el campo cantidad
/// @param precioUnitarioStr Cadena de caracteres para setear el campo precioUnitario
/// @param tarjetaDeCreditoStr Cadena de caracteres para setear el campo tarjetaDeCredito
/// @return Retorna el puntero al elemento de la entidad Venta con los campos seteados o NULL si hubo un error
Venta* venta_newParametros(char *idStr, char *fechaDiaStr, char *fechaMesStr,
		char *fechaAnioStr, char *modeloAutoStr, char *cantidadStr,
		char *precioUnitarioStr, char *tarjetaDeCreditoStr) {
	Venta *pRetorno = venta_new();
	int auxId;
	int auxFechaDia;
	int auxFechaMes;
	int auxFechaAnio;
	int auxCantidad;
	float auxPrecioUnitario;
	int contadorErrores;

	auxId = atoi(idStr);
	auxFechaDia = atoi(fechaDiaStr);
	auxFechaMes = atoi(fechaMesStr);
	auxFechaAnio = atoi(fechaAnioStr);
	auxCantidad = atoi(cantidadStr);
	auxPrecioUnitario = atof(precioUnitarioStr);
	contadorErrores = 0;

	if (pRetorno != NULL) {
		contadorErrores += venta_setIdVenta(pRetorno, auxId);
		contadorErrores += venta_setFechaDiaVenta(pRetorno, auxFechaDia);
		contadorErrores += venta_setFechaMesVenta(pRetorno, auxFechaMes);
		contadorErrores += venta_setFechaAnioVenta(pRetorno, auxFechaAnio);
		contadorErrores += venta_setModeloAuto(pRetorno, modeloAutoStr);
		contadorErrores += venta_setCantidad(pRetorno, auxCantidad);
		contadorErrores += venta_setPrecioUnitario(pRetorno, auxPrecioUnitario);
		contadorErrores += venta_setTarjetaDeCredito(pRetorno,
				tarjetaDeCreditoStr);
		if (contadorErrores != 0) {
			pRetorno = NULL;
			printf("\nHUBO UN ERROR AL CARGAR LOS DATOS\n");
		}
	} else {
		printf("\nNO HAY LUGAR PARA MAS VENTAS\n");
	}
	return pRetorno;
}

/// @fn int venta_setIdVenta(Venta*, int)
/// @brief Setea el campo idVenta en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta a la que se le quiere setear uno de sus campos
/// @param id Dato que se guardara en el campo a setear
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_setIdVenta(Venta *this, int id) {
	int retorno;

	retorno = -1;

	if (this != NULL && id >= 0) {
		this->idVenta = id;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_getIdVenta(Venta*, int*)
/// @brief Obtiene el campo idVenta en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta de la que se le quiere obtener uno de sus campos
/// @param id Puntero a entero donde se guardara el dato obtenido
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_getIdVenta(Venta *this, int *id) {
	int retorno;

	retorno = -1;

	if (this != NULL && id != NULL) {
		*id = this->idVenta;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_setFechaDiaVenta(Venta*, int)
/// @brief Setea el campo dia en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta a la que se le quiere setear uno de sus campos
/// @param fechaDia Dato que se guardara en el campo a setear
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_setFechaDiaVenta(Venta *this, int fechaDia) {
	int retorno;

	retorno = -1;

	if (this != NULL && fechaDia > 0 && fechaDia <= 31) {
		this->fechaVenta.dia = fechaDia;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_getFechaDiaVenta(Venta*, int*)
/// @brief Obtiene el campo dia en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta de la que se le quiere obtener uno de sus campos
/// @param fechaDia Puntero a entero donde se guardara el dato obtenido
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_getFechaDiaVenta(Venta *this, int *fechaDia) {
	int retorno;

	retorno = -1;

	if (this != NULL && this->fechaVenta.dia > 0
			&& this->fechaVenta.dia <= 31) {
		*fechaDia = this->fechaVenta.dia;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_setFechaMesVenta(Venta*, int)
/// @brief Setea el campo mes en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta a la que se le quiere setear uno de sus campos
/// @param fechaMes Dato que se guardara en el campo a setear
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_setFechaMesVenta(Venta *this, int fechaMes) {
	int retorno;

	retorno = -1;

	if (this != NULL && fechaMes > 0 && fechaMes <= 12) {
		this->fechaVenta.mes = fechaMes;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_getFechaMesVenta(Venta*, int*)
/// @brief Obtiene el campo mes en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta de la que se le quiere obtener uno de sus campos
/// @param fechaMes Puntero a entero donde se guardara el dato obtenido
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_getFechaMesVenta(Venta *this, int *fechaMes) {
	int retorno;

	retorno = -1;
	if (this != NULL && this->fechaVenta.mes > 0
			&& this->fechaVenta.mes <= 12) {
		*fechaMes = this->fechaVenta.mes;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_setFechaAnioVenta(Venta*, int)
/// @brief Setea el campo anio en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta a la que se le quiere setear uno de sus campos
/// @param fechaAnio Dato que se guardara en el campo a setear
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_setFechaAnioVenta(Venta *this, int fechaAnio) {
	int retorno;

	retorno = -1;

	if (this != NULL && fechaAnio > 1990 && fechaAnio <= 2023) {
		this->fechaVenta.anio = fechaAnio;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_getFechaAnioVenta(Venta*, int*)
/// @brief Obtiene el campo anio en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta de la que se le quiere obtener uno de sus campos
/// @param fechaAnio Puntero a entero donde se guardara el dato obtenido
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_getFechaAnioVenta(Venta *this, int *fechaAnio) {
	int retorno;

	retorno = -1;

	if (this != NULL && this->fechaVenta.anio > 1990
			&& this->fechaVenta.anio <= 2023) {
		*fechaAnio = this->fechaVenta.anio;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_setModeloAuto(Venta*, char*)
/// @brief Setea el campo modeloAuto en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta a la que se le quiere setear uno de sus campos
/// @param modeloAuto Dato que se guardara en el campo a setear
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_setModeloAuto(Venta *this, char *modeloAuto) {
	int retorno;

	retorno = -1;

	if (this != NULL && modeloAuto != NULL) {
		strcpy(this->modeloAuto, modeloAuto);
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_getModeloAuto(Venta*, char*)
/// @brief Obtiene el campo modeloAuto en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta de la que se le quiere obtener uno de sus campos
/// @param modeloAuto Puntero a char donde se guardara el dato obtenido
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_getModeloAuto(Venta *this, char *modeloAuto) {
	int retorno;

	retorno = -1;

	if (this != NULL && modeloAuto != NULL) {
		strcpy(modeloAuto, this->modeloAuto);
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_setCantidad(Venta*, int)
/// @brief Setea el campo cantidad en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta a la que se le quiere setear uno de sus campos
/// @param cantidad Dato que se guardara en el campo a setear
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_setCantidad(Venta *this, int cantidad) {
	int retorno;

	retorno = -1;

	if (this != NULL && cantidad >= 1) {
		this->cantidad = cantidad;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_getCantidad(Venta*, int*)
/// @brief Obtiene el campo cantidad en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta de la que se le quiere obtener uno de sus campos
/// @param cantidad Puntero a entero donde se guardara el dato obtenido
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_getCantidad(Venta *this, int *cantidad) {
	int retorno;

	retorno = -1;

	if (this != NULL && this->cantidad >= 1) {
		*cantidad = this->cantidad;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_setPrecioUnitario(Venta*, float)
/// @brief Setea el campo precioUnitario en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta a la que se le quiere setear uno de sus campos
/// @param precioUnitario Dato que se guardara en el campo a setear
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_setPrecioUnitario(Venta *this, float precioUnitario) {
	int retorno;

	retorno = -1;

	if (this != NULL && precioUnitario >= 1) {
		this->precioUnitario = precioUnitario;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_getPrecioUnitario(Venta*, float*)
/// @brief Obtiene el campo precioUnitorio en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta de la que se le quiere obtener uno de sus campos
/// @param precioUnitario Puntero a flotante donde se guardara el dato obtenido
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_getPrecioUnitario(Venta *this, float *precioUnitario) {
	int retorno;

	retorno = -1;

	if (this != NULL && this->precioUnitario >= 1) {
		*precioUnitario = this->precioUnitario;
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_setTarjetaDeCredito(Venta*, char*)
/// @brief Setea el campo tarjetaDeCredito en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta a la que se le quiere setear uno de sus campos
/// @param tarjetaDeCredito Dato que se guardara en el campo a setear
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_setTarjetaDeCredito(Venta *this, char *tarjetaDeCredito) {
	int retorno;

	retorno = -1;

	if (this != NULL && strlen(tarjetaDeCredito) == 16) {
		strcpy(this->tarjetaDeCredito, tarjetaDeCredito);
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_getTarjetaDeCredito(Venta*, char*)
/// @brief Obtiene el campo tarjetaDeCredito en una entidad del tipo Venta
/// @param this Puntero a la entidad Venta de la que se le quiere obtener uno de sus campos
/// @param tarjetaDeCredito Puntero a char donde se guardara el dato obtenido
/// @return Retorna 0 si pudo setear el campo correctamente o -1 si no pudo
int venta_getTarjetaDeCredito(Venta *this, char *tarjetaDeCredito) {
	int retorno;

	retorno = -1;

	if (this != NULL && strlen(this->tarjetaDeCredito) == 16) {
		strcpy(tarjetaDeCredito, this->tarjetaDeCredito);
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_encontrarPorId(LinkedList*, int)
/// @brief Encuentra el indice de la LinkedList donde esta guardado un elemento segun su campo idVenta
/// @param pArrayListVenta Puntero a una entidad Venta
/// @param id idVenta que se quiere encontrar dentro de la entidad
/// @return Retorna el indice si lo encontro o -1 si no lo hizo o hubo un error
int venta_encontrarPorId(LinkedList *pArrayListVenta, int id) {
	Venta *auxVenta = NULL;
	int retorno;
	int auxId;

	retorno = -1;

	if (pArrayListVenta != NULL && id > 0) {
		for (int i = 0; i < ll_len(pArrayListVenta); i++) {
			auxVenta = ll_get(pArrayListVenta, i);
			venta_getIdVenta(auxVenta, &auxId);
			if (auxId == id) {
				retorno = i;
			}
		}
	}
	return retorno;
}

/// @fn int venta_editarFecha(Venta*)
/// @brief Le pide al usuario que ingrese una nueva fecha
/// @param pVenta Puntero a una entidad del tipo Venta
/// @return Retorna 0 si pudo obtener una nueva fecha y -1 si no pudo o hubo un error
int venta_editarFecha(Venta *pVenta) {
	int retorno;
	int auxFechaDia;
	int auxFechaMes;
	int auxFechaAnio;

	retorno = -1;

	if (pVenta != NULL
			&& utn_pedirFecha(&auxFechaDia, &auxFechaMes, &auxFechaAnio, 3) == 0
			&& venta_setFechaDiaVenta(pVenta, auxFechaDia) == 0
			&& venta_setFechaMesVenta(pVenta, auxFechaMes) == 0
			&& venta_setFechaAnioVenta(pVenta, auxFechaAnio) == 0) {
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_editarModelo(Venta*)
/// @brief Le pide al usuario que ingrese un nuevo modeloAuto
/// @param pVenta Puntero a una entidad del tipo Venta
/// @return Retorna 0 si pudo obtener un nuevo modeloAuto y -1 si no pudo o hubo un error
int venta_editarModelo(Venta *pVenta) {
	int retorno;
	char auxModelo[50];

	retorno = -1;

	if (pVenta != NULL
			&& utn_pedirTexto(auxModelo, "Ingrese el modelo: ",
					"ERROR. Modelo invalido", 50, 3) == 0
			&& venta_setModeloAuto(pVenta, auxModelo) == 0) {
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_editarCantidad(Venta*)
/// @brief Le pide al usuario que ingrese una nueva cantidad
/// @param pVenta Puntero a una entidad del tipo Venta
/// @return Retorna 0 si pudo obtener una nueva cantidad y -1 si no pudo o hubo un error
int venta_editarCantidad(Venta *pVenta) {
	int retorno;
	int auxCantidad;

	retorno = -1;

	if (pVenta != NULL
			&& utn_pedirNumero(&auxCantidad, "Ingrese la cantidad (max 10): ",
					"ERROR. Cantidad invalida", 1, 10, 3) == 0
			&& venta_setCantidad(pVenta, auxCantidad) == 0) {
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_editarPrecioUnitario(Venta*)
/// @brief Le pide al usuario que ingrese un nuevo precioUnitario
/// @param pVenta Puntero a una entidad del tipo Venta
/// @return Retorna 0 si pudo obtener un nuevo precioUnitario y -1 si no pudo o hubo un error
int venta_editarPrecioUnitario(Venta *pVenta) {
	int retorno;
	float auxPrecioUnitario;

	retorno = -1;

	if (pVenta != NULL
			&& utn_pedirNumeroFlotante(&auxPrecioUnitario,
					"Ingrese el precio unitario: ", "ERROR. Precio Invalido.",
					1, 99999, 3) == 0
			&& venta_setPrecioUnitario(pVenta, auxPrecioUnitario) == 0) {
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_editarTarjetaDeCredito(Venta*)
/// @brief Le pide al usuario que ingrese una nueva tarjetaDeCredito
/// @param pVenta Puntero a una entidad del tipo Venta
/// @return Retorna 0 si pudo obtener una nueva tarjetaDeCredito y -1 si no pudo o hubo un error
int venta_editarTarjetaDeCredito(Venta *pVenta) {
	int retorno;
	char auxTarjetaDeCredito[16];

	retorno = -1;

	if (pVenta != NULL && utn_pedirTarjetaDeCredito(auxTarjetaDeCredito, 3) == 0
			&& venta_setTarjetaDeCredito(pVenta, auxTarjetaDeCredito) == 0) {
		retorno = 0;
	}
	return retorno;
}

/// @fn int venta_calcularUnidadesVendidas(void*)
/// @brief Obtiene el campo cantidad y lo retorna por retorno
/// @param this Puntero a una entidad del tipo Venta
/// @return Retorna el valor del campo cantidad
int venta_obtenerUnidadesVendidas(void *this) {
	Venta *auxVenta;
	int auxUnidades;

	if (this != NULL) {
		auxVenta = (Venta*) this;
		venta_getCantidad(auxVenta, &auxUnidades);
	}
	return auxUnidades;
}

/// @fn int venta_esMayorADiezMil(void*)
/// @brief Indica si el precio final de una venta es mayor a 10.000
/// @param this Puntero a una entidad del tipo Venta
/// @return Retorna 1 si la venta es mayor a 10.000 y 0 si no lo es
int venta_esMayorADiezMil(void *this) {
	int retorno;
	float auxPrecioUnitario;
	int auxCantidad;
	float resultado;
	Venta *pVenta;

	retorno = 0;

	if (this != NULL) {
		pVenta = (Venta*) this;
		if (venta_getPrecioUnitario(pVenta, &auxPrecioUnitario) == 0
				&& venta_getCantidad(pVenta, &auxCantidad) == 0) {

			resultado = (float) auxCantidad * auxPrecioUnitario;
			if (resultado >= 10000) {
				retorno = 1;
			}
		}
	}
	return retorno;
}

/// @fn int venta_esMayorAVeinteMil(void*)
/// @brief Indica si el precio final de una venta es mayor a 20.000
/// @param this Puntero a una entidad del tipo Venta
/// @return Retorna 1 si la venta es mayor a 20.000 y 0 si no lo es
int venta_esMayorAVeinteMil(void *this) {
	int retorno;
	float auxPrecioUnitario;
	int auxCantidad;
	float resultado;
	Venta *pVenta;

	retorno = 0;

	if (this != NULL) {
		pVenta = (Venta*) this;
		if (venta_getPrecioUnitario(pVenta, &auxPrecioUnitario) == 0
				&& venta_getCantidad(pVenta, &auxCantidad) == 0) {

			resultado = (float) auxCantidad * auxPrecioUnitario;
			if (resultado >= 20000) {
				retorno = 1;
			}
		}
	}
	return retorno;
}

/// @fn int venta_esCorsa(void*)
/// @brief Indica si el modeloAuto de una venta es Corsa
/// @param this Puntero a una entidad del tipo Venta
/// @return Retorna el valor del campo cantidad si el modelo es Corsa y 0 si no lo es
int venta_esCorsa(void *this) {
	int retorno;
	char auxModelo[50];
	Venta *pVenta;
	int auxCantidad;

	retorno = 0;

	if (this != NULL) {
		pVenta = (Venta*) this;
		if (venta_getModeloAuto(pVenta, auxModelo) == 0) {
			if (strcmp(auxModelo, "Corsa") == 0
					&& venta_getCantidad(pVenta, &auxCantidad) == 0) {
				retorno = auxCantidad;
			}
		}
	}
	return retorno;
}
