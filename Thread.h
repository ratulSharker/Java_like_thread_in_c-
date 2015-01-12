#ifndef	THREAD_H_
#define THREAD_H_

#include <iostream>
#include <pthread.h>



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
		pthread_t	 m_pthread;
	#endif
    
    static pthread_mutex_t  m_mutex_lock; //used in the "pthread_entry_point" static function so that  in a time being only one instance of Thread   can access to the "pthread_entry_point" function so that the synchronization works :)
	
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
	
	//sleeps for the specified time of milisecond
	void 	sleep(long milis);
	
	//join functionality of thread
	void 	join();
	
	//stop the running thred, if the thread is not running, calling it has no effect
	void	stop();
	
	//identification of each thread -- name like feature, difference is that you cant set a id for each thread, it is being pre-defined
	long	getID();
	
	
	//PRIVATE AREA FOR METHOD
	private:
	
	//this static function will serve as the entry point of the thread
	static void* pthread_entry_point(void *thread_obj);
};

#endif
