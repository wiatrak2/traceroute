#ifndef pachet_h
#define pachet_h 

class Packet
{
	int packet_id;
	int packet_seq;
	int packet_ttl;
	const char* packet_ip_addr;

public:

	Packet()
	: packet_id { -1 },
	packet_seq { -1 },
	packet_ttl{ -1 },
	packet_ip_addr{ nullptr }
	{ }

	Packet( int id, int seq, int ttl, const char* ip_addr )
	: packet_id { id },
	packet_seq { seq },
	packet_ttl { ttl },
	packet_ip_addr { ip_addr }
	{ }

	~Packet() { delete[] packet_ip_addr };
	
};

#endif /* packet_h */