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
	client.startconnection();
	client.sendFile("client1.in");
	return 0;
}
