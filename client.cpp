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
#include "client_connection.h"
#include "common_parser.h"
#define MYPORT 3490
 
int main(int argc, char* argv[]){
	std::string IP;
	int port = parseIP_PORT(argv[1],IP);
	ClientConnection client(IP,port);
	std::string fileName="";
	if (argc==3)
		fileName = std::string(argv[2]);
	client.startconnection(fileName);
	//client.sendFile(fileName);
	return 0;
}
