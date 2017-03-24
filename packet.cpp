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