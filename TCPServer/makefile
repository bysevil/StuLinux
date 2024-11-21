tcp:
	make tcpclient
	make tcpserver
tcpserver:TCPServer.hpp ServerTest.cc
	g++ -o $@ $^

tcpclient:TCPClient.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm ./tcpserver
	rm ./tcpclient