#include <iostream>
#include "Thread.h"
using namespace std;

class example_wait_notify_notifyAll implements Thread
{

	public:
	//public section goes here
	
	//unimplemented run method implementation
	void run()
	{
		for(int i=0;i<10;i++)
		{
			//checking for the wait condition -- this code will go to macro replacement
			/*pthread_mutex_lock( &this->m_cond_mutex_for_wait );
			while(this->m_do_thread_wait==YES)
			{
				pthread_cond_wait( &this->m_cond_var_for_wait, &this->m_cond_mutex_for_wait);
			}*/
			
			ENABLE_WAIT_CHECKING;
			
			cout<<"worker :: "<<i<<endl;
			
			Thread::sleep(1000);
			
			//this code is going into a macro
			//pthread_mutex_unlock( &this->m_cond_mutex_for_wait );
			DISABLE_WAIT_CHECKING;
		}
	}
};




int main(int argc, char *argv[])
{
	example_wait_notify_notifyAll ex1;
	
	ex1.start();
	
	//after 2 second worker will awake
	Thread::sleep(2000);//windows.h 's function direct call
	
	ex1.wait(YES,0);
	
	cout<<endl<<"order worker to wait"<<endl;
	cout<<"will inactive for 3 seconds..."<<endl;
	Thread::sleep(1000);
	cout<<"inactive 1st second passed"<<endl;
	Thread::sleep(1000);
	cout<<"inactive 2nd second passed"<<endl;
	Thread::sleep(1000);
	cout<<"inactive 3rd second passed"<<endl;
	cout<<"notifying worker"<<endl<<endl;
	
	
	ex1.notify();
	
	ex1.join();
}