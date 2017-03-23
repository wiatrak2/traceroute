#ifndef receive_h
#define receive_h 

#include "utils.h"

class Receiver
{
	
public:
	int* socketfd;
	Receiver()
	: socketfd{ nullptr }
	{ throw std::runtime_error( " Wrong Receiver constructor " ); }
	
	Receiver( int* socketfd )
	: socketfd { socketfd }
	{ }

	int receive_packet();


};

#endif /* receive_h */