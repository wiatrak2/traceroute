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
	/* walidacja argumentów programu */
	if(! arg_valid( argc, argv ) )
		return -1;
	/* tworzenie gniazda surowego wraz ze sprawdzeniem powodzenia operacji */
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	int pid = getpid(); /* process id - używane w nagłówkach wysyłanych i odbieranych pakietów do identyfikacji pakietów skierowanych do naszego progrmau */
	int seq_num = 0; /* zmienna seq_num jest używana jako numer sekwencyjny w nagłówkach pakietów */

	Sender s( argv[ 1 ] );
	Receiver r( &sockfd );

	std::array< Packet, 3 > received_packets;
	int received_packets_amount = 0; /* zmienna wyznaczająca ilość otrzymanych interesujących nas pakietów w każdej iteracji pętli */

	bool destination = false; /* wartość boolowska mówiąca, czy otrzymano odpowiedź od adresu docelowego */

	for( int ttl = 1 ; ttl <= 30 && (!destination) ; ++ ttl )
	{

		for( int i = 0 ; i < 3 ; ++ i )
			s.send_packet( ttl, sockfd, pid, seq_num ++ ); /* wysyłanie pakietu o obecnym ttl ; numer sekwencyjny musi być unikatowy dla każdego pakietu, by uniknąć ewentualnego potraktowania kolejnych pakieów jako dyplikaty */

		std::chrono::high_resolution_clock::time_point sent_time = std::chrono::high_resolution_clock::now( );
		Packet sent_packet ( pid, ttl, argv[ 1 ], sent_time ); /* wzór pakietu wysłanego */
		/* przygotowanie wartości dla funkcji select */
		fd_set descriptors;
		FD_ZERO( &descriptors );
		FD_SET( sockfd, &descriptors );
		struct timeval tv; tv.tv_sec = 1 ; tv.tv_usec = 0;
		/* odbieranie pakietów */
		while( received_packets_amount < 3 )
		{
			int ready = select( sockfd + 1, &descriptors, NULL, NULL, &tv );

			if( ready < 0 )
				throw std::runtime_error( " Read from socket error " );

			if( ready == 0 ) /* upłynięcie wyznaczonego czasu */
				break;

			else
			{
				Packet p = r.receive_packet();
				if( p == sent_packet )
				{
					received_packets[ received_packets_amount ++ ] = p;
					if( ( std::string )( p.packet_ip_addr ) == argv[ 1 ] ) /* sprawdzenie, czy uzyskany pakiet pochodzi od adresu docelowego */
						destination = true;							
				} 
			}
			/* zgodnie z dokumentacją - funkcja select aktualizuje swoje pole czasowe automatycznie */
		}

		printf("%*d.\t", 2, ttl);
		print_route( received_packets, received_packets_amount, sent_time );
		received_packets_amount = 0;
	}


	return 0;
}