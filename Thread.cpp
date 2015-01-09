
#include "Thread.h"
#include <windows.h>


/**
 The purpose of declaration as static is so that, no one else outside of this file can't access this function
**/
static void *global_c_function_for_pthread_start(void* thread_obj)
{
	if(thread_obj == NULL){
		std::cout<<"it's null bro";
		return NULL;
	}
	std::cout<<"this called"<<std::endl;
	Thread *obj = (Thread*)thread_obj;
	obj->run();
}

//CONSTRUCTOR
Thread::Thread()
{	
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
	std::cout<<"start called"<<std::endl;
	
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