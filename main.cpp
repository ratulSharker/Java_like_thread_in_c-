#include "Thread.h"

long runner_1_id;

class MyRunner implements Thread
{
//PUBLIC AREA
public:

	void run()
	{
		for(int i=0;i<10;i++)
		{
			std::cout<<"ID::"<<this->getID() <<"count::"<<" "<<i<<std::endl;
			this->sleep(1000);
			
			if(this->getID() == runner_1_id && i == 4)
				this->stop();//stop this thread immediately
		}
	}
};

int main (int argc, char *argv[])
{

	/*
	MyRunner *runner1 = new MyRunner(),
			 *runner2 = new MyRunner();
	
	runner_1_id = runner1->getID();
	std::cout<<"runner 1 id " << runner_1_id<<std::endl;
	
	runner1->start();
	runner2->start();
	
	runner1->join();
	runner2->join();
	
	delete runner1;
	delete runner2;
	*/
	
	/**
	EXAMPLE OF MAKING AN ANONYMUS THREAD LIKE JAVA
	**/
	anonymous Thread{
		public:
		void run()
		{
			for(int i=0;i<11;i++)
			{
				std::cout<<"count "<<i<<std::endl;
				this->sleep(1000);
			}
		}
	}t;
	
	anonymous Thread{
		public:
		void run()
		{
			for(int i=0;i<11;i++)
			{
				std::cout<<"count2 "<<i<<std::endl;
				this->sleep(1000);
			}
		}
	}t2;
	
	t.start();
	t2.start();
	
	t.join();
	t2.join();
	
	return 0;
}