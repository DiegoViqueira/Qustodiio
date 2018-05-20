//============================================================================
// Name        : Protocol.hpp
// Author      : Diego Viqueira
// Version     :
// Copyright   :
// Description : Protocol Definition
// 
//  Messages Types:
//    0 - Request
//    1 - Responce
//
//============================================================================

#include <cstdint>
#include <string>



class Header
{
	public:
	Header():m_msg_type(0x0),m_size(0){};
	Header(uint8_t msg_type, uint32_t size):m_msg_type(msg_type),m_size(size){};
	Header(const char *buf ){ memcpy ( this, buf, sizeof (*this) ); };
	
	uint8_t m_msg_type;
	uint32_t m_size;
	
	
};

class Request
{
	public:
	Request(std::string device,std::string url,std::string timestamp):m_device(device),m_url(url),m_timestamp(timestamp){};
	std::string m_device;
	std::string m_url;
	std::string m_timestamp;
};

class Responce
{
	public:
	Responce(uint8_t code):m_code(code){};
	uint8_t m_code;
	
};


