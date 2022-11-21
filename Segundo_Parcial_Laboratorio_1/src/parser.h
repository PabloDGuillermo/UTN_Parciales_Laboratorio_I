/*
 * parser.h
 *
 *  Created on: 13 nov. 2022
 *      Author: pablo
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_VentasFromText(FILE* pFile , LinkedList* pArrayListVentas);
int parser_VentasFromBinary(FILE* pFile , LinkedList* pArrayListVentas);
int parser_IdUnicoFromText(FILE *pFile, int* id);

#endif /* PARSER_H_ */
