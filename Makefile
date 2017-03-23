CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

traceroute: traceroute.o utils.o receive.o send.o
	$(CXX) $(CXXFLAGS) -o traceroute traceroute.o utils.o receive.o send.o

traceroute.o: traceroute.cpp

utils.o: utils.cpp utils.h

receive.o: receive.cpp receive.h

send.o: send.cpp send.h

clean:
	$(RM) traceroute *.o

.PHONY: clean