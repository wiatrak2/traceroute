#include "send.h"

Sender::Sender( )
{
	throw std::runtime_error(" Wrong Sender constructor ");
}

Sender::Sender( const char* ip_addr )
{
	bzero( &recipient, sizeof( recipient ) );
	recipient.sin_family = AF_INET;
	inet_pton( AF_INET, ip_addr, &recipient.sin_addr );
	printf("%s\n", ip_addr);
}

Sender::Sender( const Sender& s )
: recipient { s.recipient }
{ }

Sender& Sender::operator = ( const Sender& s )
{
	recipient = s.recipient;
	return *this;
}


struct icmphdr Sender::create_icmphdr ( int echo_id, int echo_seq )
{
	struct icmphdr icmp_header;
	icmp_header.type = ICMP_ECHO;
	icmp_header.code = 0;
	icmp_header.un.echo.id = echo_id;
	icmp_header.un.echo.sequence = echo_seq;
	icmp_header.checksum = 0;
	icmp_header.checksum = compute_icmp_checksum ( (u_int16_t*)&icmp_header, sizeof( icmp_header ) );
	return icmp_header;
}
