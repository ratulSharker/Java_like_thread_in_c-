#ifndef	THREAD_H_
#define THREAD_H_

#include <iostream>
#include <pthread.h>

#define implements :public
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
	//PRIVATE AREA
	private:
	
	#ifdef DECLARE_THREAD_CLASS_MEMBER_AS_POINTER
		pthread_t	*m_pthread;
	#else
		pthread_t	 m_pthread;
	#endif
	
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
	void start();
	
	//sleeps for the specified time of milisecond
	void sleep(long milis);
	
	//join functionality of thread
	void join();
};

#endif
