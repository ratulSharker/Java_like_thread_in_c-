#ifndef	THREAD_H_
#define THREAD_H_

#include <iostream>
#include <pthread.h>

//at a time enable only one
//#define WINDOWS_PLATFORM
//#define LINUX_PLATFORM
#define OSX_PLATFORM


//os dependent sleep implementation
#ifdef WINDOWS_PLATFORM
    #include <windows.h>
    #define SLEEP(MILLIS) Sleep(MILLIS)
#endif


#ifdef OSX_PLATFORM
    #include <unistd.h>
    #define SLEEP(MILLIS) usleep(MILLIS * 1000)
#endif



//SOME STATE VALUES
enum THREAD_STATUS
	{	THREAD_CHECKING_FOR_WAIT,
		THREAD_RUNNING,	
		THREAD_NOT_YET_STARTED,
        THREAD_RUN_METHOD_RUNNING_COMPLETED,
        THREAD_STOPPED
	};//these enums are defined for determining the state of the thread inside the run() loop method. this method is called loop method it is the thread where loopy works are done :). These macros are use for implementing a blocking-nonblocking feature on thread class

//SOME OF MY OWN SUGAR
#define ENABLE_WAIT_CHECKING  pthread_mutex_lock( &this->m_cond_mutex_for_wait );  \
							  this->thread_status=THREAD_CHECKING_FOR_WAIT; \
							  while(this->m_do_thread_wait==YES) \
							  pthread_cond_wait(&this->m_cond_var_for_wait, &this->m_cond_mutex_for_wait);\
                              this->thread_status=THREAD_RUNNING
			
#define	DISABLE_WAIT_CHECKING pthread_mutex_unlock( &this->m_cond_mutex_for_wait )

//SOME OBJECTIVE-C SUGAR
#define YES					true
#define NO					false

//SOME JAVA SUGARS
#define implements 			:public
#define anonymous 			class:public 



//#define MILI_TO_NANO(mili)	mili*1000000L	

/*
	comment the next define if you want all of your 
	thread class to be as a pointer.
	
	Remember, if choose as a pointer,  destructor of Thread class
	must be called to avoid memory leak
*/
#define DECLARE_THREAD_CLASS_MEMBER_AS_POINTER

class Thread
{
	//PRIVATE AREA FOR PROPERTIES
	private:
	
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		pthread_t       *m_pthread;
    #else
		pthread_t	 	 m_pthread;
	#endif
    
    static pthread_mutex_t  m_mutex_lock; //used in the "pthread_entry_point" static function so that  in a time being only one instance of Thread   can access to the "pthread_entry_point" function so that the synchronization works :)
	
	//PROTECTED AREA FOR PROPERTIES
	protected:
	bool				m_do_thread_wait;
	pthread_mutex_t		m_cond_mutex_for_wait;
	pthread_cond_t		m_cond_var_for_wait;//these three variable will be used to provide simple java like thread::wait() functionality in our thread class. a macro will provide to put in the loop of the "run()" method to check each time is it time to wait ... some more detail will be explained with the macro
	
	THREAD_STATUS 		thread_status;// possible values of this byte storage will be THREAD_CHECKING_FOR_WAIT or THREAD_RUNNING or THREAD_NOT_YET_STARTED declared in the THREAD_STATUS enum. it will denote the current thread status. it will be a readonly property.
	
	//PUBLIC AREA
	public:
	
	/**
	* Constructor & destructor
	**/
	Thread();
	~Thread();

	
	//pure virtual method which should be implemented in the derived classs
	virtual void run() = 0;
	
	
	/**
	* METHOD THAT IMPLEMENTED ONLY ON THE THREAD CLASS
	* DO NOT OVERRIDE THIS START METHOD -- find a way upto it
	* these are standard thread functionality
	**/
	
	//simply start the thread
	void 	start();
	
	//make sleep for the calling thread
	static void	sleep(long milis);
	
	//join functionality of thread
	void 	join();
	
	//stop the running thred, if the thread is not running, calling it has no effect
	void	stop();
	
	//identification of each thread -- name like feature, difference is that you cant set a id for each thread, it is being pre-defined
	unsigned long getID();
	
	//wait function will simply put the thread to sleep at the "NEXT ITERATION" inside the run method
	unsigned long wait(bool isBlocking=NO, unsigned long checkingPeriod=0);
	void notify();
	
	//get the current status of the thread. check against the THREAD_STATUS enum declaration.
    inline THREAD_STATUS getStatus(){ return this->thread_status; }
	
	//PRIVATE AREA FOR METHOD
	private:
	
	//this static function will serve as the entry point of the thread
	static void* pthread_entry_point(void *thread_obj);
};

#endif
