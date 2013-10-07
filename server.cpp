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
	List<> portList;
	parsePorts(&portList, argv[1]);
	List<ServerConnection*> threadList;
	Node<>* aux;
	for ( aux = portList.getFirst() ; aux != NULL ; aux = aux->getNext() ){
		ServerConnection* serv = new ServerConnection("127.0.0.1",aux->getData());
		Node<ServerConnection*>* aux2 = new Node<ServerConnection*>(serv);
		threadList.addNode(aux2);
	}
	Node<ServerConnection*>* aux2;
	for ( aux2 = threadList.getFirst() ; aux2 != NULL ; aux2 = aux2->getNext() ){
		(aux2->getData())->start();
	}
	while (std::cin.get() != 'q');

	for ( aux2 = threadList.getFirst() ; aux2 != NULL ; aux2 = aux2->getNext() ){
		delete (aux2->getData());
	}
	return 0;
}
