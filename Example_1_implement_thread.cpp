#include "Thread.h"

unsigned long worker_id;

class MyWorker implements Thread
{
//PUBLIC AREA
public:

	void run()
	{
		for(int i=0;i<10;i++)
		{			
			std::cout<<"ID::"<<this->getID() <<"count::"<<" "<<i<<std::endl;
			Thread::sleep(1000);
			
			if(this->getID() == worker_id && i == 4)
				this->stop();//stop this thread immediately
		}
	}
};

int main(int argc, char* argv[])
{
	MyWorker worker;
	
	worker_id = worker.getID();
	
	worker.start();
	
	worker.join();
	
	return 0;
}