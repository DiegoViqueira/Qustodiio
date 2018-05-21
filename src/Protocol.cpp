#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include "MakeString.hpp"
#include "StringUtils.hpp"
#include "Protocol.hpp"

	//##########################################################################
	//                        Request
	//##########################################################################
	Request::Request(std::string device,std::string url,std::string timestamp):m_device(device),m_url(url),m_timestamp(timestamp),h_(0x0,0),buffer_(0)
	{
		h_.setSize(m_device.size()+ m_url.size()+ m_timestamp.size() + 2  );
		m_payload_size=sizeof(Header)+h_.getSize() ;
	};

	Request::Request(const char *buf ,size_t size ):buffer_(0)
	{
		std::string strBuffer(buf,size);
				
		std::vector<std::string>  v_tokens = str::split(strBuffer,";");
		
		if (v_tokens.size() < 3)
			throw "Invalid Request ";
		
		m_device = v_tokens.at(0);
		m_url = v_tokens.at(1);
		m_timestamp = v_tokens.at(2);
		
		h_.setSize(m_device.size()+ m_url.size()+ m_timestamp.size() + 2 );
		m_payload_size=sizeof(Header)+h_.getSize()  ;
		
	};
	
	Request::~Request(){m_device.clear();m_url.clear();m_timestamp.clear(); 
	   if (buffer_){
            delete[] buffer_;
            buffer_=0;
       }
	   };
	
    void Request::setDevice( const std::string& dev )
	{ 
	  m_device= dev ; 
	  h_.setSize(size());
	  m_payload_size=sizeof(Header)+h_.getSize() ;
	}
	void Request::setURL( const std::string& url)
	{ m_url= url ;
	  h_.setSize(size() );
	  m_payload_size=sizeof(Header)+h_.getSize() ;
	}
	
	void Request::setTimestamp( const std::string& tmstmp )
	{ m_timestamp= tmstmp;
	  h_.setSize(size()  );
	  m_payload_size=sizeof(Header)+h_.getSize() ;
	}
	
	size_t Request::size(){ return m_device.size()+ m_url.size()+ m_timestamp.size() + 2 ; };
	
	//Payload
	const char* Request::payload()
	{
		
		if (buffer_)
			delete[] buffer_;
		
		buffer_=new char[m_payload_size];
		
		memcpy ( buffer_, &h_, sizeof(h_) );
		m_payload_size=sizeof(h_);
		
		
		std::string temp =  m_device ;
		temp += ";";
		temp +=  m_url ;
		temp += ";";
		temp +=  m_timestamp ;
		
		memcpy ( &buffer_[m_payload_size],  temp.c_str(), temp.length() );
		m_payload_size+=temp.length();
		
		return buffer_;
	}
	
	
	//##########################################################################
	//                        Responce
	//##########################################################################
	
	//Default Constructor
	Responce::Responce():h_(0x1,0),m_payload_size(0),buffer_(0){};
	//Parameter Cosntructor
	Responce::Responce(const std::string data ):m_data(data),h_(0x1,0),buffer_(0){h_.setSize(m_data.length());m_payload_size= sizeof(h_) + m_data.length(); };
	//Buffer constructor
	Responce::Responce(const char *buf ,size_t osize ):h_(0x1,0),buffer_(0){ m_data=std::string(buf,osize); h_.setSize(osize);m_payload_size= sizeof(h_) + m_data.length(); };
	
	
	
	Responce::~Responce()
	{ 
		if (buffer_){
            delete[] buffer_;
            buffer_=0;
        }
		m_payload_size=0;
		m_data.clear();
	};
	
	//Payload
	const char* Responce::payload()
	{
		if (buffer_)
			delete[] buffer_;
		
		buffer_=new char[m_payload_size];
		
		memcpy ( buffer_, &h_, sizeof(h_) );
		m_payload_size=sizeof(h_);
		
		memcpy ( &buffer_[m_payload_size],  m_data.c_str(), m_data.length() );
		m_payload_size+=m_data.length();
		
		return buffer_;
	}
	
