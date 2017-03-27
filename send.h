/*
 * Wojciech Pratkowiecki nr indeksu: 281417
 * Sieci Komputerowe II UWr
 * traceroute
 */
#ifndef send_h
#define send_h 

#include "utils.h"

class Sender
{
	/* obiekt klasy Sender jest przywiązany do jednego docelowego adresu IP */
	struct sockaddr_in recipient;

	struct icmphdr create_icmphdr( int echo_id, int echo_seq );
	
public:

	Sender();
	Sender( const char* ip_addr );

	void send_packet( int ttl, const int& socket, int id, int seq );
	
};

#endif
