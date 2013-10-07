#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "common_connection.h"
#include "common_converter.h"
#include "server_lock.h"
#include "common_mutex.h"
#include "common_thread.h"

class ServerConnection : public Thread , public Connection {
	private:
		struct sockaddr_in connected_addr;
		Mutex mutex;
		char* buf;
		
	public:
		void run(){
			if (connect()!=-1){
				uint32_t dataReceived;
				Lock l(this->mutex);
				if ((dataReceived = communicate()) != 0);
				std::cout<<Converter::convert("PUERTO ",port,". Conexión aceptada.")<<std::endl;
				const std::string& beg = Converter::convert("PUERTO ",port,". Recibidos ");
				std::cout<<Converter::convert(beg,dataReceived, " bytes.")<<std::endl;
			}
		}

		ServerConnection(const std::string& ip, int port) : Connection(ip, port){}
		int connect(){
			int yes=1;
			if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
			    perror("setsockopt");
			    exit(1);
			}			
			if (bind(sd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
				std::cerr<<"error on binding"<<std::endl;
				std::cout<<Converter::convert("PUERTO ",port,". Error.")<<std::endl;
				return -1;
			}
			if (listen(sd, BACKLOG) == -1) {
				//std::cout<<Converter::convert("PUERTO ",port,". Error.")<<std::endl;
				std::cerr<< "error on listening"<<std::endl;
				return -1;
			}
			std::cout<<Converter::convert("PUERTO ",port,". Abierto.")<<std::endl;
			return 0;
		}

		int welcome(int new_fd,socklen_t sin_size){
			std::string MSG=Converter::convert("PUERTO ",port," Aceptado. Recibiendo datos...");
			Msg* toSend = createMsg(MSG);
			if (sendAll(new_fd,toSend)==-1)
				return -1;
			return 0;
		}

		//Devuelve 0 en caso de error, en caso contrario devuelve la cnatidad
		//de bytes recibidos
		uint32_t communicate(){
			uint32_t dataReceived;
			int new_fd;
			socklen_t sin_size;
			sin_size = sizeof(struct sockaddr_in);
			if ((new_fd = accept(sd, (struct sockaddr *)&connected_addr,&sin_size)) == -1) {
			//TODO:
			//Mensaje de verificacion con cantidad recibida 
			//Se cierra y se reinicia el ciclo
			//if (connect(sd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
			//	std::cerr<< " Error conectando " << std::endl;
			//}
				std::cout << "ERROR EN ACCEPT " << std::endl;	
				perror("accept");
				exit(1);
				return 0;
			}
			if ((dataReceived = getData(new_fd)) == 0)
				return 0;
			return dataReceived;
		}

		//Devuelve 0 en caso de error, en caso contrario devuelve la cnatidad
		//de bytes recibidos
		uint32_t getData(int new_fd){
			uint32_t size;
			if (recv(new_fd,&size,sizeof(size),0) == -1){
				perror("todo mal reciviendo");
				return 0;
			}
			int correctSize = htons(size);
			buf = (char*)malloc(correctSize);
			if (recv(new_fd,buf,correctSize,0) == -1){
				perror("llego mal el mensaje");
				free (buf);
				return 0;
			}
			free (buf);
			return ntohs(size);
		}
		~ServerConnection(){
			shutdown(this->sd,SHUT_RDWR);
			std::cout<<"MATE UN SERVIDOR " << std::endl;
		}
};

#endif 
