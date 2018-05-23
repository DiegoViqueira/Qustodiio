//============================================================================
// Name        : TCP_Handlers.hpp
// Author      : Diego Viqueira
// Version     :
// Copyright   :
// Description : Client/Server TCP Connection Classes
//============================================================================

#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>

#include "Reporter.hpp"

using boost::asio::ip::tcp;


const int max_length = 2048;

void session(tcp::socket sock);


class Session: public Consumer , public  std::enable_shared_from_this<Session>
{
public:

    //Constructor
    Session(boost::asio::io_service &io)
        : m_socket(io),m_quest_activities(0) {
    }

	//Destructor
    ~Session();
	
	//get the socket
    tcp::socket &socket() { return m_socket; };
	//Start the session
    void start();
	
	//Implementation of Consumer for Reporter
	int getStatistics() { return m_quest_activities; };
protected:


	std::string get_strID( boost::thread::id tid )
	{
		std::stringstream ss;
		ss << tid ;
		std::string strId(ss.str());
		
		return strId;
	} ;
  
private:
    tcp::socket m_socket;
	boost::atomic<int> m_quest_activities;
};

class Server
{
	public:
	
	Server(boost::asio::io_service& io_service, unsigned short port) : m_io_service(io_service),m_port(port){};
	
	void run();	
	private:
	unsigned short m_port;
	boost::asio::io_service& m_io_service;
	
};
