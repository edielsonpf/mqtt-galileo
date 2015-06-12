/*
 * json.c
 *
 *  Created on: 09/06/2015
 *      Author: Di Toro
 */

#include <stdio.h>
#include <string.h>
#include "json.h"

	/*       TODO
	 *  1 - Aprender com o Samuel, como permitir a passagem de multiplos parametros para a mesma função
	 *  2 - Implemnetar esse tipo de passagem.
	 */

char* itojson(char measure[20], double value){

	char srtValue[20];
	strcpy(srtValue,"");
	char msg[80];
	strcpy(msg,"");

	sprintf(srtValue,"%.4lf",value);
	strcpy(msg,"\"");
	strcat(msg,measure);
	strcat(msg,"\": ");
	strcat(msg,srtValue);

	return msg;
}

char* ctojson(char measure[20], char srtValue[20]){

	char msg[80];
	strcpy(msg,"");

	strcpy(msg,"\"");
	strcat(msg,measure);
	strcat(msg,"\": ");
	strcat(msg,srtValue);

	return msg;
}
