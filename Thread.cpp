#include "Thread.h"
#include <windows.h>
#include <cstring>

/**
 The purpose of declaration as static is so that, no one else outside of this file can't access this function
**/
static void *global_c_function_for_pthread_start(void* thread_obj)
{
	if(thread_obj == NULL){
		std::cout<<"it's null bro";
		return NULL;
	}
	
	
	//ENABLING THE CANCEL FUNCTIONALITY
	//
	//We will use "pthread_cancel" function to stop a thread but "pthread_cancel" works on basis cancel_state & cancel_type, thus. cancel_state default value is set to ENABLED, thats why we dont need to tweak the cancel_state. the default value of the cancel_type is "DEFERRED" which we need to change thats why we are adding two line following
	//details on http://man7.org/linux/man-pages/man3/pthread_cancel.3.html
	int prevType;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &prevType);
	
	Thread *obj = (Thread*)thread_obj;
	obj->run();
}

//CONSTRUCTOR
Thread::Thread()
{	
	std::cout<<"constructor called"<<std::endl;
	//allocate the m_pthread property
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		this->m_pthread = (pthread_t*) malloc(sizeof(pthread_t));
	#else
		//nothing until now
	#endif
}

//DESTRUCTOR
Thread::~Thread()
{
	std::cout<<"destructor called"<<std::endl;
	
	//deallocate the m_pthread property
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		free(this->m_pthread);
	#else
		//nothing until now
	#endif
	
}

//METHOD THAT NOT TO BE OVERRIDDEN
void Thread::start()
{
	//continiously call until the thread creation succeed
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		if( pthread_create(	this->m_pthread,
						NULL, //this attribute must be implemented
						global_c_function_for_pthread_start,
						(void*)this) )
		{
			//you can throw exception here  -- further design issue
		}
	#else
		if( pthread_create(	&(this->m_pthread),
						NULL, //this attribute must be implemented
						global_c_function_for_pthread_start,
						(void*)this) )
		{
			//you can throw exception here  -- further design issue
		}
	#endif
}

void  Thread::sleep(long milis)
{
	Sleep(milis);
}

void Thread::join()
{
	//deallocate the m_pthread property
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		pthread_join(*this->m_pthread, NULL);
	#else
		pthread_join(this->m_pthread, NULL);
	#endif
}



void Thread::stop()
{
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		pthread_cancel(*this->m_pthread);
	#else
		pthread_cancel(this->m_pthread);
	#endif
}

long Thread::getID()
{
	unsigned long mem_add = 0;
	
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		mem_add = (long)this->m_pthread;
	#else
		mem_add = (long)&(this->m_pthread);
	#endif
}