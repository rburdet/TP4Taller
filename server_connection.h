#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "common_connection.h"
#include "common_converter.h"
#include "server_lock.h"
#include "common_mutex.h"
#include "common_thread.h"

class ServerConnection : public Connection,public Thread {
	private:
		struct sockaddr_in connected_addr;
		Mutex mutex;
		
	public:
		void run(){
			Lock l(this->mutex);
			if (connect()!=-1){
				std::cout<<Converter::convert("PUERTO ",port,". Abierto.")<<std::endl;
				if (communicate() != -1);
				std::cout<<Converter::convert("PUERTO ",port,". Conexión aceptada.")<<std::endl;
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
				return -1;
			}
			if (listen(sd, BACKLOG) == -1) {
				std::cerr<< "error on listening"<<std::endl;
				return -1;
			}
			return 0;
		}

		int welcome(int new_fd,socklen_t sin_size){

			std::string MSG=Converter::convert("PUERTO ",port," Aceptado. Recibiendo datos...");
			Msg* toSend = createMsg(MSG);
			if (sendAll(new_fd,toSend)==-1)
				return -1;
			return 0;
		}

		int communicate(){
			int new_fd;
			socklen_t sin_size;
			sin_size = sizeof(struct sockaddr_in);
			if ((new_fd = accept(sd, (struct sockaddr *)&connected_addr,&sin_size)) == -1) {
			//TODO:
			//Primero le da la bienvenida: Puerto XXXX aceptado. Recibiendo datos
			//Recibe un mensaje del cliente con los datos.
			//Mensaje de verificacion con cantidad recibida 
			//Se cierra y se reinicia el ciclo
			//if (connect(sd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
			//	std::cerr<< " Error conectando " << std::endl;
			//}
			
				perror("accept");
				exit(1);
				return -1;
				//continue;
			}
			//welcome(new_fd, sin_size);
			//uint32_t size;
			//if (recv(new_fd,&size,sizeof(size),0) == -1){
			//	perror("todo mal reciviendo");
			//	exit(1);
			//}
			//int correctSize=ntohs(size);
			//char* buf = (char*)malloc(correctSize);;
			//if (recv(new_fd,buf,correctSize,0) == -1){
			//	perror("TODO MAL RECIBIENDO");
			//	exit(1);
			//}
			//printf("server mensaje: %s\n",buf);
			//printf("server Received: %u\n",correctSize);

			//close(new_fd);
			return 0;
		}
};

#endif 
