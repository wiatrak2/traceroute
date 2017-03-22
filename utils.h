#ifndef utils_h
#define utils_h

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdint.h>
#include <regex>

#define ARGV_ERR 0

int arg_valid ( int argc, const char* argv[] );

u_int16_t compute_icmp_checksum ( const void *buff, int length );

#endif /* utils_h */