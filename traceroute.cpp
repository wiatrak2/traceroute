/*
 * Wojciech Pratkowiecki nr indeksu: 281417
 * Sieci Komputerowe II UWr
 * traceroute
*/
#include "utils.h"
#include "send.h"
#include "packet.h"
#include "receive.h"

int main( int argc, const char* argv[] )
{

	if(! arg_valid( argc, argv ) )
		return -1;

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	int pid = getpid();
	int seq_num = 0;

	Sender s( argv[ 1 ] );
	Receiver r( &sockfd );

	std::array< Packet, 3 > received_packets;
	int received_packets_amount = 0;

	bool destination = false;

	for( int ttl = 1 ; ttl <= 30 && (!destination) ; ++ ttl )
	{

		for( int i = 0 ; i < 3 ; ++ i )
			s.send_packet( ttl, sockfd, pid, seq_num ++ );

		std::chrono::steady_clock::time_point sent_time = std::chrono::steady_clock::now( );
		Packet sent_packet ( pid, ttl, argv[ 1 ], sent_time );

		fd_set descriptors;
		FD_ZERO( &descriptors );
		FD_SET( sockfd, &descriptors );
		struct timeval tv; tv.tv_sec = 1 ; tv.tv_usec = 0;
		
		while( received_packets_amount < 3 )
		{
			int ready = select( sockfd + 1, &descriptors, NULL, NULL, &tv );

			if( ready < 0 )
				throw std::runtime_error( " Read from socket error " );

			if( ready == 0 )
				break;

			else
			{
				for( int i = 0 ; i < ready ; ++ i )
				{
					Packet p = r.receive_packet();
					if( p == sent_packet )
					{
						received_packets[ received_packets_amount ++ ] = p;
						if( (std::string)(p.packet_ip_addr) == argv[ 1 ] )
							destination = true;							
					} 
				}
			}
		}

		printf("%*d.\t", 2, ttl);
		print_route( received_packets, received_packets_amount, sent_time );
		received_packets_amount = 0;
	}


	return 0;
}