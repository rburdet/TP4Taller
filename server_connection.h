#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "common_connection.h"
#include "common_converter.h"

class ServerConnection : public Connection {
	private:
		struct sockaddr_in connected_addr;

	public:
		ServerConnection(const std::string& ip, int port) : Connection(ip, port){}
		int connect(){
			if (bind(sd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
				std::cerr<<"error on binding"<<std::endl;
			}
			if (listen(sd, BACKLOG) == -1) {
				std::cerr<< "error on listening"<<std::endl;
				return -1;
			}
			//int yes=1;
			//if (setsockopt(sd,SOL_SOCKET,SO_REUSEADDR, &yes,sizeof(int)) ==-1){
			//	perror("setsockopt");
			//	exit(1);
			//}
			return 0;
		}

		int welcome(int new_fd,socklen_t sin_size){
			std::string MSG="PUERTO ";
			MSG.append(Converter::convert(port));
			MSG.append(" Aceptado. Recibiendo datos...");
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
				//continue;
			}
			welcome(new_fd, sin_size);
			uint32_t size;
			if (recv(new_fd,&size,sizeof(size),0) == -1){
				perror("todo mal reciviendo");
				exit(1);
			}
			int correctSize=ntohs(size);
			char* buf = (char*)malloc(correctSize);;
			if (recv(new_fd,buf,correctSize,0) == -1){
				perror("TODO MAL RECIBIENDO");
				exit(1);
			}
			printf("server mensaje: %s\n",buf);
			printf("server Received: %u\n",correctSize);

			close(new_fd);
			return 0;
		}
};

#endif 
