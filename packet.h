#ifndef packet_h
#define packet_h 

#include "utils.h"

class Packet
{
	int packet_id;
	int packet_seq;
	int packet_ttl;
	bool is_echo_reply;
	const char* packet_ip_addr;

public:

	Packet()
	: packet_id { -1 },
	packet_seq { -1 },
	packet_ttl{ -1 },
	is_echo_reply { false },
	packet_ip_addr{ nullptr }
	{ }

	Packet( int id, int seq, int ttl, bool echo_reply, const char* ip_addr )
	: packet_id { id },
	packet_seq { seq },
	packet_ttl { ttl },
	is_echo_reply { echo_reply },
	packet_ip_addr { ip_addr }
	{ printf("%s\n", packet_ip_addr ); }
	
};

#endif /* packet_h */