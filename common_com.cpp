#include "common_com.h"
#include <arpa/inet.h>

Msg::Msg(std::string aMsg){
	this->msg = aMsg.c_str();
	this->length = (uint32_t)aMsg.length();
}

Msg::~Msg(){}

int Msg::sendLength(int sd){
	int sent=0;
	int lengthToSend=htons(length);
	while (sent < (signed)sizeof(length)){
		sent += send(sd, &lengthToSend+sent,sizeof(lengthToSend)-sent,0);
		if (sent==-1)
			break;
	}
	return sent==-1?-1:0;
}

int Msg::sendMsg(int sd){
	int sent=0;
	while (sent < (signed)this->length){
		sent += send(sd, this->msg, this->length-sent, 0);
		if (sent ==-1)
			break;
	}
	return sent==-1?-1:0;
}

int Msg::sendAll(int sd){
	if (sendLength(sd) == -1)
		return -1;
	if (sendMsg(sd) == -1)
		return -1;
	return 0;
}

uint32_t Msg::getLength(){
	return this->length;
}
