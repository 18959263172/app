CC=g++
AR=${CROSS_CP}ar
src=${wildcard  *.c}
obj=${wildcard *.o}
header=${wildcard *.h}
REF:= 
PRG := test.linux
all:  $(obj)
	${CC}  -c  $(src) 
	rm libzcy.a
	${AR} rcs libzcy.a   $(obj)	
	ranlib libzcy.a
	cp libzcy.a /usr/lib/
	cp libzcy.a /lib/
	cp ${header} /usr/include  
