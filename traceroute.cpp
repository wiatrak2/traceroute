#include "utils.h"
#include "send.h"
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

	return 0;
}