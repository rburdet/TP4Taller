#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "common_connection.h"

class ServerConnection : public Connection{
	public:
		ServerConnection(const std::string& ip, int port) : Connection(ip, port){}
		

};

#endif 
