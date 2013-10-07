#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "common_com.h"
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

		uint32_t getData(int new_fd){
			uint32_t size;
			if (recv(new_fd,&size,sizeof(size),0) == -1){
				return 0;
			}
			int correctSize = htons(size);
			buf = (char*)malloc(correctSize);
			if (recv(new_fd,buf,correctSize,0) == -1){
				free (buf);
				return 0;
			}
			free (buf);
			return ntohs(size);
		}
};

#endif
