OBJ = tserver.o ts_net_server.o
CXXFLAGS = -std=c++11 -g

BOOSTLIBPATH = /usr/lib/boost/lib

all: server

.PHONY:server

server: $(OBJ)
	$(CXX) -L$(BOOSTLIBPATH) $(CXXFLAGS) $^ -lboost_system -lboost_thread -o $@

client: client.o
	$(CXX) -L$(BOOSTLIBPATH) $(CXXFLAGS) $^ -lboost_system -lboost_thread -o $@

.o: .cpp
	$(CXX) $(CXXFLAGS) $^ $@

clean:
	rm $(OBJ) server

.PHONY:client
