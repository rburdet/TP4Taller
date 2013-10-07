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
		
	public:
		ServerConnection(const std::string& ip, int port) : Connection(ip, port){};
		void run();
		int connect();
		int welcome(int new_fd,socklen_t sin_size);
		//	std::string MSG=Converter::convert("PUERTO ",port," Aceptado. Recibiendo datos...");
		//	Msg toSend(MSG);
		//	if (toSend.sendAll(new_fd)==-1)
		//		return -1;
		//	return 0;

		//Devuelve 0 en caso de error, en caso contrario devuelve la cnatidad
		//de bytes recibidos
		uint32_t communicate();
		//uint32_t getData(int new_fd){
		//	uint32_t size;
		//	if (recv(new_fd,&size,sizeof(size),0) == -1){
		//		perror("todo mal reciviendo");
		//		return 0;
		//	}
		//	int correctSize = htons(size);
		//	buf = (char*)malloc(correctSize);
		//	if (recv(new_fd,buf,correctSize,0) == -1){
		//		perror("llego mal el mensaje");
		//		free (buf);
		//		return 0;
		//	}
		//	free (buf);
		//	return ntohs(size);
		//}
		~ServerConnection(){
			this->join();
		}
};

#endif 
