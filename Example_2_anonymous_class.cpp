#include "Thread.h"

int main (int argc, char *argv[])
{	
	/**
	EXAMPLE OF MAKING AN ANONYMUS THREAD LIKE JAVA
	**/
	anonymous Thread{
		public:
		void run()
		{
			for(int i=0;i<11;i++)
			{
				std::cout<<"A "<<i<<std::endl;
				Thread::sleep(1000);
			}
		}
	}worker1;
	
	anonymous Thread{
		public:
		void run()
		{
			for(int i=0;i<11;i++)
			{
				std::cout<<"B "<<i<<std::endl;
				Thread::sleep(1000);
			}
		}
	}worker2;
	
    worker1.start();
	worker2.start();
	
	
	worker1.join();
	worker2.join();
	
	return 0;
}