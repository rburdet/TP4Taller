#include "common_com.h"
#include <arpa/inet.h>

int sendLength(int sd,uint32_t length){
	int sent=0;
	int lengthToSend=htons(length);
	while (sent < (signed)sizeof(length)){
		sent += send(sd, &lengthToSend+sent,sizeof(lengthToSend)-sent,0);
		if (sent==-1)
			break;
	}
	return sent==-1?-1:0;
}

int sendMsg(int sd,Msg* aMsg){
	int sent=0;
	while (sent < (signed)aMsg->length){
		sent += send(sd, aMsg->msg, aMsg->length-sent, 0);
		if (sent ==-1)
			break;
	}
	return sent==-1?-1:0;
}

int sendAll(int sd,Msg* aMsg){
	if (sendLength(sd,aMsg->length) == -1)
		return -1;
	if (sendMsg(sd,aMsg) == -1)
		return -1;
	return 0;
}

Msg* createMsg(std::string aMsg){
	Msg* pkg = (Msg*)malloc(sizeof(pkg));
	pkg->msg = aMsg.c_str();
	pkg->length = (uint32_t)aMsg.length();
	return pkg;
}
