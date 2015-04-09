#include <iostream>
using namespace std;

#include "Thread.h"

class GetStatusDemo implements Thread
{
public:
    void run()
    {
        for(int i = 0 ; i < 10 ; i++)
        {
            //this enable wait checking will make the thread to be in te wait checking state
            ENABLE_WAIT_CHECKING;
            
            sleep(1000);
            cout<<"running loops "<<i<<endl;
            
            
            DISABLE_WAIT_CHECKING;
        }
    }
};

void statePrinter(THREAD_STATUS status)
{
    switch(status)
    {
    case THREAD_CHECKING_FOR_WAIT:
        cout<<"THREAD STATE : CHECKING FOR WAIT"<<endl;
        break;
    case THREAD_RUNNING:
        cout<<"THREAD STATE : THREAD RUNNING"<<endl;
        break;
    case THREAD_NOT_YET_STARTED:
        cout<<"THREAD STATE : THREAD NOT YET STARTED"<<endl;
        break;
    case THREAD_RUN_METHOD_RUNNING_COMPLETED:
        cout<<"THREAD STATE : THREAD RUN METHOD RUNNING COMPLETED"<<endl;
        break;
    case THREAD_STOPPED:
        cout<<"THREAD STATE : THREAD STOPPED"<<endl;
        break;
    }
}

int main(int argc, char **argv)
{
    GetStatusDemo demo;
    
    //before start the demo thread check the thread status
    statePrinter(demo.getStatus());
    
    demo.start();
    
    statePrinter(demo.getStatus());
    Thread::sleep(1800);
    cout<<"after initial sleep"<<endl;
    statePrinter(demo.getStatus());
    
    
    for(int i=0 ;i<5;i++)
    {
        demo.wait(NO, 10);
        
        //check for a luck so that we found the thread on "checking_for_wait" state
        statePrinter(demo.getStatus());
        
        Thread::sleep(2000);
        
        demo.notify();
    }
    
    Thread::sleep(1500);
    cout<<"out of the waiting loop"<<endl;
    statePrinter(demo.getStatus());
    
    //if you wanna see the whole portion of run method running just comment out the following 3 line of code then compile & run see what happen.
    demo.stop();
    cout<<"after stop"<<endl;
    statePrinter(demo.getStatus());
    
    
    demo.join();
    cout<<"after join"<<endl;
    statePrinter(demo.getStatus());
}
