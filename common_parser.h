#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stdlib.h>
#include "common_list.h"
#include "common_node.h"
#include "server_connection.h"


void parsePorts(List<>* portList, char* ports){
	std::string portsStr = std::string(ports);
	std::string aport;
	portsStr.push_back(',');
	unsigned fpos;
	while (portsStr.size()>0){
		fpos = portsStr.find(',');
		if (fpos != std::string::npos){
			aport = portsStr.substr(0,fpos);
			portsStr.erase(0,fpos+1);
			Node<>* aux = new Node<>(atoi(aport.c_str()));
			portList->addNode(aux);
		}
	}	
}

int parseIP_PORT(char* IP_PORT,std::string& ip){
	std::string aux = IP_PORT;
	int pos = aux.find(':');
	ip =aux.substr(0,pos);
	int port = atoi(aux.substr(pos+1,aux.size()).c_str());
	return port;
}

#endif
