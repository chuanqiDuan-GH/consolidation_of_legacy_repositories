OBJ=command.o server.o

svr.out:$(OBJ) 
	arm-none-linux-gnueabi-gcc $^  -o svr.out -lpthread -lsqlite3 -L/home/farsight/hqyj/sqlite3/sqlite_arm/lib -I/home/farsight/hqyj/sqlite3/sqlite_arm/include
server.o:server.c
	arm-none-linux-gnueabi-gcc -c server.c -o server.o -lpthread -lsqlite3 -L/home/farsight/hqyj/sqlite3/sqlite_arm/lib -I/home/farsight/hqyj/sqlite3/sqlite_arm/include
command.o:command.c
	arm-none-linux-gnueabi-gcc -c command.c -o command.o -lpthread -lsqlite3 -L/home/farsight/hqyj/sqlite3/sqlite_arm/lib -I/home/farsight/hqyj/sqlite3/sqlite_arm/include


.PHONY:clean
clean:
	$(RM) *.o *.out

