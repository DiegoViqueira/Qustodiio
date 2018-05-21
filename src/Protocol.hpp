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
#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <cstdint>
#include <string>
#include <vector>

// Common Header for all Mesages
class Header
{
	public:
	//Default Constructor
	Header():m_msg_type(0x0),m_size(0){};
	//Copy Contructor
	Header( const Header &cpy ):m_msg_type(cpy.m_msg_type),m_size(cpy.m_size){};
	//Parameter Constructor
	Header(uint8_t msg_type, uint32_t size):m_msg_type(msg_type),m_size(size){};
	//Buffer Constructor
	Header(const char *buf ){ memcpy ( this, buf, sizeof (*this) ); };
	//Destructor
	~Header(){m_msg_type=0x0;m_size=0;};
	
	
	//setters
	void setMsgType(uint8_t type){ m_msg_type=type; }
	void setSize(uint32_t size){ m_size=size; }
	
	//getters
	uint8_t getType(){return m_msg_type; }; 
	uint32_t getSize(){return m_size;};
	
	private:
	uint8_t m_msg_type;
	uint32_t m_size;
	
	
};

class Request
{
	public:
	//Default Cosntructor
	Request():h_(0x0,0),m_payload_size(0),buffer_(0){};
	//Parameter Constructor
	Request(std::string device,std::string url,std::string timestamp);
	//Buffer Constructor
	Request(const char *buf ,size_t size );
	
	//Destructor
	~Request();
	
	//Protocol Encoder & Decoder 
	
	// Getters
	size_t size(){ return m_device.size()+ m_url.size()+ m_timestamp.size();};
	std::string  getDevice() { return m_device; }
	std::string  getURL() { return m_url; }
	std::string  getTimestamp() { return m_timestamp; }
	
	//Setters
	void setDevice( const std::string& dev ){ m_device= dev ; h_.setSize(size());}
	void setURL	( const std::string& url){ m_url= url ;h_.setSize(size());}
	void setTimestamp( const std::string& tmstmp ){ m_timestamp= tmstmp;h_.setSize(size());}
	
	//Payload
	const char* payload();
	size_t payloadSize(){return m_payload_size;};
	
	
	
	private: 
	std::string m_device;
	std::string m_url;
	std::string m_timestamp;
	
	protected:
	Header	h_;
	char	*buffer_;
	size_t  m_payload_size;
	
    
};

class Responce
{
	public:
	//Default Constructor
	Responce();
	//Parameter Cosntructor
	Responce(const std::string data );
	//Buffer constructor
	Responce(const char *buf ,size_t osize );
	
	//Destructor
	~Responce();
	
	//setters
	void setData(const std::string& data){ m_data=data ;h_.setSize(size());};
	
	//getters
	size_t size(){return m_data.length();}
	std::string getData(){ return m_data;};
	
	//Payload
	const char* payload();
	
	size_t payloadSize(){return m_payload_size;};
	
	private:
	std::string m_data;
	
	protected:
	Header	h_;
	char	*buffer_;
	size_t  m_payload_size;
};


#endif		/*	PROTOCOL_HPP_	*/