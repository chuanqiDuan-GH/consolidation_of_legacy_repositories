OBJ=command.o server.o M0.o start_camera.o camera_control.o lcd.o

svr.out:$(OBJ) 
	arm-none-linux-gnueabi-gcc $^  -o svr.out -lpthread -lsqlite3 -L/home/farsight/hqyj/sqlite3/sqlite_arm/lib -I/home/farsight/hqyj/sqlite3/sqlite_arm/include
M0.o:M0.c
	arm-none-linux-gnueabi-gcc -c M0.c -o M0.o -lpthread -lsqlite3 -L/home/farsight/hqyj/sqlite3/sqlite_arm/lib -I/home/farsight/hqyj/sqlite3/sqlite_arm/include
start_camera.o:start_camera.c
	arm-none-linux-gnueabi-gcc -c start_camera.c -o start_camera.o -lpthread 
camera_control.o:camera_control.c
	arm-none-linux-gnueabi-gcc -c camera_control.c -o camera_control.o -lpthread 
command.o:command.c
	arm-none-linux-gnueabi-gcc -c command.c -o command.o -lpthread -lsqlite3 -L/home/farsight/hqyj/sqlite3/sqlite_arm/lib -I/home/farsight/hqyj/sqlite3/sqlite_arm/include
server.o:server.c
	arm-none-linux-gnueabi-gcc -c server.c -o server.o -lpthread -lsqlite3 -L/home/farsight/hqyj/sqlite3/sqlite_arm/lib -I/home/farsight/hqyj/sqlite3/sqlite_arm/include
lcd.o:lcd.c
	arm-none-linux-gnueabi-gcc -c lcd.c -o lcd.o

.PHONY:clean
clean:
	$(RM) *.o *.out

