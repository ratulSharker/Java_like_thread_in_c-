#include <iostream>
using namespace std;

#include "Thread.h"
#include "ControlledSynchronizer.h"


class MarketPlace 
{
	private:
	//factorie's internal issue
	int product;
	
	bool isProductAvailable;
	
	CONTROLLED_SYNCHRONIZER sync_for_producer;
	CONTROLLED_SYNCHRONIZER sync_for_consumer;
	
	
	public:
	//open to outside world
	
	//constructor
	MarketPlace()
	{
		this->product = 0;
		
		this->isProductAvailable = NO;//initially no product is being 
		
		INITIALIZE_THE_CONTROLLED_SYNCHRONIZER( sync_for_producer );
		INITIALIZE_THE_CONTROLLED_SYNCHRONIZER( sync_for_consumer );
	}
	
	void supplyProduct()
	{
		//here only producer will enter & make product, producer will wait until the consumer has consumed it
				
		ENABLE_CONDITIONAL_SYNCHRONIZER( sync_for_producer );
		
		while(this->isProductAvailable == YES)//wait until the consumer is ready to consume any ready
			WAIT( sync_for_producer );
		
		//here the producer will reach only when no product is currently unavailable
		//which is isProductAvailable = NO
		
		//producing the product
		this->product++;
		cout<<"produced : "<<this->product;

		
		this->isProductAvailable = YES;		
		
		//notify the waited consumer
		STOP_WAITED( sync_for_consumer );
		DISABLE_CONDITIONAL_SYNCHORNIZER( sync_for_producer );
	}
	
	void consumeProduct()
	{
		//here only consumer will enter & consume product, consumer will wait until the producer has produced it
		
		//wait checking 
		ENABLE_CONDITIONAL_SYNCHRONIZER( sync_for_consumer );
		
		while(this->isProductAvailable == NO)
			WAIT( sync_for_consumer );
			
		//here the consumer will reach only when product is currently available
		//which is isProductAvailable = YES
		cout<<" - consumed : "<<this->product<<endl;		
		
		this->isProductAvailable = NO;
		
		//notify the waited producer
		STOP_WAITED( sync_for_producer );
		DISABLE_CONDITIONAL_SYNCHORNIZER( sync_for_consumer );
	}
};

class Producer implements Thread
{
	private:
	MarketPlace *market;
	
	public:
	Producer(MarketPlace *m)
	{
		this->market = m;//saving the market object
	}
	
	void run()
	{
		for(int i=0;i<9;i++)
		{
			this->market->supplyProduct();
			this->sleep(13);
		}
	}
};

class Consumer implements Thread
{
	private:
	MarketPlace *market;
	
	public:
	Consumer(MarketPlace *m)
	{
		this->market = m;//saving the market object
	}
	
	void run()
	{
		for(int i=0;i<9;i++)
		{
			this->market->consumeProduct();
			this->sleep(1243);
		}
	}
};

int main(int argc, char* argv[])
{
	MarketPlace m;
	
	//both share the same market
	Producer p(&m);
	Consumer c(&m);
	
	//start them both
	p.start();
	c.start();
	
	//wait for both to join the main thread
	p.join();
	c.join();
	
	cout<<"joined to main thread" <<endl;
	return 0;
}