CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

traceroute: traceroute.o utils.o receive.o send.o packet.o
	$(CXX) $(CXXFLAGS) -o traceroute traceroute.o utils.o receive.o send.o packet.o

traceroute.o: traceroute.cpp

utils.o: utils.cpp utils.h

receive.o: receive.cpp receive.h

send.o: send.cpp send.h

packet.o: packet.cpp packet.h

clean:
	$(RM) traceroute *.o

.PHONY: clean