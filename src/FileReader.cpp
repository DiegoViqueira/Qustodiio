#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include "FileReader.hpp"

	std::vector<std::string> FileReader::get_3_lines()
	{
		int line_read=1;
		std::vector<std::string> temp_vector;
		
		//Leo de a 3 lineas
		for( std::string line; getline( m_input_file, line ); line_read++  )
		{
			
			temp_vector.push_back(line);
			
			if (line_read >= 3)
				break;
		}
		
		return temp_vector;
	}
	
	bool FileReader::getRequest( Request& obj )
	{
		
	  
	  std::vector<std::string> temp_v = get_3_lines();
	
	  if (temp_v.size() == 3 )
	  {
		 
		  obj.setDevice(temp_v.at(0));
		  obj.setURL(temp_v.at(1));
		  obj.setTimestamp(temp_v.at(2));
		  
		  return true;
	  }
	  else
	    return false;
	
	}