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
#include "Protocol.hpp"
#include <queue>

// Singleton for monitoring and Queueing Messages
class Reporter
{
	public:
	//Default Constructor
	static std::shared_ptr<Reporter> getInstance();
	//Destructor
	~Reporter();
	
	//Notify Message offensive
    bool notify_msg(const Request& oRequest);	
	//start runing Process
	void run();
	
	private:
	//Mutex for lock Container
	std::mutex _mutex;
	
	//Queue of Messages
	std::queue<Request>  m_queue;
    
};


#endif		/*	PROTOCOL_HPP_	*/