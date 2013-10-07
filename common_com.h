#ifndef COMMON_COM_H
#define COMMON_COM_H
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>

//typedef struct TMsg{
//	const char* msg;
//	uint32_t length;
//} Msg;
//
class Msg{
	private:
		const char* msg;
		uint32_t length;
	
	public:
	Msg(std::string aMsg);
	uint32_t getLength();
	int sendLength(int sd);
	int sendMsg(int sd);
	int sendAll(int sd);
	~Msg();

};

#endif
