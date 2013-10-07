#ifndef COMMON_THREAD_H
#define COMMON_THREAD_H

#include <pthread.h>
class Thread{
	private:
		pthread_t t;
		static void* starter(void* data){
			Thread* thread = (Thread*)data;
			thread->run();
			return thread;
		}

	public:
		void start(){
			pthread_create(&t,NULL,starter,this);
		}
		void join(){pthread_join(t,NULL);}
		virtual void run()=0;
		virtual ~Thread(){
			//std::cout<<"MATE UN THREAD " << std::endl;
			//pthread_exit(NULL);
		}
};

#endif
