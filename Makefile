<<<<<<< HEAD
CC=gcc
=======
CC=arm-xilinx-linux-gnueabi-g++
>>>>>>> 0820dbbe95a35df66e11f67634ab1c8be8f6fb76
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
<<<<<<< HEAD
	${CC} code.c -o code
=======
	${CC} code.c -o code
>>>>>>> 0820dbbe95a35df66e11f67634ab1c8be8f6fb76
