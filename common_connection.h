#ifndef CLIENT_FACTORY_H
#define CLIENT_FACTORY_H

class Connection{
	private:
		struct sockaddr_in my_addr;
		int sd;
	public:
		Connection(const std::string& ip, int port){
			if ((sd=socket(AF_INET,SOCK_STREAM,0)) == -1){
				std::cerr<<"error creando socket"<<std::endl;
			}
			my_addr.sin_family = AF_INET;
			my_addr.sin_port = htons(port);
			my_addr.sin_addr.s_addr = inet_addr(ip);
			memset(&(my_addr.sin_zero), '\0', 8);
		}
};

#endif
