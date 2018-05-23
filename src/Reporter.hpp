//============================================================================
// Name        : Reporter.hpp
// Author      : Diego Viqueira
// Version     :
// Copyright   :
// Descrption : Clase que implementa la notificacion de transacciones de un thread
// 
//
//============================================================================
#ifndef REPORTER_HPP_
#define REPORTER_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <boost/thread/thread.hpp>

// Abstract Class for Consumers of Reporter
class Consumer
{
	public:
	
	//Destructor
	virtual ~Consumer(){};
	
	//get the statistics for a consumer
	virtual int getStatistics() = 0 ;
	
};

// Singleton for monitoring
class Reporter
{
	public:
	//Default Constructor
	static std::shared_ptr<Reporter> getInstance();
	//Destructor
	~Reporter();
	
	//register a Consumer 
	void register_consumer (  const std::string &ConsumerName , std::shared_ptr<Consumer> spConsumer );
	
	//Erase a Consumer
	void erase_consumer ( const std::string &ConsumerName );
	
	//start runing Process
	void run();
	
	private:
		//Map of Consumers
		std::map < std::string , std::shared_ptr<Consumer> > mConsumers; 
		//Mutex for lock Container
		std::mutex _mutex;
};


#endif		/*	PROTOCOL_HPP_	*/