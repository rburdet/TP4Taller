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
#include "common_thread.h"
#include "common_list.h"
#include "common_parser.h"
#include <iostream>

#define MYPORT 3490
 // Puerto al que conectarán los usuarios
 // Cuántas conexiones pendientes se mantienen en cola

int main(int argc, char* argv[]){
	if (argc!=2)
		return 0;
	List portList;
	parsePorts(&portList, argv[1]);
	Node* aux;
	for ( aux = portList.getFirst() ; aux != NULL ; aux = aux->getNext() ){
		ServerConnection serv("127.0.0.1",aux->getData());
		serv.start();
		std::cout << aux->getData() << std::endl;
	}
	//serv.connect();
	//serv.communicate();

	while (std::cin.get() != 'q');
	//printf("server: got connection from %s\n",inet_ntoa(their_addr.sin_addr));
	return 0;
}
