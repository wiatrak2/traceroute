#ifndef packet_h
#define packet_h 

#include "utils.h"
#include <set>

class Packet
{
public:

	int packet_id;
	int packet_ttl;
	const char* packet_ip_addr;

	std::clock_t packet_time;

	Packet()
	: packet_id { -1 },
	packet_ttl{ -1 },
	packet_ip_addr{ nullptr },
	packet_time { -1 }
	{ }

	Packet( int id, int ttl, const char* ip_addr, std::clock_t time )
	: packet_id { id },
	packet_ttl { ttl },
	packet_ip_addr { ip_addr },
	packet_time { time }
	{  }

	Packet& operator = ( const Packet& p );
	bool operator == ( const Packet& p ) const;
	bool operator != ( const Packet& p ) const;
};

void print_route( std::array< Packet, 3 > received_packets, int received_packets_amount, std::clock_t sent_time );

#endif /* packet_h */