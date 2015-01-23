#include <iostream>
using namespace std;

#include "Thread.h"
#include "UnControlledSynchronizer.h"

//this is the class that needed to be synchronized, because a shared resource (for example :: a printer) is going to be shared among different worker
class printer{
	
	private :
		UNCONTROLLED_SYNCHRONIZER	syncer;
		
	public :
	
		//PRINTER INITIALIZER
		printer()
		{
			syncer = GET_A_NEW_UNCONTROLLED_SYNCHRONIZER;
		}
	
	void print(const char *msg)
	{
		ENABLE_SYNCHRONIZATION_FOR_UNCONTROLLED_SYNCHRONIZER( syncer );
		cout<<msg<<endl;
		DISABLE_SYNCHRONIZATION_FOR_UNCONTROLLED_SYNCHRONIZER( syncer );
	}
};

class worker implements Thread
{
	private :
	printer *printer_obj;
	const char* msg;
	unsigned long resting_time;
	
	public :
	
	worker(const char* m, printer* p, unsigned long time)//constructor with the thread id & the printer with which they will print
	{
		this->msg = m;
		this->printer_obj = p;
		this->resting_time = time;
	}
	
	void run()//implementing the run method which must be implemented as promised by imeplementing the Thread class
	{
		
		for(int i=0;i<10;i++)
		{	
			//here the ENABLING THREAD WAIT CHECKING ISN'T NECESSARY FOR THIS EXAMPLE
			this->printer_obj->print(this->msg);
			//AS THREAD WAITING FEATURE ISN'T NOT NECESSARY, THUS NO NEED TO DISABLE THIS
			Thread::sleep(this->resting_time);
		}
		
	}
};

int main()
{
	printer p;//making a printer object
	
	worker worker1("i'm worker one", &p, 231);
	worker worker2("who are you ?", &p, 145);
	
	worker2.start();
	worker1.start();
	
	worker1.join();
	worker2.join();
	
	return 0;
}