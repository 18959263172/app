root@ubuntu:/home/a/rootfs/vfs/app# 
root@ubuntu:/home/a/rootfs/vfs/app# ls
Makefile  Makefile~  socket.c  socket.c~
root@ubuntu:/home/a/rootfs/vfs/app# arm-xilinx-linux-gnueabi-ma
arm-xilinx-linux-gnueabi-ma: command not found
root@ubuntu:/home/a/rootfs/vfs/app# make
arm-xilinx-linux-gnueabi-gcc socket.c -o socket
root@ubuntu:/home/a/rootfs/vfs/app# ls
Makefile  Makefile~  socket  socket.c  socket.c~
root@ubuntu:/home/a/rootfs/vfs/app# ls
Makefile  Makefile~  socket  socket.c  socket.c~
root@ubuntu:/home/a/rootfs/vfs/app# 