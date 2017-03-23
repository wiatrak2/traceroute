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

	Sender s( argv[ 1 ] );
	Receiver r( &sockfd );

	for( int i = 0 ; i < 5 ; ++ i )
	{

		s.send_packet( 30, sockfd, pid, num++ );
	
		
		 r.receive_packet();
			
		
	}


	return 0;
}