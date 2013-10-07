#ifndef CLIENT_FACTORY_H
#define CLIENT_FACTORY_H

#include <stdint.h>
#include <iostream>
#define BACKLOG 10

class Connection{
	protected:
		struct sockaddr_in my_addr;
		int sd;
		int port;
		char* buf;

	public:
		Connection(const std::string& ip, int port){
			this->port=port;
			if ((sd=socket(AF_INET,SOCK_STREAM,0)) == -1){
				std::cerr<<"error creando socket"<<std::endl;
			}
			my_addr.sin_family = AF_INET;
			my_addr.sin_port = htons(port);
			my_addr.sin_addr.s_addr = inet_addr(ip.c_str());
			memset(&(my_addr.sin_zero), '\0', 8);
		}
		int getSocket(){return this->sd;}

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
};

#endif
