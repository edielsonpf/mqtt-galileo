/*
 *  sensores.c
 *
 *  Created on: 06/06/2015
 *      Author: Di Toro
 *
 *
 *  Last update: 09/06/2015
 */

#include "sensores.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "mqtt.h"
#include "mraa.h"


float tensao(short int pin)
{
	mraa_aio_context adc_pin;
	uint16_t adc_value;
	adc_pin = mraa_aio_init(pin);
	if (adc_pin == NULL) {
		printf("DEU MERCA COM A GPIO!");
		return -1; //ERROR CODE
	}

	adc_value = mraa_aio_read(adc_pin);
	fprintf(stdout, "ADC A%d read %x - %d\n", pin, adc_value, adc_value);

	mraa_aio_close(adc_pin);
	return (adc_value/1023.0*5);
}

char* luminosidade(short int pin)
{
	char txt[5];
	mraa_aio_context adc_pin;
	uint16_t adc_value;
	adc_pin = mraa_aio_init(pin);
	if (adc_pin == NULL) {
		printf("DEU MERCA COM A GPIO!");
		return "-1"; //ERROR CODE
	}

	adc_value = mraa_aio_read(adc_pin);
	fprintf(stdout, "ADC A%d read %x - %d\n", pin, adc_value, adc_value);

	//Todos os valores são tabelados
	//   FONTE: http://www.seeedstudio.com/wiki/Grove_-_Starter_Kit_Plus#12._Grove_.E2.80.93_Temperature_Sensor

	if(adc_value >= 900)
		strcpy(txt,">100");
	else if(adc_value>=800)
		strcpy(txt,"~80");
	else if(adc_value>=700)
		strcpy(txt,"~35");
	else if(adc_value>=600)
		strcpy(txt,"~15");
	else if(adc_value>=500)
		strcpy(txt,"~10");
	else if(adc_value>=400)
		strcpy(txt,"~6");
	else if(adc_value>=300)
		strcpy(txt,"~3");
	else if(adc_value>=200)
		strcpy(txt,"~1");
	else
		strcpy(txt,">1");

	mraa_aio_close(adc_pin);
	return txt;
}


float temperatura(short int pin){

	char msg[60];
	char srtValue[20];

	float celsius;
	mraa_aio_context adc_pin;
	uint16_t adc_value;
	adc_pin = mraa_aio_init(pin); //gpio_apin
	if (adc_pin == NULL) {
		printf("CORRE QUE DEU MERCA COM A GPIO!\n Hehehehehehe");
		return -1;//ERROR CODE
	}

	adc_value = mraa_aio_read(adc_pin);
	fprintf(stdout, "ADC A%d read %x - %d\n", pin, adc_value, adc_value);

	/*******************************************
	 *   milivolts = (adc_value/1023.0)*5000   *
	 *   celsius = milivolts / 100             *
	 *   fahrenheit = celsius * 9/5 + 32       *
	 *******************************************/

	celsius = (adc_value/1023.0)*50;

	mraa_aio_close(adc_pin);
	return celsius;
}
