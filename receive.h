#ifndef receive_h
#define receive_h 

#include "utils.h"
#include "packet.h"

class Receiver
{
	int* socketfd;

public:

	Receiver()
	: socketfd{ nullptr }
	{ throw std::runtime_error( " Wrong Receiver constructor " ); }
	
	Receiver( int* socketfd )
	: socketfd { socketfd }
	{ }

	Packet receive_packet();


};

#endif /* receive_h */