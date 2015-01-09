#include "Thread.h"


class MyRunner implements Thread
{
//PUBLIC AREA
public:
	
	void run()
	{
		for(int i=0;i<10;i++)
		{
			std::cout<<i<<" "<<std::endl;
			this->sleep(1000);
		}
		std::cout<<"This is my runner"<<std::endl;
	}
};



int main (int argc, char *argv[])
{
	MyRunner *runner1 = new MyRunner(),
			 *runner2 = new MyRunner();
	
	
	runner1->start();
	runner2->start();
	
	int i;
	
	runner1->join();
	runner2->join();
	
	delete runner1;
	delete runner2;
	
	return 0;
}