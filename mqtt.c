/*
 *  mqtt.c
 *
 *  Created on: 06/06/2015
 *      Author: Di Toro
 */

#define HOST "iot.eclipse.org"
#define PORT 1883
#define KEEPALIVE 5 //Tempo em segundos


#include "mqtt\MQTTConnect.h"
#include "mqtt\MQTTFormat.h"
#include "mqtt\MQTTPacket.h"
#include "mqtt\MQTTPublish.h"
#include "mqtt\MQTTSubscribe.h"
#include "mqtt\MQTTUnsubscribe.h"
#include "mqtt\StackTrace.h"
#include "mqtt\transport.h"
#include "mqtt.h"


int publish(char* payload, char* topic ){
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer; //MQTTPacket_connectData parece estar recebendo info abaixo por programacao orientada ao objeto

    //*** CONFIGURACOES INICIAIS ***//
 	  int rc = 0;
	  char buf[200];
	  int buflen = sizeof(buf);
	  int mysock = 0;  // TCP-IP - NUNCA MUDAR! POR NEM UM MOTIVO!!!!!!!
      MQTTString topicString = MQTTString_initializer;


	//*** CONFIGURACAO DO BROKER ***//
	  char *host = HOST;
	  int port = PORT;
	  topicString.cstring = topic;//"inatel/iot/galileo/01";


	//*** MENSAGEM A SER PUBLICADA ***//
	  int payloadlen = strlen(payload);
	  int len = 0;


	mysock = transport_open(host,port);
	if(mysock < 0)
		return mysock;

	printf("Sending to hostname %s port %d\n", host, port); //Mostra endereco e porta usados


	//CONFIG MQTTPacket_connectData
	data.keepAliveInterval = KEEPALIVE;
	data.clientID.cstring  = "";
	data.username.cstring  = "";
	data.password.cstring  = "";
	data.cleansession      = 1;  //the Client and Server MUST discard any previous Session and start a new one. This Session lasts as long as the Network Connection. State data associated with this Session MUST NOT be reused in any subsequent Session
	data.MQTTVersion       = 4;


	len = MQTTSerialize_connect((unsigned char *)buf, buflen, &data);
	len += MQTTSerialize_publish((unsigned char *)(buf + len), buflen - len, 0, 0, 0, 0, topicString, (unsigned char *)payload, payloadlen);
	len += MQTTSerialize_disconnect((unsigned char *)(buf + len), buflen - len);

	rc = transport_sendPacketBuffer(mysock, buf, len);
	if (rc == len)
		printf("Successfully published\n");
	else
		printf("Publish failed\n");

	exit:
	transport_close(mysock);

	return 0;
}
