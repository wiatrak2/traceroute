#ifndef send_h
#define send_h 

#include "utils.h"

class Sender
{

	struct icmphdr create_icmphdr( int echo_id, int echo_seq );

public:

	struct sockaddr_in recipient;

	Sender();
	Sender( const char* ip_addr );
	Sender( const Sender& s );
	Sender& operator = ( const Sender& s );

	void send_packet( int ttl, const int& socket, int id, int seq );
	
};

#endif
