#ifndef LOCK_H
#define LOCK_H

#include "common_mutex.h"

class Lock{
	private:
		Mutex& m;
	public:
		Lock(Mutex& mutex) : m(mutex){
			m.lock();
		}
		~Lock(){
			m.unlock();
		}
};

#endif
