#include "receive.h"

int Receiver::receive_packet()
{
	struct sockaddr_in 	sender;	
	socklen_t 			sender_len = sizeof(sender);
	u_int8_t 			buffer[IP_MAXPACKET];

	ssize_t packet_len = recvfrom (*socketfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
	if (packet_len < 0) {
		fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	char sender_ip_str[20]; 
	inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));

	struct iphdr* 		ip_header = ( struct iphdr* ) buffer;
	u_int8_t*			icmp_packet = buffer + 4 * ip_header->ihl;
	struct icmphdr*		icmp_header = ( struct icmphdr* ) icmp_packet;

	if( icmp_header->type == ICMP_ECHOREPLY )
	{
		printf("ECHO REPLY\n");
	}

	if( icmp_header->type == ICMP_TIME_EXCEEDED )
	{
		printf("TIME EXCEEDED\n");
	}

	return 1;

}