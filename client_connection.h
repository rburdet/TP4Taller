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

		int startconnection(const std::string& fileName){
		if (connect(sd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
		perror("problemas conectado");
		return -1;
	}else{//Me pude conectar
		std::cout << "[SERVIDOR] PUERTO " << port << 
			" Aceptado. Recibiendo datos..." << std::endl;
		std::cout << "[CLIENTE] Enviado datos..."<<std::endl;
		uint32_t dataSent = this->sendFile(fileName);
		if (getData(sd)>0){
		std::cout << Converter::convert
	("[SERVIDOR] Datos recibidos exitosamente. Cantidad de bytes recibidos: ",
	 dataSent)<<std::endl;
		}
	return 0;}
		}

		uint32_t sendFile(const std::string& fileName){
			std::stringstream ss;
			std::ifstream inputFile;
			std::istream* in = &std::cin;
			if (fileName!=""){
				inputFile.open(fileName.c_str());
				//Si no lo pude abrir
				if (!inputFile.good()){
					return 0;
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
				return 0;
			return toSend->length;
		}
};

#endif
