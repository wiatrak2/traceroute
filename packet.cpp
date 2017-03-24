#include "packet.h"

bool Packet::operator == ( const Packet& p ) const
{
	if( this->packet_id == p.packet_id && this->packet_ttl == p.packet_ttl )
		return true;
	return false;
}

bool Packet::operator != ( const Packet& p ) const
{
	return( ! ((*this) == p) );
}

Packet& Packet::operator = ( const Packet& p )
{
	this->packet_id = p.packet_id;
	this->packet_ttl = p.packet_ttl;
	this->packet_ip_addr = p.packet_ip_addr;
	this->packet_time = p.packet_time;

	return *this;
}

void print_route( std::array< Packet, 3 > received_packets, int received_packets_amount, std::clock_t sent_time )
{
	if( ! received_packets_amount )
	{
		printf("*\n");
		return;
	}

	std::set< const char* > ip_addresses;
	for( auto i = received_packets.begin() ; i != received_packets.begin() + received_packets_amount ; ++ i )
		ip_addresses.insert( i->packet_ip_addr );

	for( auto ip : ip_addresses )
		printf("%*s ", 15, ip );

	if( received_packets_amount == 3 )
	{
		std::clock_t avg_time;
		for( auto p : received_packets )
			avg_time += ( p.packet_time - sent_time );
		avg_time = 1000 * ( avg_time / 3 ) / CLOCKS_PER_SEC;
		printf("%ldms\n", avg_time );
	}
	else
		printf("???\n");

}