/*
 * struc_voucher.c
 *
 *  Created on: 2 oct. 2022
 *      Author: pablo
 */

#include <stdio.h>
#include "struc_voucher.h"

#define VACIO 0
#define LLENO 1

void inicializarVoucher(voucher voucherX[], int len){
	if(voucherX!=NULL && len>0){
		for(int i=0;i<len;i++){
			voucherX[i].isEmpty=VACIO;
		}
	}
}
