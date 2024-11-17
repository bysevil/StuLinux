tcp:
	make tcpclient
	make tcpserver
tcpserver:TCPServer.hpp
	g++ -o $@ $^

tcpclient:TCPClient.hpp
	g++ -o $@ $^

.PHONY:clean
clean:
	rm ./tcpserver
	rm ./tcpclient