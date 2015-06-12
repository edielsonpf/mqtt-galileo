/* main.c
 *
 *  Created on: 08/06/2015
 *      Author: Di Toro
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "mraa.h"

#include "sensores.h"
#include "json.h"
#include "mqtt.h"

int main(int argc, char *argv[])
{
	short int PIN = 2;

	float V;
	char S[80];
	float T;

	strcpy(S,"");

	for(;;){

		V = tensao(PIN);
		strcpy(S,itojson("Tansao",V));
		publish(S,"inatel/iot/galileo/05");
		printf("\n");
		sleep(1);


		T = temperatura(1);
		strcpy(S,itojson("Celcius",T));
		strcat(S,"\n");
		strcat(S,itojson("Fahrenheit",T*9/5+32));
		publish(S,"inatel/iot/galileo/01");
		printf("\n");
		sleep(1);


		strcpy(S,ctojson("LUX",luminosidade(0)));
		publish(S,"inatel/iot/galileo/07");
		printf("\n");
		sleep(1);


	}

	return 0;

}
