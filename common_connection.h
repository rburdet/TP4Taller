#ifndef CLIENT_FACTORY_H
#define CLIENT_FACTORY_H

#include <iostream>

#define BACKLOG 10

class Connection{
	protected:
		struct sockaddr_in my_addr;
		int sd;
	public:
		Connection(const std::string& ip, int port){
			if ((sd=socket(AF_INET,SOCK_STREAM,0)) == -1){
				std::cerr<<"error creando socket"<<std::endl;
			}
			my_addr.sin_family = AF_INET;
			my_addr.sin_port = htons(port);
			my_addr.sin_addr.s_addr = inet_addr(ip.c_str());
			memset(&(my_addr.sin_zero), '\0', 8);
			if (bind(sd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
				std::cerr<<"error on binding"<<std::endl;
			}
			if (listen(sd, BACKLOG) == -1) {
				std::cerr<< "error on listening"<<std::endl;
			}
			//int yes=1;
			//if (setsockopt(sd,SOL_SOCKET,SO_REUSEADDR, &yes,sizeof(int)) ==-1){
			//	perror("setsockopt");
			//	exit(1);
			//}
		}
		int getSocket(){return this->sd;}
		sockaddr_in* getAddr(){return &my_addr;}
};

#endif
