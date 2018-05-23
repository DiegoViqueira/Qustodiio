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
        mConsumers.clear();
}

void Reporter::register_consumer (  const std::string &ConsumerName , std::shared_ptr<Consumer> spConsumer )
{
	//lock mutex
    _mutex.lock();
		//Insert Consumer
		mConsumers.insert(make_pair(ConsumerName,spConsumer));
	//Unlock mutex
	_mutex.unlock();

    //std::cout <<" Consumer Registered ["<< ConsumerName <<"]"<<std::endl;	
}

void Reporter::run()
{
   	
	
	while(true)
	{
		//lock mutex
		_mutex.lock();
			//Iterate Consumers
			for (auto it : mConsumers )
			{
				int qtty = it.second->getStatistics();
				std::cout << "["<< boost::this_thread::get_id()<< "]" << " Consumer[" << it.first <<"]" << " Offensive activities last Second [" << qtty <<"]"<< std::endl;	
			}
		//Unlock mutex
		_mutex.unlock();
		
		
		//Sleep for 1 second
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}
}

void Reporter::erase_consumer (  const std::string &ConsumerName  )
{
	
	 std::map<std::string , std::shared_ptr<Consumer>>::iterator it;
	
	//lock mutex
    _mutex.lock();
		//Search the consumer
		it = mConsumers.find(ConsumerName);
		//Erase the Consumer
		if (it != mConsumers.end())
		{
			mConsumers.erase (it);
			//std::cout <<" Consumer Erased [" << ConsumerName <<"]"<<std::endl;	
		}
	//Unlock mutex
	_mutex.unlock();

    
}

