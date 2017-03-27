/*
 * Wojciech Pratkowiecki nr indeksu: 281417
 * Sieci Komputerowe II UWr
 * traceroute
 */
#include "send.h"
/* poniższe funkcje zostały utowrzone na podstawie materiałów z wykładu */
Sender::Sender( )
{
	throw std::runtime_error( " Wrong Sender constructor " );
}

Sender::Sender( const char* ip_addr )
{ 
	/* uzupełnianie struktury adresata */
	bzero( &recipient, sizeof( recipient ) );
	recipient.sin_family = AF_INET;
	if( inet_pton( AF_INET, ip_addr, &recipient.sin_addr ) != 1 )
		throw std::runtime_error( " Converting IP address fault " );
}

void Sender::send_packet( int ttl, const int& socket, int id, int seq )
{
	/* wysyłanie pakietu o określonych wartościach */
	struct icmphdr header = create_icmphdr( id, seq );
	setsockopt ( socket, IPPROTO_IP, IP_TTL, &ttl, sizeof( int ) );
	ssize_t bytes_sent = sendto( socket, &header, sizeof( header ), 0, ( struct sockaddr* ) &recipient, sizeof( recipient ) );
	if( bytes_sent <= 0 )
		throw std::runtime_error( " Couldn't sent a packet " );
}


struct icmphdr Sender::create_icmphdr ( int echo_id, int echo_seq )
{
	/* tworzenie struktury icmphdr */
	struct icmphdr icmp_header;
	icmp_header.type = ICMP_ECHO;
	icmp_header.code = 0;
	icmp_header.un.echo.id = echo_id;
	icmp_header.un.echo.sequence = echo_seq;
	icmp_header.checksum = 0;
	icmp_header.checksum = compute_icmp_checksum ( (u_int16_t*)&icmp_header, sizeof( icmp_header ) );
	return icmp_header;
}
