#include "common_converter.h"
#include "client_connection.h"
#include <string>

int ClientConnection::startconnection(const std::string& fileName){
	if (connect(sd, (struct sockaddr*)&my_addr, 
				sizeof(struct sockaddr)) == -1 ){
		perror("problemas conectado");
		return -1;
	}else{//Me pude conectar
		std::cout << "[SERVIDOR] PUERTO " << port << 
			" Aceptado. Recibiendo datos..." << std::endl;
		std::cout << "[CLIENTE] Enviando datos..."<<std::endl;
		uint32_t dataSent = this->sendFile(fileName);
		if (getData(sd)>0){
		std::string msg=Converter::convert(
	"[SERVIDOR] Datos recibidos exitosamente. Cantidad de bytes recibidos: ",
	dataSent);
		msg.push_back('.');
		std::cout<<msg<<std::endl;
		}
	return 0;}
}

uint32_t ClientConnection::sendFile(const std::string& fileName){
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
	Msg toSend(ss.str());
	if (toSend.sendAll(sd)==-1)
		return 0;
	return toSend.getLength();

}
