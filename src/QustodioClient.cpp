// Base Includes
#include <iostream>

//ThirdParty Includes

//Common Includes
#include "CmdOptionsParser.hpp"
#include "MakeString.hpp"
#include "TCP_Handlers.hpp"
#include "Protocol.hpp"


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

	  try
	  {


	    boost::asio::io_service io_service;

	    tcp::socket s(io_service);
	    tcp::resolver resolver(io_service);
	    boost::asio::connect(s, resolver.resolve({"localhost","14000"} ));

	    std::cout << "Enter message: ";
	    char request[max_length];
	    std::cin.getline(request, max_length);
	    size_t request_length = std::strlen(request);
		
		
		Header myheader(0x1,256) ;
	    boost::asio::write(s, boost::asio::buffer(&myheader, sizeof(Header)));

	    char reply[max_length];
	    size_t reply_length = boost::asio::read(s,
	        boost::asio::buffer(reply, request_length));
	    std::cout << "Reply is: ";
	    std::cout.write(reply, reply_length);
	    std::cout << "\n";
	  }
	  catch (std::exception& e)
	  {
	    std::cerr << "Exception: " << e.what() << "\n";
	  }
	return 0;
}
