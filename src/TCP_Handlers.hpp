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

using boost::asio::ip::tcp;


const int max_length = 2048;

void session(tcp::socket sock);


class Session
{
public:
    typedef boost::shared_ptr<Session> pointer;

    static pointer create(boost::asio::io_service &io) {
        return pointer(new Session(io));
    }

    ~Session() {}

    tcp::socket &socket() { return m_socket; }

    void start();
protected:
    Session(boost::asio::io_service &io)
        : m_socket(io) {
    }

  
private:
    tcp::socket m_socket;
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
