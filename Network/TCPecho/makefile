tcp:
	make tcpclient
	make tcpserver
tcpserver:TCPServer.hpp ServerTest.cc ThreadPool.h Task.h Daemon.h
	g++ -o $@ $^

tcpclient:TCPClient.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm ./tcpserver
	rm ./tcpclient