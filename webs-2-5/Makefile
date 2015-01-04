
#include ../config.mk
PREFIX=./
#CROSS_PREFIX=arm-mv5sft-linux-gnueabi-
CROSS_PREFIX=arm-xilinx-linux-gnueabi-
all: 
	make -C ./LINUX webcomp
	find ../www -name "*.*" > websfile
	./LINUX/webcomp ../www ./websfile > ./webrom.c
	rm ./websfile
	CC=$(CROSS_PREFIX)gcc CFLAGS='$(CFLAGS)' make -C ./LINUX all
				        
install: _mkdir all
	@echo '[install]	$(PREFIX)/lib/libwebs.a' ; 			cp -arf ./LINUX/libwebs.a $(PREFIX)/lib/libwebs.a
	@echo '[install]	$(PREFIX)/bin/webs' ; 					cp -arf ./LINUX/webs $(PREFIX)/bin/webs
	@echo '[INSTALL] 	$(PREFIX)/include/libwebs/*.h'; cp -arf ./*.h $(PREFIX)/include/libwebs/

_mkdir:
	@echo '[MKDIR] 	$(PREFIX)/include/libwebs' ; 			mkdir -p $(PREFIX)/include/libwebs
	@echo '[MKDIR] 	$(PREFIX)/include/libwebs' ; 			mkdir -p $(PREFIX)/lib
	@echo '[MKDIR] 	$(PREFIX)/include/libwebs' ; 			mkdir -p $(PREFIX)/bin	
clean:
	make -C ./LINUX clean
	@echo '[RM]	webs' ; rm -f ./LINUX/webs
	@echo '[RM]	libwebs.a' ; rm -f ./LINUX/libwebs.a
	@echo '[RM]	$(PREFIX)/bin/webs' ; rm -f $(PREFIX)/bin/webs
	@echo '[RM]	$(PREFIX)/lib/libwebs.a' ; rm -f $(PREFIX)/lib/libwebs.a
	@echo '[RM]	$(PREFIX)/include/libwebs/*.h' ; rm -f $(PREFIX)/include/libwebs/*.h
