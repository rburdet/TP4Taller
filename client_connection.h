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
		int startconnection(){
		if (connect(sd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
		perror("problemas conectado");
		return -1;
	}else{//Me pude conectar
		std::cout << "[SERVIDOR] PUERTO " << 3940 << " Aceptado. Recibiendo datos..." << std::endl;
	return 0;}
		}

		int sendFile(const std::string& fileName){
			std::stringstream ss;
			std::ifstream inputFile;
			std::istream* in = &std::cin;
			if (fileName!=""){
				inputFile.open(fileName.c_str());
				//Si no lo pude abrir
				if (!inputFile.good()){
					return -1;
				}else{
					in = &inputFile;
				}
			}	
			char c;
			c = in->get();
			while(in->good()){
				ss << c;
				c = in->get();
			}
			Msg* toSend = createMsg(ss.str());
			if (sendAll(sd,toSend)==-1)
				return -1;
			return 0;
		}
};

#endif
