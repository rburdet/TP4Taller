#ifndef COMMON_COM_H
#define COMMON_COM_H
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>

typedef struct TMsg{
	const char* msg;
	uint32_t length;
} Msg;

Msg* createMsg(std::string aMsg);
int sendLength(uint sd,int32_t length);
int sendMsg(int sd,Msg* aMsg);
int sendAll(int sd,Msg* aMsg);


#endif
