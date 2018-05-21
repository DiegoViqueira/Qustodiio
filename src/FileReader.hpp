//============================================================================
// Name        : FileReaer.hpp
// Author      : Diego Viqueira
// Version     :
// Copyright   :
// Description : File Reader 
// 
//
//============================================================================
#ifndef FILE_READER_HPP_
#define FILE_READER_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Protocol.hpp"

// Common Header for all Mesages

class FileReader
{
	public:
		//Parameters Contructor 
		FileReader(const std::string oFile ):m_input_file(oFile.c_str()){};
		
		// validity Check
		bool isOpen(){return m_input_file.is_open();};
		
		// Read lines to Protocol Class 
	
		bool getRequest( Request& obj );
	
	private:
	std::ifstream m_input_file;
	std::vector<std::string> get_3_lines();	
	
	
};


#endif		/*	FILE_READER_HPP_	*/