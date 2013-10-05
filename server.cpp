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
#define MYPORT 3490
 // Puerto al que conectarán los usuarios
#define BACKLOG 10
 // Cuántas conexiones pendientes se mantienen en cola

int main(void){
	int sd, new_fd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr; 
	socklen_t sin_size;
//	struct sigaction sa;
	int yes=1;

	//Se crea el socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	//Se llena el struct sockadd_in que dsp se usa para dsp castearlo a sockaddr y usarlo en bind y listen
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(my_addr.sin_zero), '\0', 8);

	//cierra puertos que quedan abiertos
	if (setsockopt(sd,SOL_SOCKET,SO_REUSEADDR, &yes,sizeof(int)) ==-1){
		perror("setsockopt");
		exit(1);
	}

	//Hace el bind 2
	if (bind(sd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
		perror("bind");
		exit(1);
		}
	if (listen(sd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	//while(1) { // main accept() loop
		{
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sd, (struct sockaddr *)&their_addr,&sin_size)) == -1) {
			perror("accept");
			exit(1);
			//continue;
		}
		//Cuando se conecta tengo que mandar el mensaje de bienvenida 
		printf("server: got connection from %s\n",inet_ntoa(their_addr.sin_addr));
		if (!fork()) { // Este es el proceso hijo
			close(sd); // El hijo no necesita este descriptor
		Msg* toSend = createMsg("HOLISSSasdasdS");
		if (sendAll(new_fd,toSend)==-1);
		//if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
			perror("send");
		close(new_fd);
		exit(0);
		}
		close(new_fd); // El proceso padre no lo necesita
	}
	return 0;
}
