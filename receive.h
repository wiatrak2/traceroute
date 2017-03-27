/*
 * Wojciech Pratkowiecki nr indeksu: 281417
 * Sieci Komputerowe II UWr
 * traceroute
 */
#ifndef receive_h
#define receive_h 

#include "utils.h"
#include "packet.h"

class Receiver
{
	int* socketfd; /* gniazdo z którego dany Receiver ma odbierać pakiety */

public:

	Receiver()
	: socketfd{ nullptr }
	{ throw std::runtime_error( " Wrong Receiver constructor " ); } /* próba utworzenia Receivera bez gniazda */
	
	Receiver( int* socketfd )
	: socketfd { socketfd }
	{ }

	Packet receive_packet();


};

#endif /* receive_h */