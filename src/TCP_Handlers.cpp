
#include <regex>
#include "TCP_Handlers.hpp"


using namespace std;


Session::~Session() 
{
		
};


void Session::start() 
{
        

   try
	  {
		
		cout <<"["<< boost::this_thread::get_id()<< "]"<<" New Connection from :" << m_socket.remote_endpoint().address().to_string()  << endl;
		
		//Regular expression Patterns
		std::regex self_regex("porn|xxx|sex|Bieber",std::regex_constants::ECMAScript | std::regex_constants::icase);		  
		
		// Iterate for Messages
		for (;;)
		{
		  //Error Handling
		  boost::system::error_code error;

		  // Read Request From Client
		  Header request_header;

		  //Read Header
		  size_t length = m_socket.read_some(boost::asio::buffer((void *)&request_header,sizeof(Header)), error);
		  
		  
		  if (length > 0 )
		  {
			  //Read  Variable Part
			  char data[max_length];
			  length = m_socket.read_some(boost::asio::buffer(data,request_header.getSize()), error);
			  
			  if (length > 0 )
			  {
				  //Building Request 
				  Request temp_request(data,request_header.getSize());

				  // Printing Data
				  /*cout <<"["<< boost::this_thread::get_id()<< "]" << "New Request size[" << temp_request.size() <<"] payload size ["<< temp_request.payloadSize()<<"]" 
				   << "[" << temp_request.getDevice()<<"]" << "[" << temp_request.getURL()<<"]"<< "[" << temp_request.getTimestamp()<<"]"<< endl; 
				  */
				  if (std::regex_search(temp_request.getURL(), self_regex)) 
				  {
					//std::cout <<"["<< boost::this_thread::get_id()<< "]" << "OFFENCIVE WORDS IN[" << temp_request.getDevice()<<"]" << "[" << temp_request.getURL()<<"]"<< "[" << temp_request.getTimestamp()<<"]" << endl;
		
				    //obtain the singleton  Reporter
					std::shared_ptr<Reporter>  spReporter = Reporter::getInstance();
		
					//store the inapropiate message to process it later
					spReporter->notify_msg(temp_request);
					
				  }

				  //Send Responce
				  Responce protocol_responce("OK") ;
				  boost::asio::write(m_socket, boost::asio::buffer(protocol_responce.payload(), protocol_responce.payloadSize()));
			  }
		  }

		 //Check Errors to handle Close connections
		 if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
	     else if (error)
			throw boost::system::system_error(error); // Some other error.

		}
	  }
	  catch (std::exception& e)
	  {
		std::cerr << "Exception in thread: " << e.what() << "\n";
		
	  }
	  
}


void Server::run()
{
		
	try
	{

			//Start Listening Connections
			cout<<"TCP Server Start Listening on port ["<< m_port <<"]" << endl;
			tcp::acceptor a(m_io_service, tcp::endpoint(tcp::v4(), m_port));
			for (;;)
			{
				//create new Session
				std::shared_ptr<Session> new_Session = std::make_shared<Session>(m_io_service);
					
				//Accept New Connection
				a.accept(new_Session->socket());
				
				//Launch Thread for New Session
				std::thread(boost::bind(&Session::start, new_Session)).detach();
				
				
			}
	}
	catch (std::exception& e)
	{
	std::cerr << "Exception in thread: " << e.what() << "\n";
	}
	
}


