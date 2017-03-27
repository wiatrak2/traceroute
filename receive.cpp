/*
 * Wojciech Pratkowiecki nr indeksu: 281417
 * Sieci Komputerowe II UWr
 * traceroute
 */
#include "receive.h"

Packet Receiver::receive_packet()
{
	/* odbieranie pakietu z gniazda */
	struct sockaddr_in 	sender;	
	socklen_t 			sender_len = sizeof(sender);
	u_int8_t 			buffer[IP_MAXPACKET];

	ssize_t packet_len = recvfrom (*socketfd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);
	if (packet_len < 0) {
		fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
		return Packet( );
	}

	char sender_ip_str[20]; 
	inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));

	struct iphdr* 		ip_header = ( struct iphdr* ) buffer;
	u_int8_t*			icmp_packet = buffer + 4 * ip_header->ihl;
	struct icmphdr*		icmp_header = ( struct icmphdr* ) icmp_packet;
	/* przygotowanie obiektu odebranego pakietu */
	if( icmp_header->type == ICMP_ECHOREPLY )
	{
		auto packet_time = std::chrono::high_resolution_clock::now( ); /* czas odebrania pakietu */
		/* jako, że każdy wysłany przez nas pakiet ma unikatowy numer sekwencyjny należy uzyskać ttl z jakim został pakiet wysłany poprzez dzielenie całkowite przez ilość pakietów i dodanie 1 */
		return Packet( icmp_header->un.echo.id, icmp_header->un.echo.sequence / 3 + 1, sender_ip_str, packet_time );
	}

	if( icmp_header->type == ICMP_TIME_EXCEEDED )
	{
		/* komunikaty ICMP time exceeded zawierają oryginalny nagłowek IP, należy więc odpowiednio się w nim przesunąć by uzyskać dane do identyfikacji pakietu */
		icmp_packet += 8;
		icmp_packet += 4 * ((struct ip*) icmp_packet)->ip_hl;
		struct icmp* icmp_time_ex = (struct icmp*) icmp_packet;

		auto packet_time = std::chrono::high_resolution_clock::now( );

		return Packet( icmp_time_ex->icmp_id, icmp_time_ex->icmp_seq / 3 + 1, sender_ip_str, packet_time );
	}

	return Packet();

}