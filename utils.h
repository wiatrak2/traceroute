#ifndef utils_h
#define utils_h

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <cassert>
#include <regex>

#define ARGV_ERR 0

int arg_valid ( int argc, const char* argv[] );
void print_as_bytes (unsigned char* buff, ssize_t length);
u_int16_t compute_icmp_checksum ( const void *buff, int length );

#endif /* utils_h */