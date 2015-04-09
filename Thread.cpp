#include "Thread.h"
#include "UnControlledSynchronizer.h"
#include "ControlledSynchronizer.h"

#include <cstring>






//initializing the non-const static member
pthread_mutex_t Thread::m_mutex_lock = PTHREAD_MUTEX_INITIALIZER;

//static private method -- nobody can access it :D except the Thread class
void* Thread::pthread_entry_point(void *thread_obj)
{
    //locking the access only to the single thread
    pthread_mutex_lock(&Thread::m_mutex_lock);
    
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

    //before starting the real concurrent method -- we should release the mutex, otherwise two thread can't run concurrently
    pthread_mutex_unlock(&Thread::m_mutex_lock);
    
    obj->run();
	
    //change the state of the thread
    obj->thread_status = THREAD_RUN_METHOD_RUNNING_COMPLETED;
    
	//don't mess up with the "pthread_mutex_unlock(&Thread::m_mutex_lock)" line, if U wanna put this line just after the "obj->run()" all thread created extending or by anonymous class (supplying the run method) will be executed in a serialized manner, which is the opposite goal of parallel programming -- IF U DONT UNDERSTAND JUST KEEP UR HANDS OFF THIS FUNCTION :P
    
    return NULL;
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
	
	//KEEP IN MIND AT THE DESTRUCTOR IF POSSIBLE THIS VARIABLES SHOULD BE DEALLOCATED (if possible)
	//initialize the condition variables used for the wait method
	this->m_do_thread_wait = NO;
	this->m_cond_mutex_for_wait = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	this->m_cond_var_for_wait = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	
    //just object created but not started yet
    this->thread_status = THREAD_NOT_YET_STARTED;
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
						&(Thread::pthread_entry_point),
						(void*)this) )
		{
			//you can throw exception here  -- further design issue
		}
	#else
		if( pthread_create(	&(this->m_pthread),
						NULL, //this attribute must be implemented
						&(Thread::pthread_entry_point),
						(void*)this) )
		{
			//you can throw exception here  -- further design issue
		}
	#endif
}

//simple thread functionlity
void  Thread::sleep(long milis)
{
	SLEEP(milis); //this SLEEP method is basically a macro, which will be set at the compile time depending on the platform. It is being declared in the Thread.h
}

//simple thread functionlity
void Thread::join()
{
	//deallocate the m_pthread property
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		pthread_join(*this->m_pthread, NULL);
	#else
		pthread_join(this->m_pthread, NULL);
	#endif
}

//simple thread functionality
void Thread::stop()
{
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		pthread_cancel(*this->m_pthread);
	#else
		pthread_cancel(this->m_pthread);
	#endif
    
    this->thread_status = THREAD_STOPPED;
}

//simple thread functionality 
unsigned long Thread::getID()
{
	unsigned long mem_add = 0;
	
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		mem_add = (unsigned long)this->m_pthread;
	#else
		mem_add = (unsigned long)&(this->m_pthread);
	#endif
	
	return mem_add;
}

unsigned long Thread::wait(bool isBlocking, unsigned long checkingPeriod)
{
	this->m_do_thread_wait = YES;
	
	while(this->thread_status !=THREAD_CHECKING_FOR_WAIT && isBlocking == YES)
	{
		SLEEP(checkingPeriod);
	}
	
	unsigned long mem_add = 0;
	mem_add = (unsigned long)&this->m_cond_var_for_wait;
	return mem_add;
}

void Thread::notify()
{
	this->m_do_thread_wait = NO;
	pthread_cond_signal( &m_cond_var_for_wait );
}

/* //moved to Thread.h 
inline THREAD_STATUS Thread::getStatus()
{
	return this->thread_status;
}*/
