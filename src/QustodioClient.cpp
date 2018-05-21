// Base Includes
#include <iostream>

//ThirdParty Includes

//Common Includes
#include "CmdOptionsParser.hpp"
#include "MakeString.hpp"
#include "TCP_Handlers.hpp"
#include "Protocol.hpp"
#include "FileReader.hpp"


using namespace std;

//******************************************************************
//                      MAIN
//******************************************************************
int main(int argc, char **argv) {

	// Checking args requirement
	if (argc < 3 )
	{
		//Display Help
		cout << "Execute :   "<< argv[0] <<" -f [File]" << endl;
		return -1;
	}

	cout <<"##########################################"<<endl;
	cout <<"          Qustodio Test: CLIENT. " <<endl;
	cout <<"          Version: 1.0 " <<endl;
	cout <<"          Author: Diego Viqueira " <<endl;
	cout <<"##########################################"<<endl;

	CmdOptions input(argc, argv);

	//Checking Options for Filename to process
	if(!input.cmdOptionExists("-f"))
	{
		//Display Help
		cout << "ERROR: Argument Missing..." << endl;
		cout << "Execute :   "<< argv[0] <<" -f [File]" << endl;
		return -1;
	}


	const std::string &filename = input.getCmdOption("-f");
	cout << "Filename to Process: "<< filename << endl;

	FileReader ProcessFile(filename);
	
	if (!ProcessFile.isOpen())
	{
		cout << "Unable to Open File: "<< filename << endl;
		return -1;
	}
	
	  try
	  {

		//Stablish Sockets and Resolvers
	    boost::asio::io_service io_service;
	    tcp::socket s(io_service);
	    tcp::resolver resolver(io_service);
	    
		//Connect to the Server
		boost::asio::connect(s, resolver.resolve({"localhost","42422"} ));

		std::cout << "Connection with Server Stablished ..." << endl;
		
		
	    std::cout << "Press Enter to start processiong...";
	    char request[max_length];
	    std::cin.getline(request, max_length);
	    size_t request_length = std::strlen(request);
		
			
		Request MyRequest;
		
		//Leo todo el Archivo
		
		while( ProcessFile.getRequest(MyRequest) )
		{
		
		   //Send Request to Server
			boost::asio::write(s, boost::asio::buffer(MyRequest.payload(), MyRequest.payloadSize()));

			//Read Responce Header
			Header protocol_responce_Header;
			size_t reply_length = boost::asio::read(s,boost::asio::buffer((void *)&protocol_responce_Header,sizeof(Header)));
			
			//Read Responce Data
			char data[max_length];
			reply_length = boost::asio::read(s,boost::asio::buffer(&data,protocol_responce_Header.getSize()));
			
			Responce responce_from_server(data,protocol_responce_Header.getSize());
			cout << "Message Received from Server  size[" << responce_from_server.size() <<"] payload size ["<< responce_from_server.payloadSize()<<"] Data["<< responce_from_server.getData()<<"]"<< endl;
			
		
		}
		
		   	
		
		
	  }
	  catch (std::exception& e)
	  {
	    std::cerr << "Exception: " << e.what() << "\n";
	  }
	return 0;
}
