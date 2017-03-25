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

void print_route( std::array< Packet, 3 > received_packets, int received_packets_amount, std::chrono::steady_clock::time_point& sent_time )
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
		unsigned int avg_time;
		for( auto p : received_packets )
			avg_time += std::chrono::duration_cast< std::chrono::milliseconds >( p.packet_time - sent_time ).count( );
		avg_time /= 3;
		printf("%ums\n", avg_time );
	}
	else
		printf("???\n");

}