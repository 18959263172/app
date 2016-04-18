CC=gcc
socket:
	${CC} socket.c -o socket
main:
	${CC} main.c -o main csock.c ticket.c 
udp:	
	${CC} udptrans.c -o udp 
test:
	${CC} test_udp.c -o test
clean:
	rm ./main
all:	
	${CC} server.c -o server 
clent:
	${CC} client.c -o client	
code:
	${CC} code.c -o code
