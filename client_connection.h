#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include "common_connection.h"

class ClientConnection : public Connection{
	public:
		ClientConnection(const std::string& ip, int port) : Connection(ip, port){}
		int startconnection(const std::string& fileName);
		uint32_t sendFile(const std::string& fileName);
};

#endif
