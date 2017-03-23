#include "utils.h"

int arg_valid ( int argc, const char* argv[] )
{
	if( argc != 2 )
	{
		printf( "argument amount error\n" );
		return ARGV_ERR;
	}

	std::regex rgx( "[[:digit:]]{1,3}\\.[[:digit:]]{1,3}\\.[[:digit:]]{1,3}\\.[[:digit:]]{1,3}" );
	if( !regex_match( argv[ 1 ], rgx ) )
	{
		printf( "wrong IP address\n" );
		return ARGV_ERR;
	}

	return 1;
}

u_int16_t compute_icmp_checksum (const void *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = (const u_int16_t*) buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}

void print_as_bytes (unsigned char* buff, ssize_t length)
{
	for (ssize_t i = 0; i < length; i++, buff++)
		printf ("%.2x ", *buff);	
}