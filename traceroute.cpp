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
	int num = 10;

	printf("%d\n", pid);

	Sender s( argv[ 1 ] );
	Receiver r( &sockfd );

	std::array< Packet, 3 > received_packets;
	int received_packets_amount = 0;

	for( int ttl = 0 ; ttl < 5 ; ++ ttl )
	{

		s.send_packet( 2, sockfd, pid, num++ );

		std::clock_t sent_time = std::clock();
		Packet sent_packet ( pid, ttl, argv[ 1 ], sent_time );

		printf("Packet sent time: %ld\n", std::clock());
		
		Packet p = r.receive_packet();
		Packet p2 = p;
		if(p != p2)
			printf("OK\n");
		
	}


	return 0;
}