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

	// test sending

	int pid = getpid();
	int num = 0;

	printf("%d\n", pid);

	Sender s( argv[ 1 ] );
	Receiver r( &sockfd );

	std::array< Packet, 3 > received_packets;
	int received_packets_amount = 0;

	for( int ttl = 1 ; ttl < 30 ; ++ ttl )
	{

		s.send_packet( ttl, sockfd, pid, num++ );

		std::clock_t sent_time = std::clock();
		Packet sent_packet ( pid, ttl, argv[ 1 ], sent_time );

		printf("Packet sent time: %ld\n", std::clock());

		//select test

		fd_set descriptors;
		FD_ZERO( &descriptors );
		FD_SET( sockfd, &descriptors );
		struct timeval tv; tv.tv_sec = 1 ; tv.tv_usec = 0;
		int ready = select( sockfd + 1, &descriptors, NULL, NULL, &tv );
		if( ready < 0 )
			throw std::runtime_error( " Read from socket error " );

		if( ready == 0 )
			printf("NO PACKETS\n");

		else
		{
			Packet p = r.receive_packet();
			if( p == sent_packet )
				printf("OKKK - %d, %d\n", tv.tv_sec, tv.tv_usec);
			else
				printf("NOOOOO\n");
		}
		
	}


	return 0;
}