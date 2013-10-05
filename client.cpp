#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include "common_com.h"
#include <stdint.h>
#include "common_com.h"
#include "common_converter.h"
#define MYPORT 3490
 
int main(int argc, char* argv[]){
	int sd;
	uint32_t size;
	struct sockaddr_in my_addr;
	if ((sd=socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket forro");
		exit(1);
	}
	//Msg* aMsg = createMsg(NULL);
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(my_addr.sin_zero),0,8);
	if (connect(sd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
		perror("problemas conectado");
		exit(1);
	}else{//Me pude conectar
		std::cout << "[SERVIDOR] PUERTO " << MYPORT << " Aceptado. Recibiendo datos..." << std::endl;
	}
	if (recv(sd,&size,sizeof(size),0) == -1){
		perror("todo mal reciviendo");
		exit(1);
	}
	int correctSize=ntohs(size);
	char* buf = (char*)malloc(correctSize);;
	if (recv(sd,buf,correctSize,0) == -1){
		perror("TODO MAL RECIBIENDO");
		exit(1);
	}
	printf("mensaje: %s\n",buf);
	printf("Received: %u\n",correctSize);
	std::cout << "buffer: " << std::string(buf) << std::endl;
	std::string MSG="PUERTO ";
	MSG.append(Converter::convert(MYPORT));
	MSG.append(" Aceptado. Recibiendo datos...");
	Msg* toSend = createMsg(MSG);
	if (sendAll(sd,toSend)==-1)
		return -1;

	close (sd);
return 0;
}
