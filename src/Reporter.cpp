#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>         // std::chrono::seconds
#include <thread>
#include "Reporter.hpp"

namespace
{
    // shared pointer to Singleton reporter instance
    std::shared_ptr< Reporter >  g_sp_reporter;
}




std::shared_ptr<Reporter> Reporter::getInstance()
{
    
    // Check if it's the first time getInstance is called
    if ( !g_sp_reporter )
    {
       
        g_sp_reporter.reset( new Reporter());
       
    }
    
        // Return the reference to the Reporter Singleton
        return g_sp_reporter;
}

Reporter::~Reporter()
{
 
}


bool Reporter::notify_msg(const Request& oRequest)
{
	//Lock the mutex to use container
	_mutex.lock();
		//Store the Message
		m_queue.push(oRequest);
	//Unlock mutex
	_mutex.unlock();
	
}	

void Reporter::run()
{
   	
	
	while(true)
	{
		//lock mutex
		_mutex.lock();
			
			//Printing and Erasing all activities last 5 seconds.
			int qtty=0;
			while (!m_queue.empty())
			{
				 Request temp_request( m_queue.front());
				 m_queue.pop();
				 std::cout <<"["<< boost::this_thread::get_id()<< "]" << "OFFENCIVE WORDS IN[" << temp_request.getDevice()<<"]" << "[" << temp_request.getURL()<<"]"<< "[" << temp_request.getTimestamp()<<"]" << std::endl;
				 qtty++;
			}
				
			
			
		//Unlock mutex
		_mutex.unlock();
		
		std::cout <<"Inapropiate Activities in last 5 seconds: "<< qtty <<std::endl;
		//Sleep for 1 second
		std::this_thread::sleep_for (std::chrono::seconds(5));
	}
}

