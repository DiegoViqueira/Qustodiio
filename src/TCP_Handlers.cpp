
#include "TCP_Handlers.hpp"

using namespace std;
void session(tcp::socket sock)
{

  try
  {
	cout <<"["<< boost::this_thread::get_id()<< "]"<<" New Connection from :" << sock.remote_endpoint().address().to_string()  << endl;
    for (;;)
    {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock.read_some(boost::asio::buffer(data), error);
	  
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      boost::asio::write(sock, boost::asio::buffer(data, length));
	  
	  cout << "Message Received from Client: " << data << endl;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}


void Session::start() 
{
        

   try
	  {
		cout <<"["<< boost::this_thread::get_id()<< "]"<<" New Connection from :" << m_socket.remote_endpoint().address().to_string()  << endl;
		for (;;)
		{
		  char data[max_length];

		  boost::system::error_code error;
		  size_t length = m_socket.read_some(boost::asio::buffer(data), error);
		  
		  if (error == boost::asio::error::eof)
			break; // Connection closed cleanly by peer.
		  else if (error)
			throw boost::system::system_error(error); // Some other error.

		  boost::asio::write(m_socket, boost::asio::buffer(data, length));
		  
		  cout << "Message Received from Client: " << data << endl;
		}
	  }
	  catch (std::exception& e)
	  {
		std::cerr << "Exception in thread: " << e.what() << "\n";
	  }
}


void Server::run()
	{
		cout<<"TCP Server Start Listening on port ["<< m_port <<"]" << endl;
		tcp::acceptor a(m_io_service, tcp::endpoint(tcp::v4(), m_port));
		for (;;)
		{
			Session::pointer new_Session = Session::create(m_io_service);
			a.accept(new_Session->socket());
			std::thread(boost::bind(&Session::start, new_Session)).detach();
			
			
		}
	}


