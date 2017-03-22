#ifndef send_h
#define send_h 

#include "utils.h"

class Sender
{



public:

	struct sockaddr_in recipient;

	Sender();
	Sender( const char* ip_addr );
	Sender( const Sender& s );
	Sender& operator = ( const Sender& s );

	struct icmphdr create_icmphdr( int echo_id, int echo_seq );
	
};

#endif
