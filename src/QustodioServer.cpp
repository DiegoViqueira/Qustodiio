// Base Includes
#include <iostream>
#include <iostream>
#include <thread>
#include <utility>

//ThirdParty Includes
#include <boost/asio.hpp>

//Common Includes
#include "CmdOptionsParser.hpp"
#include "MakeString.hpp"
#include "TCP_Handlers.hpp"



using namespace std;

//******************************************************************
//                      MAIN
//******************************************************************
int main(int argc, char **argv) {

	// Checking args requirement


	cout <<"##########################################"<<endl;
	cout <<"          Qustodio Test: SERVER. " <<endl;
	cout <<"          Version: 1.0 " <<endl;
	cout <<"          Author: Diego Viqueira " <<endl;
	cout <<"##########################################"<<endl;

	CmdOptions input(argc, argv);


	 try
	  {

	    //Building Reporter Instance
		std::shared_ptr<Reporter> spReporter = Reporter::getInstance();

		//Launch Runing process in new thread
		std::thread(boost::bind(&Reporter::run, spReporter)).detach();
		
	    //Starting The Server
		boost::asio::io_service io_service;
	    Server MyServer(io_service, 42422);
		MyServer.run();
	  }
	  catch (std::exception& e)
	  {
	    std::cerr << "Exception: " << e.what() << "\n";
	  }

	return 0;
}
