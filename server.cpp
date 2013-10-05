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
#include "common_com.h"
#include "server_connection.h"
#define MYPORT 3490
 // Puerto al que conectarán los usuarios
 // Cuántas conexiones pendientes se mantienen en cola

int main(void){
	struct sockaddr_in their_addr; 
	ServerConnection serv("127.0.0.1",MYPORT);
	serv.connect();
	serv.communicate();
	printf("server: got connection from %s\n",inet_ntoa(their_addr.sin_addr));
	return 0;
}
