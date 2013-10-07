#include "server_connection.h"

void ServerConnection::run(){
if (connect()!=-1){
	uint32_t dataReceived;
	Lock l(this->mutex);
	if ((dataReceived = communicate()) != 0);
	std::cout<<Converter::convert("PUERTO ",port,". Conexión aceptada.")<<std::endl;
	const std::string& beg = Converter::convert("PUERTO ",port,". Recibidos ");
	std::cout<<Converter::convert(beg,dataReceived, " bytes.")<<std::endl;
	std::cout<<"PUERTO "<<port<< ". Conexión cerrada." << std::endl;
	}
}

int ServerConnection::connect(){
	int yes=1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
		exit(1);
	}			
	if (bind(sd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
		std::cout<<Converter::convert("PUERTO ",port,". Error.")<<std::endl;
		return -1;
	}
	if (listen(sd, BACKLOG) == -1) {
		return -1;
	}
	std::cout<<Converter::convert("PUERTO ",port,". Abierto.")<<std::endl;
	return 0;
}

uint32_t ServerConnection::communicate(){
	uint32_t dataReceived;
	int new_fd;
	socklen_t sin_size;
	sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = accept(sd, (struct sockaddr *)&connected_addr,&sin_size)) 
			== -1){
		std::cout << "ERROR EN ACCEPT " << std::endl;	
		exit(1);
		return 0;
	}
	if ((dataReceived = getData(new_fd)) == 0)
		return 0;
	//Mando mensaje para confirmar datos, no tengo que verificar 
	//la integridad de los datos. El sendAll manda todo
	std::string MSG=Converter::convert("",dataReceived);
	Msg toSend(MSG);
	toSend.sendAll(new_fd);
	return dataReceived;
}

int ServerConnection::welcome(int new_fd,socklen_t sin_size){
	std::string MSG=Converter::convert("PUERTO ",
		port," Aceptado. Recibiendo datos...");
	Msg toSend(MSG);
	if (toSend.sendAll(new_fd)==-1)
		return -1;
	return 0;
}

