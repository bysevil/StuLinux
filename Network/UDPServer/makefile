udp:
	make udpclient
	make udpserver
udpserver:udpserver.h udpserver.cc testServer.cc
	g++ -o $@ $^

udpclient:udpclient.cc udpserver.h
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -f ./udpserver
	rm -f ./udpclient