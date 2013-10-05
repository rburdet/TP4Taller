#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex{
	private:
		pthread_mutex_t m;

	public:
		Mutex(){
			pthread_mutex_init(&m,NULL);
		}
		void lock(){
			pthread_mutex_lock(&m);
		}
		void unlock(){
			pthread_mutex_unlock(&m);
		}
		~Mutex(){
			pthread_mutex_destroy(&m);
		}
};

#endif 
