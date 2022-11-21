/*
 * LinkedList.c
 *
 *  Created on: 13 nov. 2022
 *      Author: pablo
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

static Node* getNode(LinkedList *this, int nodeIndex);
static int addNode(LinkedList *this, int nodeIndex, void *pElement);

/// @fn LinkedList ll_newLinkedList*(void)
/// @brief Reserva espacio en memoria para una nueva LinkedList
/// @return Retorna un puntero a una LinkedList vacía o NULL si no hay mas lugar en memoria
LinkedList* ll_newLinkedList(void) {
	LinkedList *this = (LinkedList*) malloc(sizeof(LinkedList*));
	if (this != NULL) {
		this->pFirstNode = NULL;
		this->size = 0;
	}
	return this;
}

/// @fn int ll_len(LinkedList*)
/// @brief Se utiliza esta función para conocer la longitud de una LinkedList
/// @param this Recibe un puntero a la LinkedList de la que se quiere saber la longitud
/// @return Retorna el contenido del campo size o -1 si tuvo un error
int ll_len(LinkedList *this) {
	int retorno = -1;
	if (this != NULL && this->size >= 0) {
		retorno = this->size;
	}
	return retorno;
}

/// @fn Node getNode*(LinkedList*, int)
/// @brief Busca el nodo de una LinkedList segun el numero de indice que llega por parametro
/// @param this Puntero a la LinkedList de la que se quiere obtener un nodo en particular
/// @param nodeIndex Indice del nodo que se quiere obtener
/// @return Retorna un puntero a Node si pudo encontrarlo y NULL si no pudo hacerlo
static Node* getNode(LinkedList *this, int nodeIndex) {
	Node *auxNode = NULL;

	if (this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this)) {
		auxNode = this->pFirstNode;
		for (int i = 0; i < nodeIndex; i++) {
			auxNode = auxNode->pNextNode;
		}
	}
	return auxNode;
}

/// @fn int addNode(LinkedList*, int, void*)
/// @brief Añade un nodo, con su elemento correspondiente, en una LinkedList en un indice determinado
/// @param this Puntero a la LinkedList en la que se agregara el nodo
/// @param nodeIndex Indice en donde se agregara el nodo
/// @param pElement puntero al elemento que se quiere guardar en el nuevo nodo
/// @return Retorna 0 si pudo agregarlo y -1 si no pudo
static int addNode(LinkedList *this, int nodeIndex, void *pElement) {

	int retorno = -1;

	Node *auxNode = (Node*) malloc(sizeof(Node*));

	Node *auxPrevNode = NULL;

	if (auxNode != NULL && this != NULL && nodeIndex >= 0 && pElement != NULL
			&& nodeIndex <= ll_len(this)) {
		auxNode->pElement = pElement;

		if (nodeIndex == 0) {

			auxNode->pNextNode = this->pFirstNode;
			this->pFirstNode = auxNode;
			this->size++;
			retorno = 0;
		} else {
			auxPrevNode = getNode(this, nodeIndex - 1);

			if (auxPrevNode != NULL) {
				auxNode->pNextNode = auxPrevNode->pNextNode;
				auxPrevNode->pNextNode = auxNode;
				this->size++;
				retorno = 0;
			}
		}
	}
	return retorno;
}

/// @fn int ll_add(LinkedList*, void*)
/// @brief Añade un elemento dentro de un nodo en el ultimo lugar de una LinkedList
/// @param this Puntero a una LinkedList
/// @param pElement Puntero al elemento que se quiere agregar
/// @return Retorna 0 si pudo agregarlo y -1 si no pudo
int ll_add(LinkedList *this, void *pElement) {

	int retorno = -1;

	if (this != NULL && pElement != NULL) {
		if (addNode(this, ll_len(this), pElement) == 0) {
			retorno = 0;
		}
	}
	return retorno;
}

/// @fn void ll_get*(LinkedList*, int)
/// @brief Se utiliza para obtener un puntero a un elemento que esta guardado dentro de un nodo de una LinkedList
/// @param this Puntero a una LinkedList
/// @param index Indice del nodo que contiene el elemento que se quiere obtener
/// @return Retorna un puntero a void que sera del tipo del elemento que se quiere obtener
void* ll_get(LinkedList *this, int index) {
	Node *auxNode = NULL;
	void *pRetorno = NULL;

	if (this != NULL && index >= 0 && index < ll_len(this)) {

		auxNode = getNode(this, index);
		if (auxNode != NULL) {
			pRetorno = auxNode->pElement;
		}
	}
	return pRetorno;
}

/// @fn int ll_set(LinkedList*, int, void*)
/// @brief Agrega o modifica un puntero a un elemento en un nodo de una LinkedList en un indice determinado
/// @param this Puntero a una LinkedList
/// @param index Indice del nodo
/// @param pElement Puntero al elemento que se quiere agregar
/// @return Retorna 0 si pudo agregarlo o modificarlo o -1 si no pudo
int ll_set(LinkedList *this, int index, void *pElement) {
	int retorno = -1;
	Node *auxNode = NULL;

	if (this != NULL && pElement != NULL && index >= 0
			&& index < ll_len(this)) {

		auxNode = getNode(this, index);
		auxNode->pElement = pElement;
		retorno = 0;
	}
	return retorno;
}

/// @fn int ll_remove(LinkedList*, int)
/// @brief Remueve un nodo seleccionado de una LinkedList
/// @param this Puntero a una LinkedList
/// @param index Indice del nodo a remover
/// @return Retorna 0 si pudo removerlo y -1 si no pudo hacerlo
int ll_remove(LinkedList *this, int index) {
	int retorno = -1;
	Node *auxNode = NULL;
	Node *auxPrevNode = NULL;

	retorno = -1;

	if (this != NULL && index >= 0 && index < ll_len(this)) {

		auxNode = getNode(this, index);

		if (index == 0) {

			this->pFirstNode = auxNode->pNextNode;
			this->size--;

		} else {

			auxPrevNode = getNode(this, index - 1);
			auxPrevNode->pNextNode = auxNode->pNextNode;
			this->size--;

		}
		free(auxNode);
		retorno = 0;
	}

	return retorno;
}

/// @fn int ll_clear(LinkedList*)
/// @brief Remueve todos los nodos de una LinkedList, dejandola vacia
/// @param this Puntero a una LinkedList
/// @return Retorna 0 si pudo vaciar la LinkedList y -1 si no pudo
int ll_clear(LinkedList *this) {
	int retorno = -1;
	int longitudLinkedList = ll_len(this);
	if (this != NULL && longitudLinkedList > 0) {
		for (int i = 0; i < longitudLinkedList; i++) {
			ll_remove(this, 0);
		}
		retorno = 0;
	}
	return retorno;
}

/// @fn int ll_deleteLinkedList(LinkedList*)
/// @brief Elimina la reserva de memoria de una LinkedList
/// @param this Puntero a una LinkedList
/// @return Retorna 0 si pudo eliminarla o -1 si no pudo
int ll_deleteLinkedList(LinkedList *this) {
	int retorno = -1;
	if (this != NULL && ll_clear(this) == 0) {
		free(this);
		retorno = 0;
	}
	return retorno;
}

/// @fn int ll_indexOf(LinkedList*, void*)
/// @brief Obtiene el indice en donde se encuentra un elemento determinado dentro de una LinkedList
/// @param this Puntero a una LinkedList
/// @param pElement Puntero al elemento del que se quiere saber el indice dentro de la LinkedList
/// @return Retorna el indice encontrado o -1 si no pudo encontrar el elemento dentro de la LinkedList
int ll_indexOf(LinkedList *this, void *pElement) {
	int retorno = -1;
	int longitudLinkedlist = ll_len(this);
	Node *auxNode;
	if (this != NULL && pElement != NULL && longitudLinkedlist > 0) {
		for (int i = 0; i < longitudLinkedlist; i++) {
			auxNode = getNode(this, i);
			if (auxNode != NULL && auxNode->pElement == pElement) {
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/// @fn int ll_isEmpty(LinkedList*)
/// @brief Se utiliza para saber si una LinkedList esta vacia
/// @param this Puntero a una LinkedList
/// @return Retorna 0 si no esta vacia, 1 si esta vacia o -1 si hubo un error
int ll_isEmpty(LinkedList *this) {
	int retorno = -1;
	if (this != NULL) {
		if (ll_len(this) > 0) {
			retorno = 0;
		} else {
			retorno = 1;
		}
	}
	return retorno;
}

/// @fn int ll_push(LinkedList*, int, void*)
/// @brief Añade un nodo con su respectivo elemento en un indice determinado dentro de una LinkedList
/// @param this Puntero a una LinkedList
/// @param index Indice donde se quiere añadir el nodo
/// @param pElement Puntero al elemento que tendra el nodo
/// @return Retorna 0 si pudo agregarlo y -1 si no pudo
int ll_push(LinkedList *this, int index, void *pElement) {
	int retorno = -1;
	if (this != NULL && index >= 0 && index <= ll_len(this) && pElement != NULL) {
		if (addNode(this, index, pElement) == 0) {
			retorno = 0;
		}
	}
	return retorno;
}

/// @fn void ll_pop*(LinkedList*, int)
/// @brief Elimina un nodo determinado dentro de una LinkedList, pero retorna el puntero al elemento que tenia ese nodo para no perderlo
/// @param this Puntero a una LinkedList
/// @param index Inidice del nodo a eliminar
/// @return Retorna el puntero al elemento que tenia el nodo eliminado o NULL si no pudo realizar la eliminacion
void* ll_pop(LinkedList *this, int index) {
	void *retorno = NULL;
	void *auxPElement;
	if (this != NULL && index >= 0 && index < ll_len(this)) {
		auxPElement = ll_get(this, index);
		if (auxPElement != NULL) {
			if (ll_remove(this, index) == -1) {
				retorno = auxPElement;
			}
		}
	}
	return retorno;
}

/// @fn int ll_contains(LinkedList*, void*)
/// @brief Se utiliza para saber si una LinkedList contiene un elemento determinado
/// @param this Puntero a una LinkedList
/// @param pElement Puntero al elemento que se quiere buscar dentro de la LinkedList
/// @return Retorna 0 si el elemento esta en la LinkedList, 1 si no lo esta y -1 si hubo un error
int ll_contains(LinkedList *this, void *pElement) {
	int retorno = -1;   //null
	if (this != NULL && pElement != NULL) {
		if (ll_indexOf(this, pElement) != -1) {
			retorno = 0;   //si contiene
		} else {
			retorno = 1;   //si no contiene
		}
	}
	return retorno;
}

/// @fn int ll_containsAll(LinkedList*, LinkedList*)
/// @brief Se utiliza para saber si los elementos de una LinkedList estan dentro de otra LinkedList
/// @param this Puntero a una LinkedList
/// @param this2 Puntero a una LinkedList
/// @return Retorna 0 si los contiene, 1 si no los contiene y -1 si hubo un error
int ll_containsAll(LinkedList *this, LinkedList *this2) {
	int retorno = -1;
	int len;
	if (this != NULL && this2 != NULL) {
		len = ll_len(this2);
		if (len == 0) {
			retorno = 1;
		} else {
			for (int i = 0; i < len; i++) {
				if (ll_contains(this, ll_get(this2, i)) == 0) {
					retorno = 1;
					break;
				} else {
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/// @fn LinkedList ll_subList*(LinkedList*, int, int)
/// @brief Genera una nueva LinkedList con los nodos de otra LinkedList dentro de un rango de indices determinado
/// @param this Puntero a una LinkedList
/// @param from Inidice desde el que se van a copiar los nodos
/// @param to Indice hasta el que se van a copiar los nodos
/// @return Retorna el puntero a una nueva LinkedList o NULL si hubo un error
LinkedList* ll_subList(LinkedList *this, int from, int to) {
	LinkedList *subList = NULL;
	void *auxPElement;

	if (this != NULL && to > from && to <= ll_len(this) && from >= 0
			&& from < ll_len(this)) {
		subList = ll_newLinkedList();
		if (subList != NULL) {
			for (int i = from; i < to; i++) {
				auxPElement = ll_get(this, i);
				if (auxPElement != NULL) {
					ll_add(subList, auxPElement);

				}
			}
		}
	}
	return subList;
}

/// @fn LinkedList ll_clone*(LinkedList*)
/// @brief Copia una LinkedList
/// @param this Puntero a la LinkedList a copiar
/// @return Retorna un puntero a una nueva LinkedList o NULL si hubo un error
LinkedList* ll_clone(LinkedList *this) {
	LinkedList *cloneList = NULL;
	if (this != NULL) {
		cloneList = ll_subList(this, 0, ll_len(this));
	}
	return cloneList;
}

/// @fn int ll_sort(LinkedList*, int(*)(void*, void*), int)
/// @brief Ordena una LinkedList dependiendo de la funcion criterio y el orden que se pasa por parametro
/// @param this Puntero a la LinkedList a ordenar
/// @param pFunc Puntero a funcion criterio
/// @param order Si el orden es 0 se ordenara de abajo hacia arriba y si es 1 se ordenara de arriba hacia abajo
/// @return Retrona 0 si pudo ordenar y -1 si hubo un error
int ll_sort(LinkedList *this, int (*pFunc)(void*, void*), int order) {
	int retorno = -1;
	int estaOrdenado;
	int len;
	void *auxElement = NULL;
	void *auxElementDos = NULL;
	int retornoPFunc;

	if (this != NULL && pFunc != NULL && (order == 0 || order == 1)) {

		len = ll_len(this);

		do {
			estaOrdenado = 1;
			len--;
			for (int i = 0; i < len; i++) {

				auxElement = ll_get(this, i);
				auxElementDos = ll_get(this, i + 1);
				retornoPFunc = pFunc(auxElement, auxElementDos);

				if ((retornoPFunc > 0 && order == 1)
						|| (retornoPFunc < 0 && order == 0)) {
					ll_set(this, i, auxElementDos);
					ll_set(this, i + 1, auxElement);
					estaOrdenado = 0;
				}
			}
		} while (estaOrdenado == 0);
		retorno = 0;
	}
	return retorno;
}

/// @fn int ll_count(LinkedList*, int(void*))
/// @brief Cuenta la cantidad de elementos que tiene una LinkedList dependiendo de la funcion criterio que se paso por parametro
/// @param this Puntero a una LinkedList
/// @param pFunc Puntero a la funcion criterio
/// @return Retorna el numero de elementos que encontro dentro de la LinkedList, siempre mayor o igual a 0
int ll_count(LinkedList *this, int (pFunc)(void *element)) {
	int acumulador = 0;
	int i;
	void *aux;
	int longitud;
	if (this != NULL) {
		longitud = ll_len(this);
		for (i = 0; i < longitud; i++) {
			aux = (void*) ll_get(this, i);
			acumulador += pFunc(aux);
		}
	}
	return acumulador;
}

/// @fn LinkedList ll_filter*(LinkedList*, int(void*))
/// @brief Crea una nueva LinkedList con los elementos filtrados segun la funcion critero que se pasa por parametro
/// @param this Puntero a una LinkedList
/// @param fn Puntero a la funcion criterio
/// @return Retorna el puntero a una nueva LinkedList o NULL si no pudo crearla
LinkedList* ll_filter(LinkedList *this, int (fn)(void *element)) {
	LinkedList *filterList = NULL;
	int lenList;
	void *auxElement;

	if (this != NULL && fn != NULL) {
		filterList = ll_newLinkedList();
		lenList = ll_len(this);
		if (filterList != NULL && lenList > 0) {
			for (int i = 0; i < lenList; i++) {
				auxElement = ll_get(this, i);

				if (auxElement != NULL && fn(auxElement) == 0) {
					ll_add(filterList, auxElement);
				}
			}
		}
	}
	return filterList;
}
